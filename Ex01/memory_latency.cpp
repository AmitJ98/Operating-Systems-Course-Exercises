// OS 24 EX1

#include "memory_latency.h"
#include "measure.h"
#include <iostream>
#include "stdlib.h"


#define GALOIS_POLYNOMIAL ((1ULL << 63) | (1ULL << 62) | (1ULL << 60) | (1ULL << 59))


/**
 * Converts the struct timespec to time in nano-seconds.
 * @param time - the struct timespec to convert.
 * @return - the value of time in nano-seconds.
 */
uint64_t nanosectime(struct timespec t)
{
	return (uint64_t )t.tv_sec * 1000000000  + t.tv_nsec;
}


/**
* Measures the average latency of accessing a given array in a sequential order.
* @param repeat - the number of times to repeat the measurement for and average on.
* @param arr - an allocated (not empty) array to preform measurement on.
* @param arr_size - the length of the array arr.
* @param zero - a variable containing zero in a way that the compiler doesn't "know" it in compilation time.
* @return struct measurement containing the measurement with the following fields:
*      double baseline - the average time (ns) taken to preform the measured operation without memory access.
*      double access_time - the average time (ns) taken to preform the measured operation with memory access.
*      uint64_t rnd - the variable used to randomly access the array, returned to prevent compiler optimizations.
*/
struct measurement measure_sequential_latency(uint64_t repeat, array_element_t* arr, uint64_t arr_size, uint64_t zero)
{
    repeat = arr_size > repeat ? arr_size:repeat; // Make sure repeat >= arr_size

    // Baseline measurement:
    struct timespec t0;
    timespec_get(&t0, TIME_UTC);
    register uint64_t rnd=12345;
    for (register uint64_t i = 0; i < repeat; i++)
    {
        register uint64_t index = i % arr_size;
        rnd ^= index & zero;
        rnd = (rnd >> 1) ^ ((0-(rnd & 1)) & GALOIS_POLYNOMIAL);  // Advance rnd pseudo-randomly (using Galois LFSR)
    }
    struct timespec t1;
    timespec_get(&t1, TIME_UTC);

    // Memory access measurement:
    struct timespec t2;
    timespec_get(&t2, TIME_UTC);
    rnd=(rnd & zero) ^ 12345;
    for (register uint64_t i = 0; i < repeat; i++)
    {
        register uint64_t index = i % arr_size;
        rnd ^= arr[index] & zero;
        rnd = (rnd >> 1) ^ ((0-(rnd & 1)) & GALOIS_POLYNOMIAL);  // Advance rnd pseudo-randomly (using Galois LFSR)
    }
    struct timespec t3;
    timespec_get(&t3, TIME_UTC);

    // Calculate baseline and memory access times:
    double baseline_per_cycle=(double)(nanosectime(t1)- nanosectime(t0))/(repeat);
    double memory_per_cycle=(double)(nanosectime(t3)- nanosectime(t2))/(repeat);
    struct measurement result;

    result.baseline = baseline_per_cycle;
    result.access_time = memory_per_cycle;
    result.rnd = rnd;
    return result;

}




int argument_validation(uint64_t max_size , double factor , uint64_t repeat)
{

  if (factor <= 1 )
  {
    std::cout << "Factor needs to be higher then one" <<std::endl;
    return -1;
  }
    if(max_size<100){
        std::cout << "Max size should be more than 100 \n";
        return -1;
    }
    if (repeat <= 0 )
    {
        std::cout << "Reapeat shold be positive" <<std::endl;
        return -1;
    }

  return 0;

}




/**
 * Runs the logic of the memory_latency program. Measures the access latency for random and sequential memory access
 * patterns.
 * Usage: './memory_latency max_size factor repeat' where:
 *      - max_size - the maximum size in bytes of the array to measure access latency for.
 *      - factor - the factor in the geometric series representing the array sizes to check.
 *      - repeat - the number of times each measurement should be repeated for and averaged on.
 * The program will print output to stdout in the following format:
 *      mem_size_1,offset_1,offset_sequential_1
 *      mem_size_2,offset_2,offset_sequential_2
 *              ...
 *              ...
 *              ...
 */
/**
 * Runs the logic of the memory_latency program. Measures the access latency for random and sequential memory access
 * patterns.
 * Usage: './memory_latency max_size factor repeat' where:
 *      - max_size - the maximum size in bytes of the array to measure access latency for.
 *      - factor - the factor in the geometric series representing the array sizes to check.
 *      - repeat - the number of times each measurement should be repeated for and averaged on.
 * The program will print output to stdout in the following format:
 *      mem_size_1,offset_1,offset_sequential_1
 *      mem_size_2,offset_2,offset_sequential_2
 *              ...
 *              ...
 *              ...
 */
int main(int argc, char* argv[]) {
    struct timespec t_dummy;
    timespec_get(&t_dummy, TIME_UTC);
    const uint64_t zero = nanosectime(t_dummy) > 1000000000ull ? 0 : nanosectime(t_dummy);

    if (argc != 4) {
        std::cout << "The program needs 3 arguments: max size, factor, repeat\n";
        return -1;
    }

    uint64_t max_size = std::stoul(argv[1]);
    double factor = std::stod(argv[2]);
    uint64_t repeat = std::stoll(argv[3]);


    if (argument_validation(max_size,factor,repeat) == -1)
    {
        return -1;
    }
    

    for (uint64_t size = 100; size <= max_size; size = size*factor) {
        array_element_t* arr = (array_element_t*)(malloc(size));
        if (arr == nullptr) {
            std::cout << "Memory allocation failed.\n";
            return -1;
        }

        uint64_t arr_size = size / sizeof(array_element_t);

        for (uint64_t index = 0; index < arr_size; index++) {
            arr[index] = zero;
        }
        
        struct measurement random = measure_latency(repeat, arr, arr_size, zero);
        struct measurement sequential = measure_sequential_latency(repeat, arr, arr_size, zero);
        double r = random.access_time - random.baseline;
        double s = sequential.access_time - sequential.baseline;

        std::cout << size << ',' << r << ',' << s << std::endl;
        free(arr);
    }

    return EXIT_SUCCESS;
}
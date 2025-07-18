#include "VirtualMemory.h"
#include "PhysicalMemory.h"

#define TOTAL_BITS 64


uint64_t calculate_bits(uint64_t virtualAddress, uint64_t level)
{
  uint64_t offsetWidth = VIRTUAL_ADDRESS_WIDTH % OFFSET_WIDTH;
  if (level != 0 || offsetWidth == 0)
  {
    offsetWidth = OFFSET_WIDTH;
  }

  uint64_t mask = (static_cast<uint64_t>(1) << offsetWidth) - 1;
  uint64_t shiftAmount = (TABLES_DEPTH - level) * OFFSET_WIDTH;
  virtualAddress = virtualAddress >> shiftAmount;

  return (virtualAddress & mask);

}


uint64_t find_offset(uint64_t virtualAddress)
{
  int dist  = TOTAL_BITS - OFFSET_WIDTH;
  return (virtualAddress << dist) >> dist;
}


void initialize_frame(uint64_t frame)
{
  for (uint64_t i = 0; i < PAGE_SIZE; ++i)
  {
    PMwrite(frame * PAGE_SIZE + i, 0);
  }
}


word_t cyclical_distance(uint64_t p1 , uint64_t p2)
{
  uint64_t subtraction;
  if(p1 > p2)
    subtraction = p1 - p2;
  else
    subtraction = p2 - p1;

  if (NUM_PAGES - subtraction < subtraction)
    return NUM_PAGES - subtraction;
  return subtraction;
}


void update_distance(uint64_t pageIn, uint64_t currPath, word_t* MaxDist, uint64_t frame,
                     uint64_t* illegal_add, uint64_t* result_frame, uint64_t* result_path ,
                     uint64_t prev_add, uint64_t* prev_frame_add)
{
  if(frame != *illegal_add)
  {
    word_t curr_dist = cyclical_distance (pageIn, currPath);
    if (curr_dist > *MaxDist)
    {
      *MaxDist = curr_dist;
      *result_frame = frame;
      *prev_frame_add = prev_add;
      *result_path = currPath;
    }
  }
}


void search_frame(uint64_t frame, word_t* empty_frame, uint64_t depth, uint64_t* illegal_add,
                  word_t* max_frame, uint64_t* result_frame, uint64_t* prev_frame_add,
                  uint64_t prev_add, uint64_t pageIn, word_t* MaxDist, uint64_t curr_path,
                  uint64_t* result_path)
{
  if (*empty_frame == 1 || frame >= NUM_FRAMES)
  {
    return;
  }

  if (depth == TABLES_DEPTH)
  {
    *empty_frame = false;
    update_distance(pageIn, curr_path, MaxDist, frame, illegal_add, result_frame, result_path,
                    prev_add, prev_frame_add);
    return;
  }

  word_t row_val;
  uint64_t curr_add;
  bool is_empty = true;

  for (int i = 0; i < PAGE_SIZE; i++)
  {
    curr_add = (frame * PAGE_SIZE) + i;
    PMread(curr_add, &row_val);
    if (row_val != 0)
    {
      is_empty = false;
      if (row_val > *max_frame)
      {
        *max_frame = row_val;
      }
      uint64_t path = (curr_path << OFFSET_WIDTH) | i;
      search_frame (row_val, empty_frame, depth+1, illegal_add, max_frame, result_frame,
                    prev_frame_add, curr_add, pageIn, MaxDist, path, result_path);
    }
  }

  if(is_empty && frame != *illegal_add)
  {
    *empty_frame = true;
    *prev_frame_add = prev_add;
    *result_frame = frame;
  }
}


uint64_t find_frame(uint64_t illegal_add, word_t pageIn)
{
  uint64_t result_frame = 0;
  uint64_t result_path = 0;
  uint64_t prev_frame_add = 0;
  word_t max_frame = 0;
  word_t empty_frame = 0;
  word_t MaxDist = 0;

  search_frame(0, &empty_frame, 0, &illegal_add, &max_frame, &result_frame, &prev_frame_add, 0,
               pageIn, &MaxDist, 0, &result_path);

  // case 1
  if (empty_frame == 1)
  {
    PMwrite(prev_frame_add, 0);
  }
    //case 2
  else if (max_frame+1 < NUM_FRAMES)
  {
    result_frame = max_frame +1;
  }
    //case 3
  else
  {
    PMwrite (prev_frame_add, 0);
    PMevict (result_frame, result_path);
  }
  return result_frame;
}


uint64_t translate_address(uint64_t virtualAddress)
{
  word_t last_frame = 0;
  uint64_t next_frame = 0;
  word_t curr_frame = 0;
  uint64_t curr_bit = 0;
  word_t pageIn = virtualAddress >> OFFSET_WIDTH;
  for(int level = 0 ; level < TABLES_DEPTH; level++)
  {
    curr_bit = calculate_bits (virtualAddress, level);
    next_frame = (last_frame * PAGE_SIZE) + curr_bit;
    PMread(next_frame, &curr_frame);
    if(curr_frame == 0) //the frame doesn't found
    {
      curr_frame = find_frame(last_frame, pageIn);
      if (level + 1 < TABLES_DEPTH )
      {
        initialize_frame (curr_frame);
      }
      else
      {
        PMrestore(curr_frame , pageIn);
      }
      PMwrite(next_frame, curr_frame);
    }
    last_frame = curr_frame;
  }
  return curr_frame;
}


void VMinitialize()
{
  initialize_frame (0);
}


int VMread(uint64_t virtualAddress, word_t* value)
{
  if(virtualAddress > VIRTUAL_MEMORY_SIZE -1 )
  {
    return 0;
  }
  uint64_t off_set_address = find_offset (virtualAddress);
  uint64_t frame = translate_address(virtualAddress);
  PMread(frame*PAGE_SIZE+off_set_address, value);
  return 1;
}


int VMwrite(uint64_t virtualAddress, word_t value)
{
  if(virtualAddress > VIRTUAL_MEMORY_SIZE -1 )
  {
    return 0;
  }
  uint64_t off_set_address = find_offset (virtualAddress);
  uint64_t frame = translate_address(virtualAddress);
  PMwrite(frame*PAGE_SIZE+off_set_address, value);
  return 1;
}


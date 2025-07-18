amitjoseph98, Maya.heilbrun 
Amit joseph (207255050) , Maya Heilbrun (207583410)
EX: 1

FILES:
memory_latency.cpp , the file with the measurement measure_sequential_latency function and the main function
makefile , to create an executeable file
results.png, the output graph of the project , ran with 6000000000 as max size (bytes), 1.05 as factor 200000000 as repeat

REMARKS:
The Y axis in the result graph is in a linear scale


Q1- Assignment 1:
Description of the program WhatIDo:

The program expects one argument from the user. If started without an argument or with more than one argument, the program creates a file and writes a message indicating that it should receive a single argument.
quick description: the program creates a folder and inside it 3 files to each file the program write to it and after that the 3 files and the folder are been deleted.

After receiving the correct argument, the program performs the following steps:

1) It creates a folder named "Welcome"  in 0775 mod that give permission of read, write and execute to the owner and to groups others will be able only to read and execute.
2) Inside this folder, it creates three files named "Welcome", "To", and "Os-2024", in that order.
3) The program checks the status of the file "Welcome", opens it, and writes the message: "amitjoseph98\nIf you haven't read the course guidelines yet --- do it right now!".
 After writing to the file, it closes it. where "amitjoseph98" is my cse username.
4) Similarly, the program checks the status of the file "To", opens it, and writes the message: "Start exercises early!". After writing to the file, it closes it.
5) The program then checks the status of the file "Os-2024", opens it, and writes the message: "Good luck!". After writing to the file, it closes it.
6) Finally, the program deletes the files "Welcome", "To", and "Os-2024" that were created inside the folder "Welcome", in that order.
7) It removes the "Welcome" folder, and the process ends.


Q2 - Assignment 2:

The graph aligns with my expectations based on CPU cache and memory access patterns. Here's a concise analysis:

Latency for Random Access vs. Sequential Access Patterns:

Sequential Access (Orange Line):

Expected Behavior: Sequential access should have low and stable latency due to spatial locality, allowing efficient prefetching.
Observed Behavior: The graph shows low latency for sequential access across different array sizes, matching expectations.


Random Access (Blue Line):

Expected Behavior: Random access usually has higher latency because it doesn't benefit from spatial locality, causing more cache misses.
Observed Behavior: The graph shows a significant increase in latency for random access as array size grows, especially beyond cache limits when it reach the Ram space.


Latency Across Different Cache Levels:

L1 Cache (Red Line at 32 KiB per Core):
Expected Behavior: L1 cache should have the lowest latency.
Observed Behavior: Minimal latency for both access types when data fits within L1.

L2 Cache (Green Line at 256 KiB per Core):
Expected Behavior: Slightly higher latency than L1.
Observed Behavior: Increased latency for random access; sequential access remains efficient.

L3 Cache (Brown Line at 6 MiB):
Expected Behavior: Higher latency than L2.
Observed Behavior: Significant increase in latency for random access beyond L2 size.

Main Memory (Beyond L3 Cache, The Ram):
Expected Behavior: Highest latency when accessing main memory, expecting slightly higher latency in sequential access.
Observed Behavior: Dramatic latency increase for both access types beyond L3 capacity, surprisingly sequential access remain very efficient.

The graph highlights the differences in latency for random and sequential access patterns and the impact of cache levels.
 
My conclusions are:
Sequential Access: Maintains low latency due to efficient cache usage and the CPU “hardware prefetching” feature that can predict which cache lines will be needed even before they are requested.
Random Access: Higher latency due to frequent cache misses.
Cache Levels: Latency increases as data moves from L1 to L2 to L3 caches and then to main memory when trying access in the random way.
These results underscore the importance of access patterns and cache management in optimizing performance.







## Homework 3

### C Exercises

Modify the link below so it points to the `ex02.5` directory in your
student repository.

[Here is a link to the ex02.5 directory in my repository](https://github.com/iblancett/ExercisesInC/tree/master/exercises/ex02.5)

### Think OS Chapter 3 reading questions

### Virtual memory

1) The Georgian alphabet has 33 letters.  How many bits are needed to specify a letter?  6 bits

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.  
Ignoring the details of the encoding scheme, how many different characters can be represented?  2^32 characters

3) What is the difference between "memory" and "storage" as defined in *Think OS*?  Memory usually refers to volatile data (RAM) that disappears when the computer is turned off.  Storage, on the other hand, retains state.

4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes? GiB is 2^30, GB is 10^9, a GiB is 7.4% more than a GB

5) How does the virtual memory system help isolate processes from each other?  It blocks processes from accessing addresses being acessed/used by other processes

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?  So they can grow toward each other, saving space if you have a small stack and a large heap or vice versa.

7) What Python data structure would you use to represent a sparse array?  Dictionary

8) What is a context switch?  The mechanism that allows the OS to pause a process and resume it later.


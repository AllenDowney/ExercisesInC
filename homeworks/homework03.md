## Homework 3

### C Exercises

Modify the link below so it points to the `ex03` directory in your
student repository.

<<<<<<< HEAD
[Here is a link to the ex02.5 directory in my repository](https://github.com/iblancett/ExercisesInC/tree/master/exercises/ex02.5)
=======
[Here is a link to the ex03 directory in my repository](https://github.com/YOUR_GITHUB_USERNAME_HERE/ExercisesInC/tree/master/exercises/ex03)
>>>>>>> af6015fd869d00aeb2fc4e2871b4df7a3ff9d2e7

### Think OS Chapter 4 reading questions

**Files and file systems**

<<<<<<< HEAD
1) The Georgian alphabet has 33 letters.  How many bits are needed to specify a letter?  6 bits

2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.  
Ignoring the details of the encoding scheme, how many different characters can be represented?  2^32 characters

3) What is the difference between "memory" and "storage" as defined in *Think OS*?  Memory usually refers to volatile data (RAM) that disappears when the computer is turned off.  Storage, on the other hand, retains state.

4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes? GiB is 2^30, GB is 10^9, a GiB is 7.4% more than a GB

5) How does the virtual memory system help isolate processes from each other?  It blocks processes from accessing addresses being acessed/used by other processes

6) Why do you think the stack and the heap are usually located at opposite ends of the address space?  So they can grow toward each other, saving space if you have a small stack and a large heap or vice versa.

7) What Python data structure would you use to represent a sparse array?  Dictionary

8) What is a context switch?  The mechanism that allows the OS to pause a process and resume it later.
=======
1) What abstractions do file systems provide?  Give an example of something that is logically 
true about files systems but not true of their implementations.

2) What information do you imagine is stored in an `OpenFileTableEntry`?

3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?

4) Suppose your program writes a file and prints a message indicating that it is done writing.  
Then a power cut crashes your computer.  After you restore power and reboot the computer, you find that the 
file you wrote is not there.  What happened?

5) Can you think of one advantage of a File Allocation Table over a UNIX inode?  Or an advantage of a inode over a FAT?

6) What is overhead?  What is fragmentation?

7) Why is the "everything is a file" principle a good idea?  Why might it be a bad idea?

If you would like to learn more about file systems, a good next step is to learn about journaling file systems.  
Start with [this Wikipedia article](https://en.wikipedia.org/wiki/Journaling_file_system), then 
[Anatomy of Linux Journaling File Systems](http://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html).  
Also consider reading [this USENIX paper](https://www.usenix.org/legacy/event/usenix05/tech/general/full_papers/prabhakaran/prabhakaran.pdf).


>>>>>>> af6015fd869d00aeb2fc4e2871b4df7a3ff9d2e7


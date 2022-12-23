## Running and testing
**For Question 1**
* Run `make`
* Run `./a1`, `./a2`, `./b1` or `./b2` depending upon which variant you want to run

**For Question 2**
* Run `make all` to build all source files. Run `make socket`, `make fifo` or `make shm` to build only the corresponding source files
* For Unix domain sockets, run `./p1-socket` and `./p2-socket` in different terminal windows
* For FIFOs, run `./p1-fifo & ./p2-fifo` in the same terminal window (you may run them separately as well)
* For shared memory, run `./p1-shm & ./p2-shm` in the same terminal window (you may run them separately as well)

**For Question 3**
* nahi hua bhyi, semester khatam kab hoga T-T

## Assignment-3

### Question 1: Modified Dining Philosophers Problem

The dining philosophers problem contains five philosophers sitting on a round table can perform only one among two actions – eat and think. For eating, each of them requires two forks, one kept beside each person. Typically, allowing unrestricted access to the forks may result in a deadlock.

(a) Write a program to simulate the philosophers using threads, and the forks using global variables.

Resolve the deadlock using the following techniques:
1. Strict ordering of resource requests, and
2. Utilization of semaphores to access the resources.

(b) Repeat the above system only using semaphores now with a system that also has two sauce bowls. The user would require access to one of the two sauce bowls to eat, and can access any one of them at any point of time.

### Question 2: Interprocess Communication

Write two programs `P1` and `P2`. The first program `P1` needs to generate an array of 50 random strings (of characters) of fixed length each. `P1` then sends a group of five consecutive elements of the array of strings to `P2` along with the ID’s of the strings, where the ID is the index of the array corresponding to the string. The second program `P2` needs to accept the received strings, and send back the highest ID received back to `P1` to acknowledge the strings received. The program `P2` simply prints the ID’s and the strings on the console. On receiving the acknowledged packet, `P1` sends the next five strings, with the string elements starting from the successor of the acknowledged ID. The above mechanism needs to be implemented using three different techniques: (i) Unix domain sockets, (ii) FIFOs, and (iii) shared memory. Please note that you should NOT make assumptions about the reliability of the interprocess communication mechanism, unless they are guaranteed by the mechanism itself. You should also not use redundant mechanisms to guarantee reliability if the protocol itself guarantees it. Print the amount of time required to finish receiving the acknowledgment of all 50 strings in the three cases.

### Question 3: Custom Kernel Module

This exercise requires you to write your own small kernel module. You require to implement a kernel system call as a module. The task of the system call would be to read the entries of the process `task_struct` corresponding to any given process (supplied as input via command line argument) and prints the values of the following field: pid, user id, process group id (pgid) and command path. The system call should be implemented in the kernel (and not directly as a mainline kernel function, like that was done for A2). It should be functional only when the module is loaded, not otherwise.

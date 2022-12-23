## Running and testing
**For Question 1.1**
* Run `make count`

**For Question 1.2**
* Run `make kernel` (code is buggy, don't use)
* Altenatively, you may run `make kernel-test` to simulate the compilation and save yourselves some time

**For Question 2**
* Patch your kernel using `patchfile.patch` and reboot
* Test the newly installed syscall by running `gcc test.c && ./a.out`

## Assignment-2-1: Linux `pthreads` and their scheduling

### Question 1.1
This exercise is to show you how to use Linux’s scheduling policies for three threads. You need to launch three threads, each of which relies on three different functions, `countA()`, `countB()` and `countC()`. Each function does the same thing, i.e. counts from 1 – 2^32. The following should be the detailed specification of each of the threads, to being with:

1. Thread 1 (call it `Thr-A()`): Uses `SCHED_OTHER` scheduling discipline with standard priority (nice: 0).
2. Thread 2 (call it `Thr-B()`): Uses `SCHED_RR` scheduling discipline with default priority.
3. Thread 3 (call it `Thr-C()`): Uses `SCHED_FIFO` scheduling discipline with default priority.

Each of these threads must time the process of counting from 1 – 2^32. You can use the `clock_gettime()` function for obtaining the actual time ticks that can be used to compute how long it took to complete a function. We require you benchmark these three schedulers by changing the scheduling classes of the three threads (keeping the other scheduling priorities the same), against the counting program. For these cases, you would require to rely on `pthread_schedsetparam()` and related functions for the same. You would require to generate histograms showing which scheduler completes the task when, depending upon the scheduling policy. You may choose different colors for the histogram bars, with one axis showing the time to complete, and the other showing the thread priorities. Of course, you cannot plot for all possible values of priorities; you would require to choose only some.

### Question 1.2
This part of the exercise, involves creating three process, instead of the three threads. Each of these process should involve compiling a copy of the Linux kernel source (with the minimal config shared by the TAs earlier). The three processes should be created with `fork()` and thereafter the child processes should use `execl()` family system calls to run a different a different bash script, each of which should be having the commands to compile a copy of the kernel. To time the execution, the parent process could get the clock timestamp (using `clock_gettime()`) before the fork and after each process terminates (the event of which could be identified when the blocking system call `waitpid()`) returns.

## Assignment-2-2:  Kernel memory copy (`kernel_2d_memcpy()`)
This exercise aimed to test your understanding how system calls work. You need to write a system call, `kernel_2d_memcpy()`, which copies one 2-D floating point matrix to another. You would require using kernel functions like `__copy_from_user()` and `__copy_to_user()` to read data bytes from user space and write back to user space. In other words, this is a version of `memcpy()` that relies on the kernel to do the necessary copy operations, which are otherwise usually done directly in the user space (using the standard C library routines).
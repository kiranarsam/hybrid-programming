# Synchronization in Linux Kernel Programming

Concurrency: The ability to handle multiple outstanding tasks/processes with the illusion or reality of simultaneously.

Single Core Env: Concurrency is acheived via a process called context-switching i.e., at a particular time period, only a single task gets executed.

Multi Core Env: Multiple processes executing simultaneously on multiple processors/CPU's.

To find out how many cores in platform:
```bash
# using proc file
$ grep -c ^processor /proc/cpuinfo
# using nproc exeutable
$ nproc
```

To find num of processors running in platform:
```bash
# processors running
$ ps -eaf
```

## Multiprocessing systems
Each CPU has its own OS

The simplest possible way to organize a multiprocessor operating systems:
Statically divide memory into as many partitions as there are CPUs and give each CPU its own private memory and its own private copy of the operating system.
One obvious optimization is to allow all the CPUs to share the operating system code and make private copies of only the data.


## SYmmetric Multiprocessors
One copy of the OS in the memory, any CPU can run it.

## Preemption
Means forcefully taking away of the processor from one process and allocating it to another process. Switching

Switching from one running task/process to another/process is known as context switch

The scheduler is called after each timer interrupt. It determines what process to run next based on a variety of factors, priority, time already run, etc.,

Difference b/w preemption and context switching:
Preemption: Firing of timer interrupt is preempting the current running process and running the interrupt serivce routine of timer interrupt


## Causes of concurrency
- Interrupts - An interrupt can occur asynchronously at almost any time; interrupting the currently executing code
- Softirqs and tasklets - Kernel can raise or schedule a softirq or tasklet at almost any time
- Kernel preemption - Because kernel is premptive, one task in the kernel can preempt another
- Sleeping and synchronization with user space - Task in the kernel can sleep and thus invoke the schedular, resulting in running of a new process
- Symmetrical multiprocessor - 2 or more processors can execute code at exactly the same time.

## Find max number of processors in kernel
Maximum num of processors that an SMP kernel could support
```bash
$ grep NR_CPUS /boot/config-`uname -r`
```
you can override this with the nr_cpus kernel parameter in the bootlooader command line.
nr_cpus=12

Use num_online_cpus() function to get the number of cpus online.

## Find which processor is running kernel control path
smp_processor_id() gives you the current processor number on which kernel is running
# SPM19 👨🏻‍💻
Assignments and Project of the Course Parallel and Distributed Systems: Paradigms and Models (2018-19) @ Unipi

## Assignment 1 ✅

Implement a 5 stage pipeline in C++ using the standard C++ concurrency mechanisms (shared memory target architecture). The stages should behave as follows: 
- stage one outputs a stream of m integers (m from command line parameters)
- stage two increases by 1 all the input stream items
- stage three squares all input stream items
- stage four decreases all the input stream items, and
- stage five prints the input stream items
The pipeline should be implementing using 5 threads, each one behaving as the corresponding stage. All functions computed by the three inner pipeline stages should use 10ms to compute (use a std::this_thread::sleep_for to wait that amount of time).

Goal 1: verify the computation takes overall something close to (m x 10)ms.
Goal 2: measure the overhead needed to set up and complete the parallel computation

Optional: verify what happens (performance, core usage): 
- in case thread allocation is left to the operating system
- in case you stick each thread to a particular core.

To read core where the current thread is running consider using sched_getcpu(). 
To stick a thread to a core (context) use pthread_setaffinity_np(...)

## Assignment 2 🛠

Implement, using only C++ standard mechanisms and threads, a program that computes in parallel a set of independent tasks, initially stored in a shared data structure, and delivers results using a second shared data structure. The number of tasks to be computed is known and accessible to the parallel executors, as well as the number of tasks already computed/to compute. 
Assume an input task is given by an integer number N and the result to compute is the number of prime numbers included in range [1-N]. The initial set of tasks is picked up randomly in the range [1-10K].
Once the problem is working, add some delay in the procedure obtaining a task to be computed and delivering a result and observe the impact on scalability.
You may consider, after providing the C++/Thread implementation, to provide OpenMP or GrPPI implementations as well.

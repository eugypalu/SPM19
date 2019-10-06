# SPM19 🎓 👨🏻‍💻
Assignments of the Course Parallel and Distributed Systems: Paradigms and Models (2018-19) @ Unipi

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

## Assignment 2 ✅

Implement, using only C++ standard mechanisms and threads, a program that computes in parallel a set of independent tasks, initially stored in a shared data structure, and delivers results using a second shared data structure. The number of tasks to be computed is known and accessible to the parallel executors, as well as the number of tasks already computed/to compute. 
Assume an input task is given by an integer number N and the result to compute is the number of prime numbers included in range [1-N]. The initial set of tasks is picked up randomly in the range [1-10K].
Once the problem is working, add some delay in the procedure obtaining a task to be computed and delivering a result and observe the impact on scalability.
You may consider, after providing the C++/Thread implementation, to provide OpenMP or GrPPI implementations as well.

## Assignment 2 (Bis) ✅

Implement two versions of the prime number application of the second assignment using FastFLow. The first version should use a farm, with the emitter generating the input stream and the collector storing the result pairs (input task, number of primes in the interval). The second version should use parallel for instead, assuming the input tasks are already stored in a vector.

## Assignment 3 ✅

Parallel implementation of Game Of Life (Conway)
We require to provide a parallel implementation (using primitive C++ mechanisms) of the Conway's Game of Life. Given an n x n matrix of cells with an initial assignment of alive cells, compute N iterations using nw threads. In case you want to display on the screen (or save to the disk) a graphic representation of the board, please consider using CImg library (single .h file to be compiled with the source. Declaring a color picture is a matter of declaring a Cimg im(x-width, y-width, z-width, colors); variable and then single pixels may be accessed with the overloaded () operator (coords and channel parameters) for reading an writing.

## Assignment 4 ✅

We wish you implement an object computing in parallel (shared memory, using threads (ver 1) and FF (ver 2)) the google map reduce. Parameters to be given include the map function (type function<pair<Tout,Tkey>(Tin)>), the reduce function (type function<Tout(Tout,Tout)>). The input task is a vector<Tin> and the output result has to be a vector<pair<Tout,Tkey>.

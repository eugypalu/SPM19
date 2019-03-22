/*
Implement a 5 stage pipeline in C++ using the standard C++ concurrency mechanisms (shared memory target architecture).
 The stages should behave as follows: 
- stage one outputs a stream of m integers (m from command line parameters)
- stage two increases by 1 all the input stream items
- stage three squares all input stream items
- stage four decreases all the input stream items, and
- stage five prints the input stream items
The pipeline should be implementing using 5 threads, each one behaving as the corresponding stage. All functions 
computed by the three inner pipeline stages should use 10ms to compute (use a std::this_thread::sleep_for to wait
 that amount of time).

Goal 1: verify the computation takes overall something close to (m x 10)ms.
Goal 2: measure the overhead needed to set up and complete the parallel computation

Optional: verify what happens (performance, core usage): 
- in case thread allocation is left to the operating system
- in case you stick each thread to a particular core.

To read core where the current thread is running consider using sched_getcpu(). 
To stick a thread to a core (context) use pthread_setaffinity_np(...)
*/

#include <iostream>
#include <thread>
#include <chrono>
#include "./safeQueue.h"
#include "./threadTasks.h"


int main(int argc, char * argv[]){
    if(argc == 1){
        std::cout << "Usage: input the lenght of the stream" << std::endl;
        return 0;
    }

    auto start = std::chrono::high_resolution_clock::now();

    int streamLen = atoi(argv[1]);

    std::vector<std::thread *> threadVector(5);
    std::vector<safeQueue<int> *> threadQueues(4);

    for(int i=0;i<4;i++){
        threadQueues[i] = new safeQueue<int>();
    }


    threadVector[0] = new std::thread(dispatcher, streamLen, threadQueues[0]);
    threadVector[1] = new std::thread(increment, threadQueues[0], threadQueues[1]);
    threadVector[2] = new std::thread(sqrt, threadQueues[1], threadQueues[2]);
    threadVector[3] = new std::thread(decrement, threadQueues[2], threadQueues[3]);
    threadVector[4] = new std::thread(printOutput, threadQueues[3]);


    for (int i = 0; i < 5; i++){
        threadVector[i]->join();
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

    std::cout << "Total Time: " << milliseconds << std::endl;

    return 0;
}
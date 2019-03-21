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
#include "./safeQueue.h"

using namespace std;




int main(int argc, char * argv[]){
    if(argc == 1){
        cout << "Usage: input the lenght of the stream" << endl;
        return 0;
    }
    
    int streamLen = atoi(argv[1]);

    safeQueue<int> * queue = new safeQueue<int>();
    queue->push(10);

    int i = (int) queue->pop();

    cout << i << endl;

    return 0;
}
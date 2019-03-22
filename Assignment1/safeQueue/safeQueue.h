#include <queue>
#include <limits.h>
#include <mutex>
#include <condition_variable>

/*
    safeQueue is the class that implements the safe pop and push from a queue.
    The push method check if the queue is full and in that case wait.
    The pop method check if the queue is empty and in that case wait.
    When an item is pushed into the queue the waiting thread are notified.
*/
template <class T> class safeQueue{

  private:
    std::queue<T> myQueue;
    std::mutex mtx;
    std::condition_variable cv;
    int queueSize;

  public:

    /*
        Add an item to the queue 
    */
    void push(int item){
    
        std::unique_lock<std::mutex> lck(mtx);
        if(myQueue.size() == queueSize)
            cv.wait(lck);
        myQueue.push(item);
        cv.notify_all();
    }

    /*
        Remove the first item of the queue
    */
    T pop(){
        // Unique Lock uses the previously definined mutex 
        // When the queue is empy we do the wait with the previously defined condition
        // variable.
        std::unique_lock<std::mutex> lck(mtx);
        if(myQueue.empty())
            cv.wait(lck);
        T item = myQueue.front();
        myQueue.pop();
        return item;
    }

    // Constructor
    safeQueue(int size){
        queueSize = size;
        {}
    }

    safeQueue(){
        queueSize = std::numeric_limits<unsigned int>::max();
        {}
    }

};
#include <string>
#include <iostream>
#include <thread>
#include "./safeQueue.h"
#include <chrono>
#include <cstdlib>

using namespace std;

/*
    The producer insert #StreamLen elements into the queue
*/
void producerCode(int streamLen, safeQueue<int> *queue)
{
    for (int i = 0; i < streamLen; i++)
    {
        queue->push(i);
    }

    queue->push(-1);

    return;
}

/*
    The consumer Thread extract the items from the queue
*/
void consumerCode(safeQueue<int> *queue){
    int extracted = 0;
    while(extracted != -1){
        extracted = queue->pop();
        cout << extracted << endl;
    }

    return;
}

int main(int argc, char *argv[]){

    if (argc == 1)
    {
        cout << "Usage: input the lenght of the stream" << endl;
        return 0;
    }

    int streamLen = atoi(argv[1]);
    int nThread = atoi(argv[2]);

    safeQueue<int> *queue = new safeQueue<int>();

    std::cout << "Starting Producer Thread "<< std::endl;
    thread producer(producerCode, streamLen, queue);

    std::cout << "Starting Consumer Thread " << std::endl;
    thread consumer(consumerCode, queue);


    producer.join();
    consumer.join();

    

    return 0;
}


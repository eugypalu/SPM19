#include <iostream>
#include <thread>
#include <chrono>

std::chrono::milliseconds waitTime(10);

void dispatcher(int streamLen, safeQueue<int> * outputQueue){
    for(int i=0;i<streamLen;i++){
        outputQueue->push(i);
        std::this_thread::sleep_for(waitTime);
    }

    outputQueue->push(-1);
}

void increment(safeQueue<int> * inputQueue, safeQueue<int> * outputQueue){
    int extracted = 0;

    while((extracted = inputQueue->pop()) != -1){

        outputQueue->push(++extracted);

        std::this_thread::sleep_for(waitTime);
    }

    outputQueue->push(-1);
}

void sqrt(safeQueue<int> *inputQueue, safeQueue<int> *outputQueue){
    int extracted = 0;
    while ((extracted = inputQueue->pop()) != -1){

            outputQueue->push(extracted * extracted);
            std::this_thread::sleep_for(waitTime);
        }
        outputQueue->push(-1);
}

void decrement(safeQueue<int> *inputQueue, safeQueue<int> *outputQueue){
    int extracted = 0;
    while ((extracted = inputQueue->pop()) != -1){

        outputQueue->push(--extracted);
        std::this_thread::sleep_for(waitTime);
    }
    outputQueue->push(-1);
}

void printOutput(safeQueue<int> *inputQueue){
    int extracted = 0;
    while ((extracted = inputQueue->pop()) != -1){

        std::cout << extracted << std::endl;
        std::this_thread::sleep_for(waitTime);
    }
}
#include <thread>
#include <vector>
#include "./safeQueue/safeQueue.h"
#include <iostream>
#include <math.h>
#include "./Utils/utils.h"
#include "./Utils/utimer.hpp"
#define EOS -1


safeQueue<int> producerQueue;
safeQueue<int> outputQueue;


/*
    Producer thread
*/
void producer(int numTask){
    for(int i=0;i<numTask;i++){
        int tmp = rand()%10000+1;
        producerQueue.push(tmp);
        //active_udelay(500);
    }

    producerQueue.push(EOS);
}

/*  
    This function count the number of prime number in the interval and save
    the result in the vector partialResults.
*/
void computePrime(int nw, int start, int end, std::vector<int> * partialResults, int position){
    
    for(int i=start; i<=end; i++){
        if(isPrime(i)){
            (* partialResults)[position]++;
        }
    }
    //active_udelay(500);
}

/*
    Compute the length of every bin.
*/
int partition(int max, int nw){
    if (max < nw){
        nw = max;
        return 1;
    }
    else
        return ((max) / nw);
}

/*
    This function partition the vector in equal parts based on the number of worker,
    then creates the thread to compute the number of prime number in every parts.
    Finally compute the sum of the number of prime number of each part.
*/
void reducer(int nw){
    int extracted = 0;
    int sum = 0;

    while ((extracted = producerQueue.pop()) != -1){

        int max = extracted - 1;
        std::vector<std::thread> threads(nw);
        std::vector<int> partialResult(nw);
        int binLen = partition(max, nw);

        for(int i=0;i<nw;i++){
            if(i == nw -1){
                threads[i] = std::thread(computePrime, nw, (binLen * i) + 2, extracted, &partialResult, i);
            }else{
                threads[i] = std::thread(computePrime, nw, (binLen * i) + 2, binLen * (i + 1) + 1, &partialResult, i);
            }
        }
        for (int i = 0; i < nw; i++){
            threads[i].join();
        }


        sum = 0;
        for (int i = 0; i < nw; i++){
            sum+=partialResult[i];
        }
        //std::cout << sum << std::endl;

        outputQueue.push(sum);

    }
}

int main(int argc, const char ** argv){

    if(argc > 1){
        int numTask = atoi(argv[1]);
        int nw = atoi(argv[2]);

        {   
            utimer t("Producer + Reducer");
            // This thread produces the tasks and put them in the input queue.
            std::thread * producerThread = new std::thread(producer, numTask);

            // Compute the number of prime numbers included in the range
            reducer(nw);
            producerThread->join();
        }
        
    }
    else{
        std::cout << "Usage: the first parameter is the number of tasks, the second parameter is the number of worker" << std::endl;
    }


    return 0;
}
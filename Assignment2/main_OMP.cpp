#include <thread>
#include <vector>
#include "./safeQueue/safeQueue.h"
#include <iostream>
#include <math.h>
#include "./Utils/utils.h"
#include "./Utils/utimer.hpp"
#include <omp.h>
#define EOS -1

safeQueue<int> producerQueue;
safeQueue<int> outputQueue;


int main(int argc, char *argv[])
{

    utimer t("Prime Number");{

    if (argc != 1){
        auto numTask = atoi(argv[1]);
        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                {
                    for (int i = 0; i < numTask; i++){
                        int tmp = rand() % 10000 + 1;
                            producerQueue.push(tmp);
                            //active_udelay(500);
                    }
                    producerQueue.push(EOS);
                }

                
                #pragma omp section
                {
                    int counter = 0;
                    int extracted = 0;
                    while ((extracted = producerQueue.pop()) != -1){
                        counter = 0;
                        #pragma omp parallel for reduction(+ : counter)
                        for (int i = 2; i < extracted; i++){
                            if(isPrime(i))
                                counter++;
                            //active_udelay(500);
                        }
                        outputQueue.push(counter);
                        //std::cout << "The number of prime numbers is " << counter << std::endl;
                    }
                }
            }
        }
    }
    }

    return 0;
}
/*
    Esecuzione:
    make mainParallelFor
    ./main.o numeroTask lunghezzaTask nWorker seed
*/

#include <ff/ff.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include "testprime.cpp"
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>

using namespace ff;
using namespace std;

int main(int argc, char *argv[]){

    if (argc != 5){
        cout << "Usage is: " << argv[0] << " m n nw seed" << endl;
        return (-1);
    }
    int m = atoi(argv[1]);      // Quanti task
    int maxLen = atoi(argv[2]); // Dimensione singolo task
    int nw = atoi(argv[3]);     // Numero worker
    int seed = atoi(argv[4]);   // il seed per il calcolo random dei task

    vector<pair<int,int>> tasks;
    srand(seed);
    for (int i = 0; i < m; ++i){
        tasks.push_back(make_pair(rand() % maxLen, -1));
    }
    

    {
        utimer tpar("par nw = " + to_string(nw) + " m= " + to_string(m) + " max= " + to_string(maxLen));

        ff::ParallelFor pf(nw);
        pf.parallel_for(0L, m,
                        [&tasks](const long i) {
                            tasks[i].second = primes_to(tasks[i].first);
                        }
        );
    }
    

    //for (int i = 0; i < m; ++i)
      //  cout << tasks[i].first << " " << tasks[i].second << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include "testprime.cpp"

using namespace std;

int main( int argc, char * argv[]){

    if(argc != 5){
        cout << "Usage is: " << argv[0] << " m n seed nw" << endl;
        return (-1);
    }

    int m    = atoi(argv[1]); //how many tasks
    int maxv = atoi(argv[2]); // max single task size
    int seed = atoi(argv[3]);
    int nw   = atoi(argv[4]);

    vector<int> tasks;
    vector<pair<int, int>> res;

    //initialize tasks    
    srand(seed);
    for(int i=0; i<m; i++){
        tasks.push_back(rand() % maxv);
    }

    mutex lock_in;
    mutex lock_out;

    long timepar;


    // thread body, process items until the input vector is empty
    auto tbody = [&](int nw){
        
        while(true){
            int atask;
            {
                unique_lock<mutex> lock1(lock_in);
                if(tasks.empty()){
                    break;
                }
                atask = tasks.back();
                tasks.pop_back();
            }
            // compute popped task

            int np = primes_to(atask);

            // push the result

            {
                unique_lock<mutex> lock2(lock_out);
                res.push_back(make_pair(atask, np));
            }

        }
    };
    
    if(nw == 0){
        utimer tseq("seq m = " + to_string(m) + " max" + to_string(maxv));

        for(int t =(tasks.size()-1); t>=0; t--){
            auto np = primes_to(tasks.at(t));
            res.push_back(make_pair(tasks.at(t), np));
        }
    }
    res.resize(0);

    if(nw != 0){
        utimer tpar("par nw = " + to_string(nw) + " m= " + to_string(m) + " max= " + to_string(maxv));
        vector<thread * > tid(0);
        for(int i=0; i<nw; i++)
            tid.push_back(new thread(tbody, i));
        for(int i=0; i<nw; i++)
            tid[i] -> join();
    } 

    return 0;
}
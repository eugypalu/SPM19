#include <iostream>
#include <cmath>
#include "utimer.hpp"
using namespace std;

bool is_prime(int n){
    int limit = sqrt(n);
    for(int i=2; i<=limit; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int primes_to(int n){
    int nprimes = 0;
    for(int i=2; i<=n; i++){
        if(is_prime(i)){
            nprimes++;
        }
    }
    return nprimes;
}

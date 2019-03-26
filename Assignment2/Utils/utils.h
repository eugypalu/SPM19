#include <math.h>
#include <vector>

/*
    Function that return true if the number x is prime else
    return false
*/
bool isPrime(int x){

    if(x == 2)
        return true;

    else if(x % 2 == 0)
        return false;

    else {
        int i = 2;
        int sqR = sqrt(x);

        while (i <= sqR)
        {
            if (x % i == 0)
                return false;
            i++;
        }
    }
    
    return true;
}


/*     
    Active Delay
*/
void active_udelay(int usecs){
    
    auto start = std::chrono::high_resolution_clock::now();
    auto end = false;
    while (!end)
    {
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        auto usec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        if (usec > usecs)
            end = true;
    }
    return;
}
#include "mutex.h"
#include <iostream>

mutex::mutex()
{
    this->isLocked = false;
}

// basic spinning mutex lock that times out after 30 seconds

int mutex::lock(){
    if(!this->isLocked) {
        this->isLocked = true;
    }else{
        std::cout << " waiting " << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        while(this->isLocked) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> soFar = end - start;
            if(soFar.count() >= 30000.0) { // timeout after 30 seconds
                return 1;
            }
        }
    }
    return 0;
}



void mutex::unlock(){
    this->isLocked = false;
}

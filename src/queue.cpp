#include <iostream>
#include "queue.hpp"



template <typename T>
Queue<T>::Queue(){

}

template <typename T>
void Queue<T>::pop(){
    this->queue.pop();
}

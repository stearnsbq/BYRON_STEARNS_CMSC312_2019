#include "table.h"
#include <cmath>

using namespace std;
ProcessTable::ProcessTable(){
    this->table.reserve(41);
    this->currSize = this->table.size();
}

ProcessTable::~ProcessTable(){
    this->table.clear();
}

int ProcessTable::hash(unsigned int pid){
    return pid*2654435761 % (int)std::pow(2, 32);
}


int ProcessTable::checkCollision(int index){
    if (this->table[index])
    {
        return 1;
    }
    return 0;
}

void ProcessTable::put(Process * Process){
    int index = this->hash(Process->getPid()) % this->currSize;
    if (!checkCollision(index))
    {
        this->table[index] = Process;
    }else{
     for (size_t i = index; i < this->currSize; i++)
     {
         if (!this->table[i])
         {
             this->table[i] = Process;
             break;   
         }else if(i >= this->currSize){
            i = 0;
         }
     }
    }
    this->storedItems++;
    this->currSize = this->table.size();
}


Process * ProcessTable::remove(unsigned int pid){
    int index = this->hash(pid) % this->currSize;
    if (this->table[index]->getPid() == pid)
    {
        Process * tmp = this->table[index];
        this->table[index] = NULL;
        return tmp;
    }else{
       for (size_t i = 0; i < this->currSize; i++)
       {
            if (this->table[i]->getPid() == pid)
            {
                 Process * tmp = this->table[i];
                this->table[i] = NULL;
                return tmp;
            }
       }
    }
    this->storedItems--;
}
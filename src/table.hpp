#include <vector>
#include "PCB.hpp"
#ifndef PROCESSTABLE
#define PROCESSTABLE
class ProcessTable
{
private:
    int nextPrime(int n);
    std::vector<Process *> table;
    int hash(unsigned int pid);
    void resize();
    int checkCollision(int index);
    int currSize;
    bool isPrime(int n);
    double loadFactor;
    int storedItems;

public:
    ProcessTable();
    ~ProcessTable();
    void put(Process *Process);
    Process *remove(unsigned int pid);
    int size();
};

#endif

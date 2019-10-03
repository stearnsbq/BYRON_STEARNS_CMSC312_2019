#include <vector>
#include "PCB.hpp"
#ifndef PROCESSTABLE
#define PROCESSTABLE
class ProcessTable
{
private:
    unsigned int nextPrime(unsigned int n);
    std::vector<Process *> table;
    unsigned int hash(unsigned int pid);
    void resize();
    bool checkCollision(unsigned int index);
    unsigned int currSize;
    bool isPrime(unsigned int n);
    double loadFactor;
    unsigned int storedItems;

public:
    ProcessTable();
    ~ProcessTable();
    void put(Process *Process);
    Process *remove(unsigned int pid);
    int size();
};

#endif

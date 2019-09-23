#include <vector>
#include "Process.hpp"
#ifndef PROCESSTABLE
#define PROCESSTABLE
class ProcessTable
{
private:
    std::vector<Process *> table;
    int hash(unsigned int pid);
    void resize();
    int checkCollision(int index);
    int currSize;

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

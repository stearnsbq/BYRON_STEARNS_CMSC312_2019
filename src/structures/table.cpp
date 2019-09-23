#include "table.hpp"
#include <cmath>
#include <cstddef>
using namespace std;
ProcessTable::ProcessTable()
{
    this->table.reserve(41);
    this->currSize = this->table.size();
}

ProcessTable::~ProcessTable()
{
    this->table.clear();
}

int ProcessTable::hash(unsigned int pid)
{
    return pid * 2654435761 % (int)pow(2, 32);
}

int ProcessTable::checkCollision(int index)
{
    if (this->table[index])
    {
        return 1;
    }
    return 0;
}

void ProcessTable::resize()
{
    this->table.resize((this->currSize * 2) + 1);
    this->currSize = this->table.size();
}

void ProcessTable::put(Process *Process)
{
    if (this->loadFactor >= 0.75)
    {
        this->resize();
    }

    int hash = this->hash(Process->getPid());
    int index = hash % this->currSize;
    if (!checkCollision(index))
    {
        this->table[index] = Process;
    }
    else
    {
        while (this->table[index] != NULL)
        {
            hash++;
            index = hash % this->currSize;
        }
        this->table[index] = Process;
    }
    this->storedItems++;
    this->currSize = this->table.size();
    this->loadFactor = (double)this->table.size() / (double)this->storedItems;
}

Process *ProcessTable::remove(unsigned int pid)
{
    int hash = this->hash(pid);
    int index = hash % this->currSize;
    if (this->table[index]->getPid() == pid)
    {
        Process *tmp = this->table[index];
        this->table[index] = NULL;
        return tmp;
    }
    else
    {
        while (this->table[index]->getPid() != pid)
        {
            hash++;
            index = hash % this->currSize;
        }

        Process *tmp = this->table[index];
        this->table[index] = NULL;
    }
    this->storedItems--;
    this->loadFactor = (double)this->table.size() / (double)this->storedItems;
}
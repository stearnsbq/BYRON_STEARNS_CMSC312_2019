#ifndef MUTEX_H
#define MUTEX_H
#include <chrono>
#include <ctime>

class mutex
{
public:
mutex();
int lock();
void unlock();
private:
bool isLocked;
};

#endif // MUTEX_H

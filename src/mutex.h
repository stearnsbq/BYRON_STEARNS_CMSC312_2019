#ifndef MUTEX_H
#define MUTEX_H
#include <chrono>
#include <ctime>
#include <mutex>

class mutex
{
public:
mutex();
int lock();
void unlock();
private:
bool isLocked;
std::mutex _mut;
};

#endif // MUTEX_H

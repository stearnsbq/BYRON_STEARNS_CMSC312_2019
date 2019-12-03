#ifndef RESOURCE_H
#define RESOURCE_H
#include <vector>
#include <PCB.hpp>
class Resource
{
public:

struct AbstractResource {
    std::string data;
    bool beingUsed;
};

Resource(int count);
Resource();
void release(AbstractResource * res);
std::pair<bool, AbstractResource *> tryAcquire();
private:
int instanceCount;
AbstractResource * acquire();
std::vector<AbstractResource *> instances;
};

#endif // RESOURCE_H

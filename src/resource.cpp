#include "resource.h"
#include <utility>
Resource::Resource()
{

}

Resource::Resource(int count)
{
    this->instanceCount = count;
}

std::pair<bool, Resource::AbstractResource *> Resource::tryAcquire(){
    AbstractResource * e;

    return std::make_pair((e = this->acquire()) != nullptr, e);

}

Resource::AbstractResource * Resource::acquire(){
    std::vector<AbstractResource *>::iterator finder = std::find_if(instances.begin(), instances.end(), [](AbstractResource * e){
        return !e->beingUsed;
    });

    AbstractResource * found = *finder;
    found->beingUsed = true;
    return found;
}


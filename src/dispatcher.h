#ifndef DISPATCHER_H
#define DISPATCHER_H


class Core;
class Dispatcher
{
public:
Dispatcher(Core & parent);
~Dispatcher();
private:
Core & parent;
};

#endif // DISPATCHER_H

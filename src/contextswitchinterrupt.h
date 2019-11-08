#ifndef CONTEXTSWITCHINTERRUPT_H
#define CONTEXTSWITCHINTERRUPT_H
#include "interrupt.h"

class contextswitchinterrupt : public interrupt
{
public:
contextswitchinterrupt();
INTERRUPT_TYPE getType();
~contextswitchinterrupt();
private:
void handler() override;
INTERRUPT_TYPE type;
};

#endif // CONTEXTSWITCHINTERRUPT_H

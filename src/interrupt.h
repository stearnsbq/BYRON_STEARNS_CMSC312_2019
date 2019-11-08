#ifndef INTERRUPT_H
#define INTERRUPT_H

enum INTERRUPT_TYPE {
    IO_INTR,CONTEXT_SWITCH
};


class interrupt
{
public:
interrupt();
virtual ~interrupt();
private:
virtual void handler();

};

#endif // INTERRUPT_H

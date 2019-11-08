#include "contextswitchinterrupt.h"
#include "CPU.hpp"

contextswitchinterrupt::contextswitchinterrupt()
{

}

contextswitchinterrupt::~contextswitchinterrupt(){

}

void contextswitchinterrupt::handler()  {


}

INTERRUPT_TYPE contextswitchinterrupt::getType(){
    return this->type;
}

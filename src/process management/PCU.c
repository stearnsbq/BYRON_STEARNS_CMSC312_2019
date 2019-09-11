#include <stdio.h>
#include "../structures/queue.h"
#include "PCU.h"

void main(int argc, char **argv)
{
    Heap *heap = NULL;
    ProcessBlock process1;
    process1.priority = 1;
    process1.state = NEW;
    process1.pid = 21451;
    ProcessBlock process2;
    process2.priority = 5;
    process2.state = NEW;
    process2.pid = 21452;
    ProcessBlock process3;
    process3.priority = 12;
    process3.state = NEW;
    process3.pid = 21453;
    ProcessBlock process4;
    process4.priority = 9;
    process4.state = NEW;
    process4.pid = 21454;
    ProcessBlock process5;
    process5.priority = 50;
    process5.state = NEW;
    process5.pid = 21455;
    ProcessBlock process6;
    process6.priority = 0;
    process6.state = NEW;
    process6.pid = 21456;
    ProcessBlock process7;
    process7.priority = 75;
    process7.state = NEW;
    process7.pid = 21457;
    ProcessBlock process8;
    process8.priority = 41;
    process8.state = NEW;
    process8.pid = 21458;
    ProcessBlock process9;
    process9.priority = 38;
    process9.state = NEW;
    process9.pid = 21459;
    ProcessBlock process10;
    process10.priority = 30;
    process10.state = NEW;
    process10.pid = 21460;
    ProcessBlock process11;
    process11.priority = 11;
    process11.state = NEW;
    process11.pid = 21461;
    addProcess(&heap, &process1);
    addProcess(&heap, &process2);
    addProcess(&heap, &process3);
    addProcess(&heap, &process4);
    addProcess(&heap, &process5);
    addProcess(&heap, &process6);
    addProcess(&heap, &process7);
    addProcess(&heap, &process8);
    addProcess(&heap, &process9);
    addProcess(&heap, &process10);
    //print(heap);
    ProcessBlock t = removeProcess(&heap);
    ProcessBlock t2 = removeProcess(&heap);
    print(heap);
}

#ifndef FEEDBACKQUEUE_H
#define FEEDBACKQUEUE_H
#include "queue.hpp"
#include "PCB.hpp"

class FeedbackQueue
{
public:
    FeedbackQueue();
    ~FeedbackQueue();
    Process getNextProcess();
private:
    Queue topLevel;
    Queue midLevel;
    Queue baseLevel;
};

#endif // FEEDBACKQUEUE_H

#include <exception>

using namespace std;

class EmptyQueueException : public exception
{
    const char *what() const throw()
    {
        return "Queue is Empty!";
    };
};
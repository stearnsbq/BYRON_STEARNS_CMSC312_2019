#include "../process management/PCU.h"
typedef struct Node
{
    ProcessBlock data;
    Node *next;
} Node;
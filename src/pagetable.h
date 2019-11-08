#ifndef PAGETABLE_H
#define PAGETABLE_H
#include "page.h"
#include "CPU.hpp"
#include <vector>
class pagetable
{
public:
pagetable();
~pagetable();
page putPage(int pageNumber);
page * removePage(int pageNumber);
std::vector<int> getPages();
private:
unsigned int size;
unsigned int storedPages;
double loadFactor;
std::vector<std::vector<page *> > pages;
unsigned int getNextPrime(int num);
bool isPrime(int num);
void resize();
unsigned int hash(unsigned int num);
};

#endif // PAGETABLE_H

#ifndef PAGETABLE_H
#define PAGETABLE_H
#include "page.h"
#include <vector>
class pagetable
{
public:
pagetable();
~pagetable();
void putPage(int pageNumber, int frameNumber);
page * removePage(int pageNumber);
std::vector<int> getPages();
private:
unsigned int size;
unsigned int storedPages;
double loadFactor;
std::vector<std::vector<page *>> pages;
unsigned int getNextPrime(int num);
bool isPrime(int num);
void resize();
unsigned int hash(int num);
};

#endif // PAGETABLE_H

#ifndef PAGETABLE_H
#define PAGETABLE_H
#include "page.h"
#include "CPU.hpp"
#include <vector>
#include <unordered_map>
class pagetable
{
public:
pagetable();
~pagetable();
page putPage(int pageNumber);
page removePage(int pageNumber);
int findPageToReplace();
std::unordered_map<int, page> pages;
private:
unsigned int size;
unsigned int storedPages;
double loadFactor;

};

#endif // PAGETABLE_H

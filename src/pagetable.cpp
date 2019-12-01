#include "pagetable.h"
#include <cmath>


pagetable::pagetable()
{
    this->loadFactor = 0.75;
    this->size = 757;
    this->storedPages = 0;
}

pagetable::~pagetable(){
    this->pages.clear();
}


page pagetable::putPage(int pageNumber){

    page newPage = page(pageNumber);
    newPage.setFrameNumber(CPU::getInstance().getNextOpenFrame());
    newPage.setInMemory(true);
    this->pages.insert(std::make_pair(pageNumber,  newPage));
    this->storedPages++;
    return newPage;
}

page pagetable::removePage(int pageNumber){
    page *find;
    if((find = &this->pages[pageNumber]) != nullptr) {
        return *find;
    }
}

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
    int frameNumber = CPU::getInstance().getNextOpenFrame();
    if(frameNumber < 0) {
        int newFrameNumber = this->findPageToReplace();
        newPage.setFrameNumber(newFrameNumber);
        kernel::getInstance().window->setMemoryGraphic(newFrameNumber, true);
    }else{
        newPage.setFrameNumber(frameNumber);
        kernel::getInstance().window->setMemoryGraphic(frameNumber, true);
    }


    newPage.setInMemory(true);
    this->pages.insert(std::make_pair(pageNumber,  newPage));
    this->storedPages++;
    return newPage;
}


int pagetable::findPageToReplace(){
    for(auto it = this->pages.begin(); it != this->pages.end(); it++) {
        page tmp = it->second;
        if(!tmp.isDirty()) {
            it->second.setFrameNumber(-1);
            return tmp.getFrameNumber();
        }
    }
}

page pagetable::removePage(int pageNumber){
    page *find;
    if((find = &this->pages[pageNumber]) != nullptr) {
        return *find;
    }
}

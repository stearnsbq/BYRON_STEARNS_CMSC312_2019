#include "mainmemory.h"
#include <cmath>

mainmemory::mainmemory(unsigned int totalMemory, double pageSize)
{
    this->pageSize = pageSize;
    this->usedFrames = 0;
    this->pageTable = new pagetable();
    this->totalMemory = totalMemory;
    unsigned int frameCount = std::ceil((double)this->totalMemory / this->pageSize);
    this->totalFrames = frameCount;
    this->frames.reserve(frameCount);
    this->nextFrame = frameCount-1;
    for(int i = frameCount-1; i >= 0; i--) {
        this->frames.push_back({i, true});
        this->emptyFrames.push({i, true});
    }
}



std::vector<page> mainmemory::allocateMemory(size_t size){

    std::vector <page> pages;
    unsigned int amountOfPages = std::ceil((double)size/this->pageSize);
    this->usedFrames += amountOfPages;
    for(unsigned int i = 0; i < amountOfPages; i++) {
        unsigned int pageNumber = CPU::getInstance().getNextLogicalAddr() / this->pageSize;
        pages.push_back(this->pageTable->putPage(pageNumber));
        emit kernel::getInstance().window->updateMemoryBarGUI(this->pageSize);
    }

    return pages;
}

unsigned int mainmemory::availableMemory(){

    return this->totalMemory - (this->usedFrames * this->pageSize);
}


void mainmemory::setPagesDirty(std::vector<page>& pages){
    for(auto it = pages.begin(); it != pages.end(); it++) {
        if(it->getFrameNumber() >= 0) {
            this->pageTable->pages.at(it->getPageNumber()).setDirty(!this->pageTable->pages.at(it->getPageNumber()).isDirty());
        }else{
            // page fault
            std::replace(pages.begin(), pages.end(), *it, this->pageTable->putPage(it->getPageNumber()));

        }
    }
}


void mainmemory::freeMemory(std::vector<page> pages){
    for(int i = 0; i < pages.size(); i++) {
        frame &tmp = this->frames.at(pages[i].getFrameNumber());
        this->pageTable->removePage(pages[i].getPageNumber());
        emit kernel::getInstance().window->updateMemoryBarGUI(-this->pageSize);
        tmp.free = true;
        this->emptyFrames.push(tmp);
        kernel::getInstance().window->setMemoryGraphic(pages[i].getFrameNumber(), false);
    }

}

int mainmemory::getNextFrame(){
    if(this->emptyFrames.empty()) {
        return -1;
    }else{
        frame newFrame = this->emptyFrames.top();
        this->emptyFrames.pop();
        return newFrame.num;
    }

}

bool comparePages(page * p1, page * p2)
{
    return (p1->getPageNumber() < p2->getPageNumber());
}





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
    for(unsigned int i = frameCount-1; i > 0; i--) {
        this->frames.push_back({i, true});
        this->emptyFrames.push({i, true});
    }
}



std::vector<page> mainmemory::allocateMemory(size_t size){
    std::lock_guard<std::mutex>(this->_mutex);

    std::vector <page> pages;
    unsigned int amountOfPages = std::ceil((double)size/this->pageSize);
    this->usedFrames += amountOfPages;
    for(int i = 0; i < amountOfPages; i++) {
        unsigned int pageNumber = CPU::getInstance().getNextLogicalAddr() / this->pageSize;
        pages.push_back(this->pageTable->putPage(pageNumber));
    }
    return pages;
}

unsigned int mainmemory::availableMemory(){
    std::lock_guard<std::mutex>(this->_mutex);
    return this->totalMemory - (this->usedFrames * this->pageSize);
}


void mainmemory::freeMemory(std::vector<page> pages){
    std::lock_guard<std::mutex>(this->_mutex);
    for(int i = 0; i < pages.size(); i++) {
        frame &tmp = this->frames.at((this->emptyFrames.size() - 1) - pages[i].getFrameNumber());
        this->pageTable->removePage(pages[i].getPageNumber());
        tmp.free = true;
        this->emptyFrames.push(tmp);
    }
}

unsigned int mainmemory::getNextFrame(){
    std::lock_guard<std::mutex>(this->_mutex);
    frame newFrame = this->emptyFrames.top();
    this->emptyFrames.pop();
    return newFrame.num;
}

bool comparePages(page * p1, page * p2)
{
    return (p1->getPageNumber() < p2->getPageNumber());
}

page * mainmemory::tlbSearch(int pageNum, int l = 0, int h = 0){   // basic binary search of tlb
    if(l < h) {
        return nullptr; // miss
    }else{
        std::sort(this->TLB.begin(), this->TLB.end(), comparePages);
        unsigned int mid = (l + h) / 2;
        if(pageNum == this->TLB.at(mid)->getPageNumber()) {
            return this->TLB.at(mid); // hit
        }else if(pageNum < this->TLB.at(mid)->getPageNumber()) {
            return tlbSearch(pageNum, l, mid-1);
        }else{
            return tlbSearch(pageNum, mid+1, h);
        }
    }

}



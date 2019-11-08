#include "mainmemory.h"
#include <cmath>

mainmemory::mainmemory(int totalMemory, double pageSize)
{
    this->pageSize = pageSize;
    this->usedFrames = 0;
    this->pageTable = new pagetable();
    this->totalMemory = totalMemory;
    unsigned int frameCount = std::ceil((double)this->totalMemory / this->pageSize);
    this->totalFrames = frameCount;
    this->emptyFrames.reserve(frameCount);
    this->nextFrame = frameCount-1;
    for(int i = frameCount-1; i >= 0; i--) {

        this->emptyFrames.push_back({i, true});
    }
}



std::vector<page> mainmemory::allocateMemory(size_t size){
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
    return this->totalMemory - (this->usedFrames * this->pageSize);
}


void mainmemory::freeMemory(std::vector<page> pages){
    for(int i = 0; i < pages.size(); i++) {
        this->emptyFrames.at((this->emptyFrames.size() - 1) - pages[i].frameNumber).free = true;
    }
}


unsigned int mainmemory::getNextFrame(){
    for(int i = this->emptyFrames.size()-1; i >= 0; i--) {
        if(this->emptyFrames[i].free) {
            this->emptyFrames[i].free = false;
            return this->emptyFrames[i].num;
        }
    }
}

bool comparePages(page * p1, page * p2)
{
    return (p1->pageNumber < p2->pageNumber);
}

page * mainmemory::tlbSearch(int pageNum, int l = 0, int h = 0){   // basic binary search of tlb
    if(l < h) {
        return nullptr; // miss
    }else{
        std::sort(this->TLB.begin(), this->TLB.end(), comparePages);
        unsigned int mid = (l + h) / 2;
        if(pageNum == this->TLB.at(mid)->pageNumber) {
            return this->TLB.at(mid); // hit
        }else if(pageNum < this->TLB.at(mid)->pageNumber) {
            return tlbSearch(pageNum, l, mid-1);
        }else{
            return tlbSearch(pageNum, mid+1, h);
        }
    }

}



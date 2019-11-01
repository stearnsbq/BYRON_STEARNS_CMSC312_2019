#include "mainmemory.h"
#include <cmath>

mainmemory::mainmemory(int totalMemory, double pageSize)
{
    this->pageSize = pageSize;
    unsigned int frameCount = std::ceil((double)totalMemory / this->pageSize);
    this->totalFrames = frameCount;
    this->emptyFrames.reserve(frameCount);

    for(int i = frameCount-1; i >= 0; i--) {

        this->emptyFrames.push_back({i, true});

    }
}

void mainmemory::allocateMemory(Process &process){

    int pageCount = std::ceil(process.getMemoryReq() / this->pageSize);

    int pNum = 0;

    pagetable * table = process.getPTable();

    int baseFrame = this->emptyFrames.back().num;

    for(int i = 0; i < pageCount; i++) {

        this->emptyFrames.at(baseFrame).free = false;

        table->putPage(pNum++, baseFrame--);

    }
}

void mainmemory::freeMemory(Process &process){
    std::vector<int> frames = process.getPTable()->getPages();
    for(int i = 0; i < frames.size(); i++) {
        this->emptyFrames.at(frames.at(i)).free = true;
    }
}

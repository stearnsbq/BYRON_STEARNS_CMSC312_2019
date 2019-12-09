#include "page.h"

page::page(int pageNumber)
{
    this->pageNumber = pageNumber;
    this->inMemory = true;
    this->dirty = 0;
    this->lastUsed = 0;
    this->timeInMemory = 0;
    this->frameNumber = -1;
}

page::page(){
    this->pageNumber = -1;
    this->inMemory = false;
    this->dirty = 0;
    this->lastUsed = 0;
    this->timeInMemory = 0;
    this->frameNumber = -1;

}


bool page::operator==(const page & p){
    return this->pageNumber == p.pageNumber;
}

page::~page(){

}

bool page::isInMemory(){
    return this->inMemory;
}

int page::getPageNumber(){
    return this->pageNumber;
}

int page::getFrameNumber(){
    return this->frameNumber;
}

void page::setPageNumber(int number){
    this->pageNumber = number;
}

void page::setFrameNumber(int number){
    this->frameNumber = number;
}

void page::setInMemory(bool is){
    this->inMemory = is;
}

bool page::isDirty(){
    return this->dirty;
}

void page::setDirty(bool d){
    this->dirty = d;
}

#include "page.h"

page::page(int pageNumber)
{
    this->pageNumber = pageNumber;
    this->inMemory = true;
    this->frameNumber = -1;
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

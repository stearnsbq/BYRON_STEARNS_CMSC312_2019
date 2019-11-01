#include "pagetable.h"
#include <cmath>
pagetable::pagetable()
{
    this->loadFactor = 0.75;
    this->size = 757;
    this->pages.reserve(this->size);
}


unsigned int pagetable::getNextPrime(int num){

    unsigned int val = num;

    while(!isPrime(val)) {

        val++;

    }

    return val;

}


std::vector<int> pagetable::getPages(){
    std::vector<int> frames;
    for(int i = 0; i < this->pages.size(); i++) {
        if(this->pages.at(i).size() > 0) {
            for(int j = 0; j < this->pages.at(i).size(); j++) {
                frames.push_back(this->pages.at(i).at(j)->frameNumber);
            }
        }
    }
}

bool pagetable::isPrime(int num){

    for(int i = 2; i <= num/2; i++) {

        if(num % i == 0) {

            return false;

        }

    }

    return true;

}

void pagetable::resize(){

    this->pages.resize(this->getNextPrime(this->pages.size()));

    this->size = this->pages.size();

}

unsigned int pagetable::hash(int num){

    return num * 2654435761 % (int)std::pow(2, 32);

}

void pagetable::putPage(int pageNumber, int frameNumber){
    unsigned int index = this->hash(pageNumber) % this->size;

    page * newPage = new page(pageNumber);
    newPage->frameNumber = frameNumber;
    newPage->inMemory = true;
    this->pages.at(index).push_back(newPage);

    if(this->pages.size() / this->storedPages >= 0.75) {

        this->resize();

    }
}

page * pagetable::removePage(int pageNumber){
    unsigned int index = this->hash(pageNumber) % this->size;

    std::vector<page *> chain = this->pages.at(index);

    unsigned int length = chain.size();

    for(unsigned int i = 0; i < length; i++) {

        if(chain.at(i)->pageNumber == pageNumber) {

            return chain.at(i);

        }
    }
    return nullptr;
}

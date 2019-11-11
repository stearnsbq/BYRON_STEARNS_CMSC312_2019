#include "pagetable.h"
#include <cmath>
pagetable::pagetable()
{
    this->loadFactor = 0.75;
    this->size = 757;
    this->storedPages = 0;
    this->pages.resize(this->size);
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
                frames.push_back(this->pages.at(i).at(j)->getPageNumber());
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

unsigned int pagetable::hash(unsigned int a){

    return (a * 2654435769 >> 32);

}

page pagetable::putPage(int pageNumber){
    unsigned int index = this->hash(pageNumber) % this->size;

    page * newPage = new page(pageNumber);
    newPage->setPageNumber(CPU::getInstance().getNextOpenFrame());
    newPage->setInMemory(true);
    this->pages.at(index).push_back(newPage);
    this->storedPages++;
    if((this->storedPages / this->pages.size()  ) >= 0.75) {

        this->resize();

    }
    return *newPage;
}

page * pagetable::removePage(int pageNumber){
    unsigned int index = this->hash(pageNumber) % this->size;

    std::vector<page *> chain = this->pages.at(index);

    unsigned int length = chain.size();

    for(unsigned int i = 0; i < length; i++) {

        if(chain.at(i)->getPageNumber() == pageNumber) {
            return chain.at(i);
        }
    }
    std::remove_if(chain.begin(), chain.end(), [pageNumber](page* x) {
        return x->getPageNumber() == pageNumber;
    });
    return nullptr;
}

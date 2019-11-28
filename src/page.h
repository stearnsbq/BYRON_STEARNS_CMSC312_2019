#ifndef PAGE_H
#define PAGE_H


class page
{
public:
page(int pageNumber);
page();
~page();
bool isInMemory();
int getPageNumber();
int getFrameNumber();
void setPageNumber(int number);
void setFrameNumber(int number);
void setInMemory(bool is);
void setDirty(bool d);
bool isDirty();
private:
int pageNumber;
int frameNumber;
bool inMemory;
int timeInMemory;
bool dirty;
unsigned int lastUsed;
};

#endif // PAGE_H

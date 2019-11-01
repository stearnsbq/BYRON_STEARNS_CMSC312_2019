#ifndef PAGE_H
#define PAGE_H


class page
{
public:
    page(int pageNumber);
    ~page();
    int pageNumber;
    int frameNumber;
    bool inMemory;
    int timeInMemory;
private:
    bool isInMemory();
    int getPageNumber();
    int getFrameNumber();
    void setPageNumber(int number);
    void setFrameNumber(int number);
    void setInMemory(bool is);
};

#endif // PAGE_H

#include "mailbox.h"

mailbox::mailbox()
{

}

void mailbox::newMessage(std::string msg, int origin){
    std::lock_guard<std::mutex> lock(_mailMutex);
    message msgToSend = {msg, origin};
    this->msgQueue.push(msgToSend);
}

mailbox::message mailbox::recieveMessage(){
    std::lock_guard<std::mutex> lock(_mailMutex);
    message tmp = this->msgQueue.front();
    this->msgQueue.pop();
    return tmp;
}

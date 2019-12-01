#ifndef MAILBOX_H
#define MAILBOX_H
#include <queue>
#include <string>
#include <mutex>

class mailbox
{
public:
mailbox();
struct message {
    std::string msg;
    int originPid;
};
void newMessage(std::string msg, int origin);
message recieveMessage();
bool empty();
private:
std::queue<message> msgQueue;
std::mutex _mailMutex;
};

#endif // MAILBOX_H

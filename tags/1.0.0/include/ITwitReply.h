#ifndef ITWITREPLY_H
#define ITWITREPLY_H

#include "Server.h"

class ITwitReply
{
    public:
        virtual void OnError(std::string error) = 0;
        virtual void OnMessageReceived(std::string message) = 0;
        virtual void OnStatusReceived(SERVER::RESP response) = 0;
        virtual void OnLoginStatus(bool isLoggedIn) = 0;
};


#endif //ITWITREPLY_H

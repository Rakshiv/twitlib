#ifndef Returnables_H
#define Returnables_H

#include "Server.h"

namespace Returnable
{
    class Message
    {
        public:
            int id;
            SERVER::RESP svrResp;
            std::string strMessage;
        private:
            Message() {}
    };
    
    

};


#endif //Returnables_H

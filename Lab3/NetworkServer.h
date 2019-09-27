//
// Created by giova on 06/05/2019.
//

#ifndef LAB3_NETWORKSERVER_H
#define LAB3_NETWORKSERVER_H

#include "Message.h"
#include "vector"
#include "memory"
#include "queue"

class SharedEditor; //non mettiamo include perchè SharedEditor già fa '#include NetworkServer.h' -> rischio loop

class NetworkServer {

    private:
        std::vector<SharedEditor*> editors;
        std::queue<Message> messages;
        int editorId = 0;

    public:
        int connect(SharedEditor* sharedEditor);
        void disconnect (SharedEditor* sharedEditor);
        void send(const Message& m);
        void dispatchMessages();
        NetworkServer();
};


#endif //LAB3_NETWORKSERVER_H

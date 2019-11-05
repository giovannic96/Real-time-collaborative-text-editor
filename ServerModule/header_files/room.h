//
// Created by giova on 10/10/2019.
//

#ifndef SERVERMODULE_ROOM_H
#define SERVERMODULE_ROOM_H

#include <memory>
#include <string>
#include <set>
#include <deque>
#include <queue>
#include "participant.h"

typedef std::shared_ptr<participant> participant_ptr;
typedef std::deque<message> message_queue;
typedef std::queue<msgInfo> msgInfo_queue;

class room {

private:
    std::set<participant_ptr> participants_;
    enum { max_recent_msgs = 100 };
    message_queue recent_msgs_;
    msgInfo_queue infoMsgs_;

public:
    void join(participant_ptr participant);
    void leave(participant_ptr participant);
    void deliver(const message& msg); //deliver to the clients
    void send(const msgInfo& m);
    void dispatchMessages(); //dispatch to the participants

};


#endif //SERVERMODULE_ROOM_H

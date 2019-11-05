//
// Created by giova on 10/10/2019.
//

#include <iostream>
#include "header_files/room.h"

void room::join(participant_ptr participant) {
    participants_.insert(participant);
    for (auto msg: recent_msgs_)
        participant->deliver(msg);
}

void room::leave(participant_ptr participant) {
    participants_.erase(participant);
    std::cout << "participant leaved the room" << std::endl;
}

void room::deliver(const message &msg) {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    for (auto participant: participants_) //TODO: not send to same client:   if (it->getId() != messages.front().getEditorId())
        participant->deliver(msg);
}

void room::send(const msgInfo &m) {
    infoMsgs_.push(m);
}

void room::dispatchMessages() {
    while(!infoMsgs_.empty()) {
        for (auto it: participants_)
            if (it->getId() != infoMsgs_.front().getEditorId())
                it->process(infoMsgs_.front());
        infoMsgs_.pop();
    }
}




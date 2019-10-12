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

    for (auto participant: participants_)
        participant->deliver(msg);
}





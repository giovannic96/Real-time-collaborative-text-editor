//
// Created by giova on 10/10/2019.
//

#include <iostream>
#include "header_files/room.h"

void room::join(const participant_ptr& participant) {
    participants_.insert(participant);
    std::cout << "participant #" << participant->getId() << " joined the room" << std::endl;
    for (auto msg: recent_msgs_)
        participant->deliver(msg);
}

void room::leave(const participant_ptr& participant) {
    participants_.erase(participant);
    std::cout << "participant leaved the room" << std::endl;
}

void room::deliver(const message &msg) {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    for (const auto& p: participants_)
            p->deliver(msg);
}

void room::deliverToAll(const message &msg, const int& edId) {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    for (const auto& p: participants_) {
        if (p->getId() != edId) //don't send the message to the same client
            p->deliver(msg);
    }
}

void room::send(const msgInfo &m) {
    infoMsgs_.push_back(m);
}

void room::dispatchMessages() {
    while(!infoMsgs_.empty()) {
        for (const auto& it: participants_)
            if (it->getId() != infoMsgs_.front().getEditorId())
                it->process(infoMsgs_.front());
        infoMsgs_.pop_front();
    }
}

std::vector<symbol> room::getSymbolMap(const std::string& filename) {
    return room_map_.empty() ? std::vector<symbol>() : room_map_.at(filename);
}

std::map<std::string, std::vector<symbol>> room::getMap() {
    return this->room_map_;
}

void room::setEmptyMap(const std::string& key) {
    std::map<std::string, std::vector<symbol>> m = {{ key, { } }};
    this->room_map_ = m;
}

void room::setMap(const std::string &key, const std::vector<symbol>& symbols) {
    std::map<std::string, std::vector<symbol>> m = {{ key, symbols }};
    this->room_map_ = m;
}





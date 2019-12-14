//
// Created by giova on 10/10/2019.
//

#include <iostream>
#include "header_files/room.h"
#include "header_files/fileUtility.h"

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

void room::deliverToAll(const message &msg, const int& edId, const std::string& curFile, bool includeThisEditor) {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    if(!includeThisEditor) {
        for (const auto& p: participants_) {
            if (p->getId() != edId && p->getCurrentFile() == curFile) //don't send the message to the same client and don't send to clients having other file opened
                p->deliver(msg);
        }
    } else {
        for (const auto& p: participants_) {
            if (p->getCurrentFile() == curFile) { //don't send the message to the clients having other file opened
                p->deliver(msg);
            }
        }
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
    if(room_map_.empty()) //server has nothing in RAM
        return std::vector<symbol>();
    if(room_map_.at(filename).empty()) //server has not in RAM the vector symbols for this filename
        return fileUtility::readFile(R"(..\Filesystem\)" + filename + ".txt");
    else //server has already in RAM this vector symbols
        return room_map_.at(filename);
}

std::map<std::string, std::vector<symbol>> room::getMap() {
    return this->room_map_;
}

void room::updateMap(const std::string &key, const std::vector<symbol>& symbols) {
    this->room_map_[key] = symbols; //overwrite symbols in that key(uri)
}

void room::setMap(const std::map<std::string, std::vector<symbol>>& m) {
    this->room_map_ = m;
}

void room::addEntryInMap(const std::string &key, const std::vector<symbol> &symbols) {
    this->room_map_.emplace(key, symbols);
}





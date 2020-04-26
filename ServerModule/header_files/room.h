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
#include <map>
#include "participant.h"

typedef std::shared_ptr<participant> participant_ptr;
typedef std::deque<message> message_queue;
typedef std::deque<msgInfo> msgInfo_queue;

class room {

private:
    std::set<participant_ptr> participants_;
    enum { max_recent_msgs = 100 };
    message_queue recent_msgs_;
    msgInfo_queue infoMsgs_;
    std::map<std::string, std::vector<symbol>> room_map_;

public:
    void join(const participant_ptr& participant);
    void leave(const participant_ptr& participant);
    void deliver(const message& msg); //deliver to the clients
    void deliverToAll(const message& msg, const int& edId, const std::string& curFile, bool includeThisEditor=false); //deliver to the clients except the client with id 'edId'
    void send(const msgInfo& m);
    void dispatchMessages(); //dispatch to the participants
    std::map<std::string, std::vector<symbol>> getMap();
    void updateMap(const std::string& key, const std::vector<symbol>& symbols);
    void addEntryInMap(const std::string& key, const std::vector<symbol>& symbols);
    void insertInSymbolMap(const std::string &key, int index, const symbol& s);
    void eraseInSymbolMap(const std::string &key, int index);
    void formatInSymbolMap(const std::string &key, int index, int format);
    void changeFontSizeInSymbolMap(const std::string &key, int index, int fontSize);
    void changeFontFamilyInSymbolMap(const std::string &key, int index, const std::string& fontFamily);
    void changeAlignmentInSymbolMap(const std::string &key, int index, int alignment);
    void updateSymbolsMap(const std::string &key, int index, const std::vector<symbol>& symbols);
    void setMap(const std::map<std::string, std::vector<symbol>>& m);
    std::vector<symbol> getSymbolMap(const std::string& filename, bool canReadFromFile);
};


#endif  //SERVERMODULE_ROOM_H

//
// Created by giova on 06/05/2019.
//

#include "NetworkServer.h"
#include "SharedEditor.h"
#include <algorithm>

NetworkServer::NetworkServer() = default;

int NetworkServer::connect(SharedEditor *sharedEditor) {
    editors.push_back(sharedEditor);
    return ++editorId;
}

void NetworkServer::disconnect(SharedEditor *sharedEditor) {
    editors.erase(std::remove_if(editors.begin(), editors.end(),  [sharedEditor](SharedEditor* i) {return i->getId() == sharedEditor->getId();}), editors.end());
}

void NetworkServer::send(const Message &m) {
    messages.push(m);
}

void NetworkServer::dispatchMessages() {
    while(!messages.empty()) {
        for (auto it: editors)
            if (it->getId() != messages.front().getEditorId())
                it->process(messages.front());
        messages.pop();
    }
}

//
// Created by giova on 10/10/2019.
//

#ifndef SERVERMODULE_PARTICIPANT_H
#define SERVERMODULE_PARTICIPANT_H


#include "message.h"

class participant {

public:
    virtual ~participant() {}
    virtual void deliver(const message& msg) = 0;

};


#endif //SERVERMODULE_PARTICIPANT_H

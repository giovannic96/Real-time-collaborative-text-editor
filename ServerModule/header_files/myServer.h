//
// Created by giova on 01/10/2019.
//

#ifndef SERVERMODULE_MYSERVER_H
#define SERVERMODULE_MYSERVER_H

#include "room.h"

using boost::asio::ip::tcp;

class myServer {

private:
    tcp::acceptor acceptor_;
    int editorCounter_;
    void accept_connection();

public:
    myServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint);
};


#endif //SERVERMODULE_MYSERVER_H

//
// Created by giova on 01/10/2019.
//

#ifndef SERVERMODULE_SESSION_H
#define SERVERMODULE_SESSION_H

#include "json.hpp"

using boost::asio::ip::tcp;
using json = nlohmann::json;

class session : public std::enable_shared_from_this<session> {

private:
    tcp::socket socket_;
    std::size_t max_length = 4096;
    json jdata_in;
    void do_read();
    void do_write(const json& jdata_out, std::size_t length);

public:
    explicit session(tcp::socket socket);
    void handle_accept();
};

#endif //SERVERMODULE_SESSION_H

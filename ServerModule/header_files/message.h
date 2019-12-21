//
// Created by giova on 10/10/2019.
//

#ifndef SERVERMODULE_MESSAGE_H
#define SERVERMODULE_MESSAGE_H

#include <string>

class message {

public:
    enum { header_length = 5 };
    enum { max_body_length = 65536 };
    message();
    const char* data() const;
    char* data();
    std::size_t length() const;
    const char* body() const;
    char* body();
    std::size_t body_length() const;
    void body_length(std::size_t new_length);
    bool decode_header();
    void encode_header();

private:
    char data_[header_length + max_body_length];
    std::size_t body_length_;

};


#endif //SERVERMODULE_MESSAGE_H

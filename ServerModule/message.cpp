//
// Created by giova on 10/10/2019.
//

#include <cstring>
#include "header_files/message.h"

message::message() : body_length_(0) {
}

const char *message::data() const {
    return data_;
}

char *message::data() {
    return data_;
}

std::size_t message::length() const {
    return header_length + body_length_;
}

const char *message::body() const {
    return data_ + header_length;
}

char *message::body() {
    return data_ + header_length;
}

std::size_t message::body_length() const {
    return body_length_;
}

void message::body_length(std::size_t new_length) {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
        body_length_ = max_body_length;
}

bool message::decode_header() {
    char header[header_length + 1] = "";
    std::strncat(header, data_, header_length);
    body_length_ = std::atoi(header);
    if (body_length_ > max_body_length)
    {
        body_length_ = 0;
        return false;
    }
    return true;
}

void message::encode_header() {
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(body_length_));
    std::memcpy(data_, header, header_length);
}

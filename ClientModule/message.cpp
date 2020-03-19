//
// Created by giova on 10/10/2019.
//
#include <QDebug>
#include <cstring>
#include "message.h"

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
}

char& message::isThisLastChunk() {
    return isLastChunk;
}

void message::setLastChunk(char val) {
    this->isLastChunk = val;
}

void message::decode_header() {
    char header[header_length + 2] = "";
    std::strncat(header, data_+1, header_length);
    body_length_ = std::atoi(header);
    this->setLastChunk(*data_);
}

void message::encode_header() {
    char header[header_length + 1] = "";
    std::sprintf(header, "%5d", static_cast<int>(body_length_));
    std::memcpy(data_+1, header, header_length);
}

message message::constructMsg(const std::string& chunkRequest, char isLastChunk) {
    //Send data (header and body)
    message msg;
    msg.setLastChunk(isLastChunk);
    msg.body_length(chunkRequest.size());
    std::memcpy(msg.body()+1, chunkRequest.data(), msg.body_length());
    msg.body_length(chunkRequest.size());
    msg.body()[msg.body_length()+1] = '\0';
    msg.encode_header();
    std::memcpy(msg.data(), &msg.isThisLastChunk(), 1);
    return msg;
}


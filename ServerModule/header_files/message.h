//
// Created by giova on 10/10/2019.
//

#ifndef SERVERMODULE_MESSAGE_H
#define SERVERMODULE_MESSAGE_H

#include <string>
#define MAX_CHUNK_LENGTH 65000

class message {

public:
    enum { header_length = 5 };
    message();
    const char* data() const;
    char* data();
    std::size_t length() const;
    const char* body() const;
    char* body();
    std::size_t body_length() const;
    void body_length(std::size_t new_length);
    void decode_header();
    void encode_header();
    char& isThisLastChunk();
    void setLastChunk(char val);
    static message constructMsg(const std::string& chunkResponse, char isLastChunk);

private:
    char data_[MAX_CHUNK_LENGTH + header_length + 1];
    std::size_t body_length_;
    char isLastChunk;

};


#endif //SERVERMODULE_MESSAGE_H

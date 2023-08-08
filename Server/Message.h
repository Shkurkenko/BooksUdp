#pragma once

#include "Config.h"
#include "Decoder.h"

enum class MessageType {
    JSON,
    TEXT,
};

class Message {
public:
    char buffer[CONFIG::BUFLEN_DEFAULT];
    MessageType _type;
public:
    Message(MessageType type) : _type(type) {}

public:
    void decode() {
        Decoder::decode(buffer);
    }

    void encode() {
        auto encoded = Decoder::multiplyString(buffer);
        this->clear();
        this->setMessage(encoded);
    }

    void clear() {
        memset(buffer, 0, sizeof(buffer));
    }

    void setMessage(std::string &message) {
        this->clear();
        if(message.size() <= CONFIG::BUFLEN_DEFAULT) {
            this->setMessage(message);
        }
        else {
            std::cout << "Message is too long..." << "\n";
        }
    }

    void setMessage(char* message) {
        this->clear();
        if(strlen(message) <= CONFIG::BUFLEN_DEFAULT) {
            for(size_t i = 0; i != strlen(message); ++i) {
                buffer[i] = message[i];
            }
        } 
        else {
            std:cout << "Message if too long..." << '\n';
        }
    }

    inline void setType(MessageType type) {
        _type = type;
    }
};

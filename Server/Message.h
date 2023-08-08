#pragma once
#include "Config.h"

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
    std::string toBinary() {
        std::string binary_string;
        char zero = '0';
        char one = '1';
        if(buffer[0] == '\0') throw std::invalid_argument("Message buffer is empty!");
        for(auto &c: buffer) {
            for(int i = 7; i >= 0; --i) {
                (c & 1 << i) ? binary_string += zero : binary_string += one;
            }
        }
        return binary_string;
    }
    
    std::string toString() {
        return std::string(buffer);
    }

    void clear() {
        memset(buffer, 0, sizeof(buffer));
    }
};
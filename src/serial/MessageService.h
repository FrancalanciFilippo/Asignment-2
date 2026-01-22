#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <Arduino.h>

enum MessageType {
    HANGAR,
    DRONE,
    DISTANCE,
    ERROR
};

class MessageService {

public:
    MessageService();
    void init();
    void sendMessage(MessageType type, const String& message);
    String getMessage();
    bool messageAvailable();
private:
    String msg;
    bool hasMessage;
    
};

#endif
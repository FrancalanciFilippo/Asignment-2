#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <Arduino.h>

class MessageService {

public:
    MessageService();
    void init();
    void sendMessage(const String& message);
    String getMessage();
    bool messageAvailable();
private:
    String msg;
    bool hasMessage;
    
};

#endif
#include "MessageService.h"

MessageService::MessageService(){
    hasMessage = false;
    msg = "";
}

void MessageService::init(){
    Serial.begin(9600);
    Serial.setTimeout(100);
}

bool MessageService::messageAvailable(){
    hasMessage = false;
    if(Serial.available() > 0){
        String temp = Serial.readStringUntil('\n');
        temp.trim();
        if(temp.length() > 0){
            msg = temp;
            hasMessage = true;
        }
    }
    return hasMessage;
}


String MessageService::getMessage(){
    if(hasMessage){
        hasMessage = false;
        return msg;
    }
    return "";
}

void MessageService::sendMessage(MessageType type, const String& message){
    Serial.println(String(type)+":"+message);
}

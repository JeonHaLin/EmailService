#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <map>

struct emailData {
    std::string sender;
    std::string receiver;
    std::string title;
    std::string content;
};

class EmailController {
private:
    std::map <std::string,emailData> emailDataMap;
public:
    EmailController() {};

    /*
    std::string getSender();
    std::string getReceiver();
    std::string getTitle();
    std::string getContent();

    void setSender(std::string);
    void setReceiver(std::string);
    void setTitle(std::string);
    void setContent(std::string);
    */

    virtual void sendMail(std::string);
    virtual bool receiveMail(std::string);
    virtual bool sentMail(std::string);
    virtual void fileRead(std::map<std::string, emailData>&);
    virtual void fileWrite(std::map<std::string, emailData>&);
    virtual void deleteSentMail(std::string);
    virtual void deleteReceiveMail(std::string);

};

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
    virtual void sentMail(std::string);
    virtual void sendMail(std::string);
    virtual void receiveMail(std::string);
    virtual void fileRead(std::map<std::string, emailData>&, std::ifstream&);
    virtual void fileWrite(std::map<std::string, emailData>&, std::ofstream&);
    virtual void deleteSentMail(std::string);
    virtual void deleteReceiveMail(std::string);

};
class EmailToMe :public EmailController {
    emailData mail;
public:
    void sendMail(std::string) override;
};
class BusinessEmail :public EmailController {
    emailData mail;
public:
    void setTitle(std::string);
    void setContent(std::string);
    void sendMail(std::string) override;
};
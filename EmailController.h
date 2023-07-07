#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
struct email {
    std::string sender;
    std::string receiver;
    std::string title;
    std::string content;
};

class EmailController {
private:
    email mail;
public:
    EmailController() {};
    EmailController(std::string);

    std::string getSender();
    std::string getReceiver();
    std::string getTitle();
    std::string getContent();

    void setSender(std::string);
    void setReceiver(std::string);
    void setTitle(std::string);
    void setContent(std::string);

    void sentMail(std::string);
    void sendMail();
    void receiveMail(std::string);

};
class EmailToMe :public EmailController {
private:
    email mail;
public:
    EmailToMe(std::string);
};
class EmailToCustomer :public EmailController {
private:
    email mail;
public:
    EmailToCustomer(std::string);
};
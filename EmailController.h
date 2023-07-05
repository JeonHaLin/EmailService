#pragma once
#include <string>

struct mail {
    std::string sender;
    std::string receiver;
    std::string title;
    std::string content;
};

class EmailController {
public:
    void sendMail();
    void recieveMail();
};
class EmailToMe :public EmailController {

};

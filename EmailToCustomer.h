#pragma once
#include "EmailController.h"

class EmailToCustomer :public EmailController {
    emailData mail;
public:
    void setTitle(std::string);
    void setContent(std::string);
    void sendMail(std::string) override;
};
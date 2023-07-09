#pragma once
#include "EmailController.h"

class EmailToMe :public EmailController {
    emailData mail;
public:
    void sendMail(std::string) override;
};
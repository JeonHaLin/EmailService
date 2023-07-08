#pragma once
#include <string>

class AccountController;
class EmailController;

class MainController{
private:
	std::string me;
	AccountController* acc;
	EmailController* mail;
public:
	MainController();
	~MainController();

	void start();
	void signUp();
	void logIn();
	void subMenu_normal();
	void subMenu_business();
	void findPW();
	void printUserList();
	void exitProgram();
	void BackOrDelete_sent();
	void BackOrDelete_receive();
	void deleteAccount();
};
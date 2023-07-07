#pragma once
#include <iostream>
#include <string>

class AccountController;
class EmailController;

class MainController{
private:
	std::string me = "";
	AccountController* acc;
	EmailController* mail;
public:
	MainController();
	~MainController();

	void start();
	void signUp();
	void logIn();
	void subMenu();
	void findPW();
	void printUserList();
	void exitProgram();

};
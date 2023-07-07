#include "EmailController.h"
#include <iostream>
#include <string>

EmailController::EmailController(std::string sender) {
	mail.sender = sender;
}

std::string EmailController::getSender() {
    return mail.sender;
}
std::string EmailController::getReceiver() {
    return mail.receiver;
}
std::string EmailController::getTitle() {
    return mail.title;
}
std::string EmailController::getContent() {
    return mail.content;
}

void EmailController::setSender(std::string sender) {
    mail.sender = sender;
}
void EmailController::setReceiver(std::string receiver) {
    mail.receiver = receiver;
}
void EmailController::setTitle(std::string title) {
    mail.title = title;
}
void EmailController::setContent(std::string content) {
    mail.content = content;
}

void EmailController::sendMail() {
	std::string r, t, c;

	std::cin.ignore(1000, '\n');
	std::cout << "From. " << mail.sender << std::endl;
	std::cout << "To. " << mail.receiver << std::endl;
	std::cout << "Title : ";
	std::getline(std::cin, t);
	std::cout << "Content : ";
	std::getline(std::cin, c);

	setReceiver(r);
	setTitle(t);
	setContent(c);

	std::ofstream fout;

	std::string fileName = +"./" + mail.sender + "_" + mail.receiver + ".txt";
	fout.open(fileName,std::ios::app);

	if (!fout) {
		std::cout << "Error!";
		return;
	}

	fout << "From. me"<< std::endl;
	fout << "To. me" << std::endl;
	fout << "Title : " << mail.title << std::endl;
	fout << "Content : " << mail.content << std::endl;
	fout << "-----------------" << std::endl;

	fout.close();
}
void EmailController::receiveMail(std::string me) {
	std::string fileName = +"./" + mail.sender + "_" + me + ".txt";
	std::ifstream fin(fileName);
	if (!fin) {
		std::cout << "The inbox is empty!" << std::endl;
		return;
	}

	std::string buff;
	while (std::getline(fin, buff)) { 
		std::cout << buff << std::endl;
	}

	fin.close();

}

EmailToMe::EmailToMe(std::string me) {
	mail.sender = me;
	mail.receiver = me;
}

EmailToCustomer::EmailToCustomer(std::string content) {
	mail.content = content;
}


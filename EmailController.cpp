#include "EmailController.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

/*
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
*/
void EmailController::sendMail(std::string me) {
	emailData mail;
	std::string r, t, c;

	std::cin.ignore(1000, '\n');
	std::cout << "From. " << me << std::endl;
	std::cout << "To. ";
	std::getline(std::cin, r);
	std::cout << "Title : ";
	std::getline(std::cin, t);
	std::cout << "Content : ";
	std::getline(std::cin, c);

	mail.sender = me;
	mail.receiver = r;
	mail.title = t;
	mail.content = c;

	std::ofstream fout;

	fout.open("./mailData.txt", std::ios::app);

	if (!fout) {
		std::cout << "Error!";
		return;
	}

	fout << mail.sender << '|';
	fout << mail.receiver << '|';
	fout << mail.title << '|';
	fout << mail.content << '|' << '\n';

	fout.close();

	std::cout << std::endl;
	std::cout << "The mail is sent successfully." << std::endl;
	std::cin.clear();
	Sleep(1000);
	system("cls");
}
bool EmailController::sentMail(std::string me) {
	bool found = false;

	fileRead(emailDataMap);

	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		std::string buff;
		if (it->second.sender == me) {
			std::cout << "From. : " << me << std::endl;
			std::cout << "To. " << it->second.receiver << std::endl;
			std::cout << "Title :  " << it->second.title << std::endl;
			std::cout << "Content : " << it->second.content << std::endl;
			found = true;
		}
	}
	if (!found) {
		std::cout << "It's empty!" << std::endl;
		return found;
	}
	return found;
}
bool EmailController::receiveMail(std::string me) {
	bool found = false;

	fileRead(emailDataMap);


	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		if (it->second.receiver == me) {
			std::cout << "From. " << it->second.sender << std::endl;
			std::cout << "To. : " << me << std::endl;
			std::cout << "Title :  " << it->second.title << std::endl;
			std::cout << "Content : " << it->second.content << std::endl;
			found = true;
		}
	}
	if (!found) {
		std::cout << "The inbox is empty!" << std::endl;
		return found;
	}
	return found;
}
void EmailController::fileRead(std::map<std::string, emailData>& m) {
	std::ifstream fin;
	fin.open("./mailData.txt");
	if (fin) {
		m.clear();
		std::string line;
		while (!fin.eof()) {
			std::getline(fin, line);

			std::string id;
			emailData data;

			std::istringstream iss(line);
			std::getline(iss, data.sender, '|');
			std::getline(iss, data.receiver, '|');
			std::getline(iss, data.title, '|');
			std::getline(iss, data.content, '|');

			std::string temp = data.sender;

			m.insert(std::make_pair(temp, data));
		}
		fin.close();
	}
	else {
		std::ofstream emptyFile("./mailData.txt");
		emptyFile.close();
	}
}
void EmailController::fileWrite(std::map<std::string, emailData>& m) {
	std::ofstream fout;
	fout.open("./mailData.txt");

	if (!fout) {
		std::cout << "Error!";
		return;
	}
	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		fout << it->second.sender << '|';
		fout << it->second.receiver << '|';
		fout << it->second.title << '|';
		fout << it->second.content << '|' << '\n';
	}
	fout.close();
}

void EmailController::deleteSentMail(std::string me) {

	fileRead(emailDataMap);

	emailDataMap.erase(me);

	fileWrite(emailDataMap);

	system("cls");
	for (int i = 0; i < 3; i++) {
		std::cout << ".";
		Sleep(500);
	}
	std::cout << std::endl;
	std::cout << "Successfully deleted." << std::endl;
}
void EmailController::deleteReceiveMail(std::string me) {

	fileRead(emailDataMap);

	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		if (it->second.receiver == me) {
			emailDataMap.erase(it->first);
		}
	}

	fileWrite(emailDataMap);

	system("cls");
	for (int i = 0; i < 3; i++) {
		std::cout << ".";
		Sleep(500);
	}
	std::cout << std::endl;
	std::cout << "Successfully deleted." << std::endl;
}
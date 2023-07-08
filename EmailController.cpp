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
	fout << mail.content << '|';

	fout.close();
}
void EmailController::sentMail(std::string me) {
	bool found = false;
	std::ifstream fin("./mailData.txt");
	if (!fin) {
		std::cout << "Datat loss error!" << std::endl;
		return;
	}
	fileRead(emailDataMap, fin);
	fin.close();

	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		std::string buff;
		if (it->second.sender == me) {
			std::cout << "To. " << it->second.receiver << std::endl;
			std::cout << "Title :  " << it->second.title << std::endl;
			std::cout << "Content : " << it->second.content << std::endl;
			found = true;
		}
	}
	if (!found) {
		std::cout << "It's empty!" << std::endl;
		return;
	}
}
void EmailController::receiveMail(std::string me) {
	bool found = false;
	std::ifstream fin("./mailData.txt");
	if (!fin) {
		std::cout << "Datat loss error!" << std::endl;
		return;
	}
	fileRead(emailDataMap, fin);
	fin.close();

	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		if (it->second.receiver == me) {
			std::cout << "From. " << it->second.sender << std::endl;
			std::cout << "Title :  " << it->second.title << std::endl;
			std::cout << "Content : " << it->second.content << std::endl;
			found = true;
		}
	}
	if (!found) {
		std::cout << "The inbox is empty!" << std::endl;
		return;
	}
}
void EmailController::fileRead(std::map<std::string, emailData>& m, std::ifstream& fin) {
	std::string line;
	emailDataMap.clear();

	if (fin) {
		while (std::getline(fin, line)) {

			std::string id;
			emailData* ED = new emailData;

			std::istringstream iss(line);
			std::getline(iss, ED->sender, '|');
			std::getline(iss, ED->receiver, '|');
			std::getline(iss, ED->title, '|');
			std::getline(iss, ED->content, '|');

			m.insert(make_pair(ED->sender, *ED));
			delete ED;
		}
	}
	else {
		std::ofstream emptyFile("./mailData.txt");
		emptyFile.close();
	}

}
void EmailController::fileWrite(std::map<std::string, emailData>& m, std::ofstream& fout) {

	fout.open("./mailData.txt");

	if (!fout) {
		std::cout << "Error!";
		return;
	}
	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		fout << it->first << '|';
		fout << it->second.receiver << '|';
		fout << it->second.title << '|';
		fout << it->second.content << '|';

	}

	fout.close();
}

void EmailController::deleteSentMail(std::string me) {
	std::ifstream fin("./mailData.txt");
	if (!fin) {
		std::cout << "Datat loss error!" << std::endl;
		return;
	}
	fileRead(emailDataMap, fin);
	fin.close();

	emailDataMap.erase(me);

	std::ofstream fout("./mailData.txt");
	fileWrite(emailDataMap, fout);
	fout.close();
}
void EmailController::deleteReceiveMail(std::string me) {
	std::ifstream fin("./mailData.txt");
	if (!fin) {
		std::cout << "Datat loss error!" << std::endl;
		return;
	}
	fileRead(emailDataMap, fin);
	fin.close();

	for (auto it = emailDataMap.begin(); it != emailDataMap.end(); it++) {
		if (it->second.receiver == me) {
			emailDataMap.erase(it->first);
		}
	}

	std::ofstream fout("./mailData.txt");
	fileWrite(emailDataMap, fout);
	fout.close();
}

void EmailToMe::sendMail(std::string me) {
	std::string t, c;

	std::cin.ignore(1000, '\n');
	std::cout << "From. " << me << std::endl;
	std::cout << "To. " << me << std::endl;
	std::cout << "Title : ";
	std::getline(std::cin, t);
	std::cout << "Content : ";
	std::getline(std::cin, c);

	mail.sender = me;
	mail.receiver = me;
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
	fout << mail.content << '|';

	fout.close();
}

void BusinessEmail::setTitle(std::string t) {
	this->mail.title = t;
}
void BusinessEmail::setContent(std::string c) {
	this->mail.content = c;
}

void BusinessEmail::sendMail(std::string me) {
	std::string r;

	std::cin.ignore(1000, '\n');
	std::cout << "From. " << me << std::endl;
	std::cout << "To. ";
	std::getline(std::cin, r);
	std::cout << "Title : " << mail.title;
	std::cout << "Content : " << mail.content;

	mail.receiver = r;

	std::ofstream fout;

	fout.open("./mailData.txt", std::ios::app);

	if (!fout) {
		std::cout << "Error!";
		return;
	}

	fout << mail.sender << '|';
	fout << mail.receiver << '|';
	fout << mail.title << '|';
	fout << mail.content << '|';

	fout.close();
}
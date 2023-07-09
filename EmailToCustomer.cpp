#include "EmailToCustomer.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

void EmailToCustomer::setTitle(std::string t) {
	this->mail.title = t;
}
void EmailToCustomer::setContent(std::string c) {
	this->mail.content = c;
}

void EmailToCustomer::sendMail(std::string me) {
	std::string r;

	std::cin.ignore(1000, '\n');
	std::cout << "From. " << me << std::endl;
	std::cout << "To. ";
	std::getline(std::cin, r);
	std::cout << "Title : " << mail.title << std::endl;
	std::cout << "Content : " << mail.content;

	mail.sender = me;
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
	fout << mail.content << '|' << '\n';

	fout.close();

	std::cout << std::endl;
	std::cout << "The mail is sent successfully." << std::endl;
	std::cin.clear();
	Sleep(1000);
	system("cls");
}
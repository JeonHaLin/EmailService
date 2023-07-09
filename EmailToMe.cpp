#include "EmailToMe.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>



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

	std::cout << std::endl;
	std::cout << "The mail is sent successfully." << std::endl;
	std::cin.clear();
	Sleep(1000);
	system("cls");
}
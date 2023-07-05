#include "MainController.h"
#include "AccountController.h"
#include "EmailController.h"
#include <Windows.h>
#include <fstream>

MainController::MainController() {
	acc = new AccountController;
	mail = new EmailController;
}
MainController::~MainController() {
	delete acc;
	delete mail;
}

void MainController::start() {

	int choice;

	while (true) {
		std::cout << "----Email Service----" << std::endl;
		std::cout << "1. Sign Up" << std::endl;
		std::cout << "2. Log In" << std::endl;
		std::cout << "3. Find Password" << std::endl;
		std::cout << "4. User List" << std::endl;
		std::cout << "5. Exit" << std::endl;

		std::cin >> choice;
		switch (choice) {
		case 1: {
			signUp();
			continue;
		}
		case 2: {
			logIn();
			continue;
		}
		case 3: {
			findPW();
			continue;
		}
		case 4: {
			printUserList();
			continue;
		}
		case 5: {
			exitProgram();
			exit(0);
		}
		default: {
			std::cout << "Wrong input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
			continue;
		}
		}
	}
}
void MainController::signUp() {
	std::string ID, PW, RP;
	std::cin.ignore(1000, '\n');
	while (true) {
		system("cls");
		std::cin.clear();
		std::cout << "**Sign Up**" << std::endl;
		std::cout << "ID>> ";
		std::getline(std::cin, ID);
		if (acc->isId(ID) || ID == "NULL") {
			std::cout << "This ID already exists. try again!" << std::endl;
			Sleep(1000);
			continue;
		}
		std::cout << "This ID is available." << std::endl;
		std::cout << "PW>> ";
		std::getline(std::cin, PW);
		std::cout << "Recovery Phase>> ";
		std::getline(std::cin, RP);
		break;
	}
	acc->setID(ID);
	acc->setPW(PW);
	acc->setRP(RP);
	std::cout << "Success!";
	std::cin.clear();
	Sleep(1000);
	system("cls");
}
void MainController::logIn() {
	std::string ID, PW;

	system("cls");
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "**Log In**" << std::endl;
	std::cout << "ID>> ";
	std::getline(std::cin, ID);
	if (!acc->isId(ID)) {
		std::cout << "There's no info about " << ID << std::endl;
		std::cin.clear();
		Sleep(1000);
		system("cls");
	}
	std::cout << "PW>> ";
	while (true) {
		std::getline(std::cin, PW);
		if (!acc->isPwMatched(ID, PW)) {
			std::cout << "Wrong password!";
			std::cin.clear();
			Sleep(1000);
			system("cls");
			return;
		}
		me = ID;
		system("cls");
		std::cin.clear();
		std::cout << "@@@ Welcome! @@@";
		std::cin.clear();
		Sleep(1000);
		system("cls");
	}

}
void MainController::findPW() {
	std::string ID, RP;
	system("cls");
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "**Find Password**" << std::endl;
	std::cout << "Insert your ID>> ";
	std::getline(std::cin, ID);
	std::cout << "Insert the recovery phase>> ";
	std::getline(std::cin, RP);

	std::cout << acc->getPW(ID, RP) << std::endl;
	std::cin.clear();
	Sleep(1000);
	system("cls");
}
void MainController::printUserList() {
	system("cls");
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "**User List**" << std::endl;
	if (acc->getSize() == 0) {
		std::cout << "No account found";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		system("cls");
		return;
	}
	for (int i = 0; i < acc->getSize(); i++) {
		std::cout << i + 1 << ". " << acc->getID(i) << std::endl;
	}
	for (int i = 0; i < acc->getSize() + 1; i++) {
		std::cout << ".";
		Sleep(500);
	}
	std::cout << std::endl;
	std::cout << "Back to main menu." << std::endl;
	Sleep(1000);
	system("cls");
}
void MainController::exitProgram() {
	system("cls");
	for (int i = 0; i < 3; i++) {
		std::cout << ".";
		Sleep(500);
	}
	std::cout << std::endl;
	std::cout << "Thank you for using our program." << std::endl;
	Sleep(500);
	std::cout << "We hope to see you again." << std::endl;
	Sleep(2000);
}
#include "MainController.h"
#include "AccountController.h"
#include "EmailController.h"

#include<iostream>
#include <Windows.h>
#include <fstream>
#include <string>

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
		std::cout << std::endl;
		std::cout << "9. Exit" << std::endl;
		std::cout << std::endl;
		std::cout << ">>";

		std::cin >> choice;
		switch (choice) {
		case 1: {
			signUp();
			break;
		}
		case 2: {
			logIn();
		}
		case 3: {
			findPW();
			break;
		}
		case 4: {
			printUserList();
			break;
		}
		case 9: {
			exitProgram();
		}
		default: {
			std::cout << "Wrong input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
			break;
		}
		}
	}
}
void MainController::signUp() {
	std::string ID, PW, RP, AT;
	std::cin.ignore(1000, '\n');
	while (true) {
		system("cls");
		std::cin.clear();
		std::cout << "**Sign Up**" << std::endl;
		std::cout << "(enter 'exit' to cancel)" << std::endl;
		std::cout << "ID>> ";
		std::getline(std::cin, ID);
		if (ID == "exit") {
			std::cin.clear();
			system("cls");
			return start();
		}
		if (acc->isId(ID)) {
			std::cout << "This ID already exists. try again!" << std::endl;
			Sleep(1000);
			continue;
		}
		std::cout << "This ID is available." << std::endl;
		std::cout << "PW>> ";
		std::getline(std::cin, PW);
		if (PW == "exit") {
			std::cin.clear();
			system("cls");
			return start();
		}
		std::cout << "Recovery Phase>> ";
		std::getline(std::cin, RP);
		if (RP == "exit") {
			std::cin.clear();
			system("cls");
			return start();
		}
		std::cout << "Are you signing up for bussiness? (y/n)" << std::endl;
		std::getline(std::cin, AT);
		break;
	}

	acc->setData(ID, { PW,RP,AT });
	acc->saveAll();

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
	std::cout << "(enter 'exit' to cancel)" << std::endl;
	std::cout << "ID>> ";
	std::getline(std::cin, ID);
	if (ID == "exit") {
		std::cin.clear();
		system("cls");
		return start();
	}
	if (!acc->isId(ID)) {
		std::cout << "No account found";
		std::cin.clear();
		Sleep(1000);
		system("cls");
		return start();
	}
	std::cout << "PW>> ";
	while (true) {
		std::getline(std::cin, PW);
		if (PW == "exit") {
			std::cin.clear();
			system("cls");
			return start();
		}
		if (!acc->isPwMatched(ID, PW)) {
			std::cout << "Wrong password!";
			std::cin.clear();
			Sleep(1000);
			system("cls");
			return start();
		}
		me = ID;
		system("cls");
		std::cin.clear();
		std::cout << "@@@ Welcome! @@@";
		Sleep(1000);
		system("cls");

		if (acc->isType(ID) == "y"|| acc->isType(ID) == "Y")
			return subMenu_business();
		else
			return subMenu_normal();
	}

}
void MainController::subMenu_normal() {
	int choice;
	while (true) {
		std::cout << "** [ " << me << " ], good to see you again.**" << std::endl;
		std::cout << "1. Send mail" << std::endl;
		std::cout << "2. Send mail to me" << std::endl;
		std::cout << "3. Inbox" << std::endl;
		std::cout << "4. Sent mail" << std::endl;
		std::cout << "5. Log out" << std::endl;
		std::cout << std::endl;
		std::cout << "9. Delete my account" << std::endl;
		std::cout << std::endl;
		std::cout << ">>";
		std::cin >> choice;
		switch (choice) {

		//send mail
		case 1: {
			mail->sendMail(me);
			std::cin.clear();
			system("cls");
			break;
		}
		//send mail to me
		case 2: { 
			EmailToMe* etm = new EmailToMe();
			etm->sendMail(me);
			std::cout << std::endl;
			std::cout << "The mail is sent successfully." << std::endl;
			Sleep(1000);
			delete etm;
			system("cls");
			std::cin.clear();
			break;
		}
		//inbox
		case 3: {
			mail->receiveMail(me);
			BackOrDelete_receive();
			break;
		}
		//sent mail
		case 4: {
			mail->sentMail(me);
			BackOrDelete_sent();
			break;
		}
		//log out
		case 5: {
			system("cls");
			return start();
		}

		//delte my account
		case 9: {
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			std::string yourPW;
			std::cout << "Enter your Password to confirm >> ";
			std::cin >> yourPW;
			if (yourPW == acc->getPW(me)) {
				std::string yourRP;
				std::cout << "Enter your RecoveryPhase to confirm >> ";
				std::cin >> yourRP;
				if (yourRP == acc->getRP(me)) {
					acc->deleteAcc(me);
					std::cout << "Successfully deleted." << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					Sleep(1000);
					system("cls");
					return start();
				}
				else {
					std::cout << "ID verification failed. Retrun to submenu." << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					Sleep(1000);
					system("cls");
					break;
				}
			}
			else {
				std::cout << "ID verification failed. Retrun to submenu." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
				break;
			}
		}

		default: {
			std::cout << "Wrong input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
			break;
		}
		}
	}
}

void MainController::subMenu_business() {
	int choice;
	while (true) {
		std::cout << "**" << me << ", good to see you again.**" << std::endl;
		std::cout << "1. Send business mail" << std::endl;
		std::cout << "2. Set Title and Content" << std::endl;
		std::cout << "3. Inbox" << std::endl;
		std::cout << "4. Sent mail" << std::endl;
		std::cout << "5. Log out" << std::endl;
		std::cout << std::endl;
		std::cout << "9. Delete my account" << std::endl;
		std::cout << std::endl;
		std::cout << ">>";
		std::cin >> choice;
		switch (choice) {

		case 1: { //send mail
			mail->sendMail(me);
			break;
		}
		case 2: { //set title and content
			std::string t, c;
			BusinessEmail* BE = new BusinessEmail;
			std::cout << "Title>> ";
			std::getline(std::cin, t);
			std::cout << "Content>> ";
			std::getline(std::cin, c);
			BE->setTitle(t);
			BE->setContent(c);
			delete BE;

		}
		case 3: { //inbox
			mail->receiveMail(me);
			std::cout << std::endl;
			std::cout << "1. Go back to submenu" << std::endl;
			std::cout << std::endl;
			std::cout << ">>";
			int choice2;
			std::cin >> choice2;
			switch (choice2) {
			case 1: { //go back to submenu
				Sleep(1000);
				system("cls");
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				break;
			}
			default: {
				std::cout << "Wrong input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
				break;
			}
			}
		}
		case 4: { //sent mail
			mail->sentMail(me);
			std::cout << std::endl;
			std::cout << "1. Go back to submenu" << std::endl;
			std::cout << std::endl;
			std::cout << ">>";
			int choice2;
			std::cin >> choice2;
			switch (choice2) {
			case 1: { //go back to submenu
				Sleep(1000);
				system("cls");
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				break;
			}
			default: {
				std::cout << "Wrong input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
				break;
			}
			}
		}
		case 5: { //log out
			system("cls");
			return start();
		}

		case 9: { //delte my account
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			std::string yourPW;
			std::cout << "Enter your Password to confirm >> ";
			std::cin >> yourPW;
			if (yourPW == acc->getPW(me)) { //check password
				std::string yourRP;
				std::cout << "Enter your RecoveryPhase to confirm >> ";
				std::cin >> yourRP;
				if (yourRP == acc->getRP(me)) { //check recovery phase
					acc->deleteAcc(me);
					std::cout << "Successfully deleted." << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					Sleep(1000);
					system("cls");
					return start();
				}
				else {
					std::cout << "ID verification failed. Retrun to submenu." << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					Sleep(1000);
					system("cls");
					break;
				}
			}
			else {
				std::cout << "ID verification failed. Retrun to submenu." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
				break;
			}
		}

		default: {
			std::cout << "Wrong input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
			break;
		}
		}
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

	std::cout << acc->getYourPW(ID, RP) << std::endl;
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
		for (int i = 0; i < 4; i++) {
			std::cout << ".";
			Sleep(500);
		}
		std::cout << std::endl;
		std::cout << "Back to main menu." << std::endl;
		std::cin.clear();
		Sleep(1000);
		system("cls");
		return start();
	}
	else {
		acc->printUsers();

		for (int i = 0; i < acc->getSize() + 1; i++) {
			std::cout << ".";
			Sleep(500);
		}
		std::cout << std::endl;
		std::cout << "Back to main menu." << std::endl;
		Sleep(1000);
		system("cls");
	}
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
	exit(0);
}

void MainController::BackOrDelete_sent() {
	std::cout << std::endl;
	std::cout << "1. Go back to submenu" << std::endl;
	std::cout << "2. Delete sent mail" << std::endl;
	std::cout << std::endl;
	std::cout << ">>";
	int choice2;
	std::cin >> choice2;
	switch (choice2) {
	case 1: { //go back to submenu
		Sleep(1000);
		system("cls");
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		break;
	}
	case 2: { // delete sent mail
		std::string yourPW;
		std::cout << "Enter your Password to confirm >> ";
		std::cin >> yourPW;
		if (yourPW == acc->getPW(me)) {
			std::string yourRP;
			std::cout << "Enter your RecoveryPhase to confirm >> ";
			std::cin >> yourRP;
			if (yourRP == acc->getRP(me)) {
				mail->deleteSentMail(me);
				std::cout << "Successfully deleted." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
				return start();
			}
			else {
				std::cout << "ID verification failed. Retrun to submenu." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
			}
		}
		else {
			std::cout << "ID verification failed. Retrun to submenu." << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
		}
	}
	default: {
		std::cout << "Wrong input!" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		system("cls");
		break;
	}
	}
}
void MainController::BackOrDelete_receive() {
	std::cout << std::endl;
	std::cout << "1. Go back to submenu" << std::endl;
	std::cout << "2. Delete received mail" << std::endl;
	std::cout << std::endl;
	std::cout << ">>";
	int choice2;
	std::cin >> choice2;
	switch (choice2) {
	case 1: {
		Sleep(1000);
		system("cls");
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		break;
	}
	case 2: {
		std::string yourPW;
		std::cout << "Enter your Password to confirm >> ";
		std::cin >> yourPW;
		if (yourPW == acc->getPW(me)) {
			std::string yourRP;
			std::cout << "Enter your RecoveryPhase to confirm >> ";
			std::cin >> yourRP;
			if (yourRP == acc->getRP(me)) {
				mail->deleteReceiveMail(me);
				std::cout << "Successfully deleted." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
				return start();
			}
			else {
				std::cout << "ID verification failed. Retrun to submenu." << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				Sleep(1000);
				system("cls");
			}
		}
		else {
			std::cout << "ID verification failed. Retrun to submenu." << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
		}

	}
	default: {
		std::cout << "Wrong input!" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		system("cls");
		break;
	}
	}
}
void MainController::deleteAccount() {
	std::string yourPW;
	std::cout << "Enter your Password to confirm >> ";
	std::cin >> yourPW;
	if (yourPW == acc->getPW(me)) {
		std::string yourRP;
		std::cout << "Enter your RecoveryPhase to confirm >> ";
		std::cin >> yourRP;
		if (yourRP == acc->getRP(me)) {
			acc->deleteAcc(me);
			std::cout << "Successfully deleted." << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
			return start();
		}
		else {
			std::cout << "ID verification failed. Retrun to submenu." << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			system("cls");
		}
	}
	else {
		std::cout << "ID verification failed. Retrun to submenu." << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		system("cls");
	}
}
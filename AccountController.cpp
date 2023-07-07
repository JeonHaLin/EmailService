#include "AccountController.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

AccountController::AccountController() {
	std::ifstream fout("./userData.txt");
	fileRead(userData, fout);
	fout.close();
}

//Check if the given name exists.
bool AccountController::isId(std::string name) {
	for (auto it = userData.begin(); it != userData.end(); it++) {
		if (it->first == name) {
			return true;
		}
	}
	return false;
}
//Check if the given password is matched to the given name.
bool AccountController::isPwMatched(std::string name, std::string pw) {
	std::string temp;
	for (auto it = userData.begin(); it != userData.end(); it++) {
		if (it->first == name) {
			temp=it->second.password;
		}
	}
	if (pw == temp) return true;
	else return false;
}
//Check if the given recovery phase is matched to the given name.
bool AccountController::isRpMatched(std::string name, std::string rp) {
	std::string temp;
	for (auto it = userData.begin(); it != userData.end(); it++) {
		if (it->first == name) {
			temp = it->second.recoveryPhase;
		}
	}
	if (rp == temp) return true;
	else return false;
}

//add ID to id list.
void AccountController::setData(std::string ID, personalData PD) {
	userData.insert(make_pair(ID,PD));
}

//getter of id size
int AccountController::getSize() {
	return userData.size();
}

//getter of password
std::string AccountController::getPW(std::string name) {
	for (auto it = userData.begin(); it != userData.end(); it++) {
		if (it->first == name) {
			return it->second.password;
		}
	}
}
std::string AccountController::getRP(std::string name) {
	for (auto it = userData.begin(); it != userData.end(); it++) {
		if (it->first == name) {
			return it->second.recoveryPhase;
		}
	}
}

std::string AccountController::getYourPW(std::string ID, std::string RP) {
	int index = 0;
	if (isId(ID)) {
		if (isRpMatched(ID, RP)) {
			std::string temp;
			for (auto it = userData.begin(); it != userData.end(); it++) {
				if (it->first == ID) {
					temp = it->second.password;
				}
			}
			return "Your password is [ " + temp + " ]";
		}
		return "Wrong Recovery Phase!";
	}
	return "No account found.";
}

void AccountController::fileRead(std::map<std::string, personalData>& v, std::ifstream& fin) {
	std::string line;
	if (fin) {
		while (std::getline(fin, line)) {

			std::string id;
			personalData data;

			std::istringstream iss(line);
			std::getline(iss, id, ',');
			std::getline(iss, data.password, ',');
			std::getline(iss, data.recoveryPhase, ',');

			v.insert(std::make_pair(id, data));
		}
	}
	else {
		std::ofstream emptyFile("./userData.txt");
		emptyFile.close();
	}

}

void AccountController::printUsers() {
	for (auto it = userData.begin(); it != userData.end(); it++) {
		std::cout << it->first << std::endl;
	}
}
void AccountController::saveAll() {
	std::ofstream fout;

	fout.open("./userData.txt");
	if (!fout) {
		std::cout << "Data loss error!" << std::endl;
		exit(0);
	}

	for (auto it = userData.begin(); it != userData.end(); it++) {
		fout << it->first << ',';
		fout << it->second.password << ',';
		fout << it->second.recoveryPhase << std::endl;
	}
	fout.close();	
}

void AccountController::deleteAcc(std::string name) {
	userData.erase(name);

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

void AccountController::deleteAllInfo(std::string) {
	
}
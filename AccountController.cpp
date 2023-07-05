#include "AccountController.h"
#include <iostream>
#include <windows.h>

//Check if the given name exists.
bool AccountController::isId(std::string name) {
	for (int i = 0; i < id.size(); i++) {
		if (id[i] == name) {
			return true;
		}
	}
	return false;
}
//Check if the given password is matched to the given name.
bool AccountController::isPwMatched(std::string name, std::string pw) {
	int index = -1;
	for (int i = 0; i < id.size(); i++) {
		if (name == id[i]) {
			index = i;
		}
	}
	if (pw == password[index]) return true;
	else return false;
}
//Check if the given recovery phase is matched to the given name.
bool AccountController::isRpMatched(std::string name, std::string rp) {
	int index = -1;
	for (int i = 0; i < id.size(); i++) {
		if (name == id[i]) {
			index = i;
		}
	}
	if (rp == recoveryPhrase[index]) return true;
	else return false;
}

//add ID to id list.
void AccountController::setID(std::string ID) {
	id.push_back(ID);
}
//add PW to password list.
void AccountController::setPW(std::string PW) {
	password.push_back(PW);
}
//add RP to recoveryPhase list.
void AccountController::setRP(std::string RP) {
	recoveryPhrase.push_back(RP);
}

//getter of id size
int AccountController::getSize() {
	return id.size();
}
//getter of id
std::string AccountController::getID(int index) {
	return id[index];
}
//kind of getter of password
std::string AccountController::getPW(std::string ID, std::string RP) {
	int index = 0;
	if (isId(ID)) {
		if (isRpMatched(ID, RP)) {
			for (int i = 0; i < id.size(); i++) {
				if (id[i] == ID) index = i;
			}
			return "Your password is [ " + password[index] + " ]";
		}
		return "Wrong Recovery Phase";
	}
	return "No account found";
}

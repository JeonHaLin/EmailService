#pragma once
#include <string>
#include <map>

struct personalData {
	std::string password;
	std::string recoveryPhase;
	std::string accountType;
};

class AccountController {
private:
	std::map <std::string, personalData> userData;

public:
	AccountController();

	bool isId(std::string);
	bool isPwMatched(std::string,std::string);
	bool isRpMatched(std::string, std::string);
	std::string isType(std::string);

	void setData(std::string, personalData);

	int getSize();

	std::string getPW(std::string);
	std::string getRP(std::string);

	std::string getYourPW(std::string, std::string);
	void fileRead(std::map<std::string, personalData>&);
	void fileWrite(std::map<std::string, personalData>&);

	void printUsers();
	void saveAll();
	void deleteAcc(std::string);
};
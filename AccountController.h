#pragma once
#include <string>
#include <vector>

class AccountController {
private:
	std::vector <std::string> id;
	std::vector <std::string> password;
	std::vector <std::string> recoveryPhrase;

public:
	bool isId(std::string);
	bool isPwMatched(std::string,std::string);
	bool isRpMatched(std::string, std::string);

	void setID(std::string);
	void setPW(std::string);
	void setRP(std::string);

	int getSize();
	std::string getID(int);
	std::string getPW(std::string, std::string);
};
#pragma once
#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>

class Account
{
public:
	Account() { name = ""; passwd = ""; }
// использовался для фиксации удаления при тестировании	~Account() { std::cout << "deleted account " << this->name << std::endl;  } 
	void chg_passwd(const std::string tmp);
	void chg_name(const std::string tmp);
	std::string get_name() { return this->name; }
	std::string get_passwd() { return this->passwd; }
	Account(const std::string str1, const std::string str2) { name = str1; passwd = str2; }
	void show();
private:
	std::string name;
	std::string passwd;
};


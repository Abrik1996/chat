#pragma once
#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>

class Account
{
public:
	Account() { name = ""; passwd = ""; }
	~Account() { std::cout << "deleted account " << this->name << std::endl;  }
	void chg_passwd(const std::string tmp)
	{
		this->passwd = tmp;
		std::cout << "pass set " << tmp << std::endl;
	}
	void chg_name(const std::string tmp)
	{
		this->name = tmp;
		std::cout << "name set " << tmp << std::endl;
	}
	std::string get_name() { return this->name; }
	std::string get_passwd() { return this->passwd; }
	Account(const std::string str1, const std::string str2) { name = str1; passwd = str2; }
	void show()
	{
		std::cout << "Account name = " << name << ", Passwd = " << passwd << std::endl;
 	}
private:
	std::string name;
	std::string passwd;
};


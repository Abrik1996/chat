#include "Account.h"

void Account::chg_passwd(const std::string tmp)
{
	this->passwd = tmp;
	std::cout << "pass set " << tmp << std::endl;
}

void Account::chg_name(const std::string tmp)
{
	this->name = tmp;
	std::cout << "name set " << tmp << std::endl;
}

void Account::show()
{
	
		std::cout << "Account name = " << name << std::endl; // ", Passwd = " << passwd << std::endl; (старый функционал для тестирования)
	
}

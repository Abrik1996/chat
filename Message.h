#pragma once
#include "Account.h"
#include <sstream>
class Message
{
public:
	Message(std::string input);

	std::string get_originator() { return this->originator; }
	std::string get_target() { return this->target; }
	void show();
private:
	std::string originator;
	std::string target;
	std::string text;
};


#include "Message.h"

Message::Message(std::string input)
{
	std::stringstream ss(input);
	ss >> this->originator;
	ss >> this->target;
	std::string tmp;
	while (ss)
	{
		this->text += tmp + " ";
		ss >> tmp;
	}
}

void Message::show()
{
	std::cout << "From " << originator << " to " << target << " text: " << text << std::endl;
}

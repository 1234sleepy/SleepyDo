#pragma once

#include <string>
#include <array>


class SessionQuote
{
private:
	static const std::array<std::string, 10> _quotes;
public:
	static std::string getRandomQuote();
};

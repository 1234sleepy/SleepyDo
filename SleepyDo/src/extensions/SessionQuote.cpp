#include "../../include/extensions/SessionQuote.h"

#include <random>

const std::array<std::string, 10> SessionQuote::_quotes =
{
    "Code. Break. Fix. Repeat.",
    "Small steps build big results.",
    "Think first, code second.",
    "Progress beats perfection.",
    "Stay curious, keep learning.",
    "Discipline creates freedom.",
    "Solve problems, not symptoms.",
    "Focus beats scattered effort.",
    "Consistency builds mastery.",
    "Build today, improve tomorrow."
};

std::string SessionQuote::getRandomQuote()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, _quotes.size() - 1);

    return _quotes[dist(gen)];
}
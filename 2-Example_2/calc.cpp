#include "calc.hpp"

Student::Student()
{
}
Student::Student(int score, std::string name) : score(score), name(name)
{
    std::cout << "Constructor is Called" << std::endl;
}
bool Student::DisplayScore()
{
    if (score >= 50)
        return true;
    else
        return false;
}

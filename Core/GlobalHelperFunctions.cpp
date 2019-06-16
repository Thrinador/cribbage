#include "GlobalHelperFunctions.h"

/*------------------------------------------------------------------
// name:		ClearScreen
// description:	Clears the console screen. ONLY FOR WINDOWS OPERATING
//              SYSTEMS.
// parameters:	none
// returns:		none
// called by:	Human::printPegging, intro, printTable, printRoundStart
//----------------------------------------------------------------*/
void ClearScreen() {
    std::cout << std::endl;
    for (int i = 0; i < 80; i++)
        std::cout << "#";
    std::cout << std::endl;
}

/*------------------------------------------------------------------
// name:		format
// description:	takes in a num and formats it to take up two char spaces.
//              that is if the number is less then 10 it adds a space after
// parameters:	num to be formatted
// returns:		string of the formatted number
// called by:	printTable
//----------------------------------------------------------------*/
std::string format(int num) {
    if (num < 10) {
        return (std::to_string(num) + "  ");
    }
    else if (num < 100) {
        return (std::to_string(num) + " ");
    }
    return std::to_string(num);
}

std::string format(double num)
{
    std::string s;
    std::stringstream sstream;
    sstream.setf(std::ios::fixed);
    sstream.precision(2);
    sstream << num;
    if (num < 10) {
        return " " + sstream.str();
    }
    return sstream.str();
}

/*------------------------------------------------------------------
// name:		printName
// description:	Takes in a name and prints one space before the name
//              as many spaces as need after to make the total length 20
// parameters:	string to be printed
// returns:		none
// called by:	printTable
//----------------------------------------------------------------*/
void printName(std::string name) {
    std::cout << " " << name;
    for (int i = name.length(); i < 20; i++) std::cout << " ";
    std::cout << "|";
}
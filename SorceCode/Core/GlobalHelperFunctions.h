#pragma once

#include <iostream>
#include <string>
#include <sstream>

/*------------------------------------------------------------------
// name:		ClearScreen
// description:	Clears the console screen. ONLY FOR WINDOWS OPERATING
//              SYSTEMS.
// parameters:	none
// returns:		none
// called by:	Human::printPegging, intro, printTable, printRoundStart
//----------------------------------------------------------------*/
void ClearScreen();

/*------------------------------------------------------------------
// name:		format
// description:	takes in a num and formats it to take up two char spaces.
//              that is if the number is less then 10 it adds a space after
// parameters:	num to be formatted
// returns:		string of the formatted number
// called by:	printTable
//----------------------------------------------------------------*/
std::string format(int num);

std::string format(double num);

/*------------------------------------------------------------------
// name:		printName
// description:	Takes in a name and prints one space before the name
//              as many spaces as need after to make the total length 20
// parameters:	string to be printed
// returns:		none
// called by:	printTable
//----------------------------------------------------------------*/
void printName(std::string name);
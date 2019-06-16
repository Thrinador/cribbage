#pragma once

#include "Board.h"
#include "Deck.h"
#include "../Players/Computer.h"
#include "../Players/Human.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

Board* setupGame() {
    cout << "--------------------------------" << endl;
    cout << "*                              *" << endl;
    cout << "*   Welcome to text Cribbage   *" << endl;
    cout << "*                              *" << endl;
    cout << "--------------------------------" << endl << endl;

    int choice = 0;
    do {
        cout << "Enter 0 for Human vs Computer." << endl;
        cout << "Enter 1 for Human vs Human." << endl;
        cout << "Enter 2 for Computer vs Computer." << endl;
        cin >> choice;
        cin.get();
    } while (choice < 0 && choice > 3);

    if (choice == 0) return new Board(new Human(), new Computer());
    else if (choice == 1) return new Board(new Human(), new Human());
    else return new Board(new Computer(), new Computer());
}

/*------------------------------------------------------------------
// name:		main
// description:	Starts the Game by making a Board and calling play.
//----------------------------------------------------------------*/
int main() {
    Board *b = setupGame();
    b->play();
}
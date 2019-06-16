#pragma once

#include "Board.h"
#include "Deck.h"
#include "../Players/Computer.h"
#include "../Players/Human.h"
#include "../Players/MediumBot.h"
#include "../Players/HardBot.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int getChoice(char* player) {
    int choice = 0;
    do {
        cout << "Who is " << player << "?" << endl;
        cout << "Enter 0 for Human" << endl;
        cout << "Enter 1 for EasyBot" << endl;
        cout << "Enter 2 for MediumBot" << endl;
        cout << "Enter 3 for HardBot" << endl;
        cin >> choice;
        cin.get();
    } while (choice < 0 || choice > 4);
    return choice;
}

Player* getPlayer(char* player) {
    int choice = getChoice(player);

    switch (choice) {
    case 0:
        return new Human();
    case 1:
        return new Computer();
    case 2:
        return new MediumBot();
    default:
        return new HardBot();
    }
}

Board* setupGame() {
    cout << "--------------------------------" << endl;
    cout << "*                              *" << endl;
    cout << "*   Welcome to text Cribbage   *" << endl;
    cout << "*                              *" << endl;
    cout << "--------------------------------" << endl << endl;

    Player* player1 = getPlayer("player 1");
    Player* player2 = getPlayer("player 2");

    return new Board(player1, player2);   
}

int main() {
    Board *b = setupGame();
    b->play();
}
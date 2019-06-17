#pragma once

#include "Board.h"
#include "Deck.h"
#include "../Players/Computer.h"
#include "../Players/Human.h"
#include "../Players/MediumBot.h"
#include "../Players/HardBot.h"
#include "../Output/SimulationStats.h"
#include "Constants.h"
#include "ctpl_stl.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

Player* selectPlayer(int choice) {
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

#if (!simulating)

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

    return selectPlayer(choice);
}

#endif

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

void gameThread(SimulationStats* sim, bool turn, int player1Type, int player2Type, int gameNumber) {
    Board b(selectPlayer(player1Type), selectPlayer(player2Type), turn);
    GameStats game = b.play();
    sim->addGame(game);
    cout << "Game " << gameNumber << endl;
}

void simulateGames() {
    chrono::time_point<std::chrono::system_clock> start, end;

    int gamesToSimulate = 1000;
    int simulatedGames = 1;

    int player1Type = 3;
    int player2Type = 1;

    SimulationStats * sim = new SimulationStats(selectPlayer(player1Type)->getName(), selectPlayer(player2Type)->getName(), gamesToSimulate);
    bool startPlayer = false;

    start = std::chrono::system_clock::now();

    ctpl::thread_pool p(16);
    for (int i = 0; i < gamesToSimulate; i++) {
        p.push([sim, player1Type, player2Type, startPlayer, i](int id) {
            Board b(selectPlayer(player1Type), selectPlayer(player2Type), startPlayer);
            GameStats game = b.play();
            sim->addGame(game);
            cout << "Game " << i << endl;
        });
        startPlayer = !startPlayer;
    }

    p.stop(true);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Simulation took " << elapsed_seconds.count() << " seconds" << endl << endl;
    sim->printSimulationResults();
}

void playGame() {

}

int main() {
    if (simulating) {
        simulateGames();
    }
    else {
        playGame();
    }
}
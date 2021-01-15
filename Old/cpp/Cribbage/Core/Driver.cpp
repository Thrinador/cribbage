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
#include "json.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>

Player* selectPlayer(string choice) {
    if (choice == "Human") {
        return new Human();
    }
    else if (choice == "EasyBot") {
        return new Computer();
    }
    else if (choice == "MediumBot") {
        return new MediumBot();
    }
    else if (choice == "HardBot") {
        return new HardBot();
    }
    else {
        //TODO add abort logic
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

//Player* getPlayer(char* player) {
//    int choice = getChoice(player);
//
//    return selectPlayer(choice);
//}

#endif

//Board* setupGame() {
//    cout << "--------------------------------" << endl;
//    cout << "*                              *" << endl;
//    cout << "*   Welcome to text Cribbage   *" << endl;
//    cout << "*                              *" << endl;
//    cout << "--------------------------------" << endl << endl;
//
//    Player* player1 = getPlayer("player 1");
//    Player* player2 = getPlayer("player 2");
//
//    return new Board(player1, player2);   
//}

void gameThread(SimulationStats* sim, bool turn, string player1Type, string player2Type, int gameNumber) {
    Board b(selectPlayer(player1Type), selectPlayer(player2Type), turn);
    GameStats game = b.play();
    sim->addGame(game);
    cout << "Game " << gameNumber << endl;
}

void simulateGames(nlohmann::json json) {
    int gamesToSimulate = json["numOfGames"];
    int simulatedGames = 1;
    string player1Type = json["player1"];
    string player2Type = json["player2"];
    SimulationStats * sim = new SimulationStats(selectPlayer(player1Type)->getName(), selectPlayer(player2Type)->getName(), gamesToSimulate);
    bool startPlayer = true;
    bool player1AlwaysStart = (json["player1AlwaysStart"] == "yes") ? true : false;
    chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    ctpl::thread_pool p(json["numOfThreads"]);
    for (int i = 0; i < gamesToSimulate; i++) {
        p.push([sim, player1Type, player2Type, startPlayer, i](int id) {
            Board b(selectPlayer(player1Type), selectPlayer(player2Type), startPlayer);
            GameStats game = b.play();
            sim->addGame(game);
            cout << "Game " << i << endl;
        });
        
        if (!player1AlwaysStart) startPlayer = !startPlayer;
    }
    p.stop(true);

    chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Simulation took " << elapsed_seconds.count() << " seconds" << endl << endl;
    sim->printSimulationResults();
}

void playGame() {
    
}

nlohmann::json buildGame() {
    std::ifstream file("config.json");
    nlohmann::json json;
    file >> json;
    return json;
}

int main() {
    nlohmann::json json = buildGame();

    if (json["simulating"] == "yes") {
        simulateGames(json);
    }
    else {
        playGame();
    }
}
#pragma once
#include <iostream>
#include <vector>

#include "../Core/Score.h"
#include "../Core/GlobalHelperFunctions.h"
#include "../Players/Player.h"
#include "GameStats.h"

using namespace std;

class SimulationStats {
public:
    SimulationStats(string p1, string p2, int gamesToSimulate) : player1(p1), player2(p2), gamesSimulated(gamesToSimulate) {};

    void addGame(GameStats game);
    void printSimulationResults();

private:
    struct Stats {
        int totalFifteens = 0;
        int totalRuns = 0;
        int totalFlushes = 0;
        int totalOfAKind = 0;
        int totalNubs = 0;
        int totalPegs = 0;

        int totalHand = 0;
        int bestHand = 0;
        int totalCrib = 0;
        int bestCrib = 0;
        int bestPeg = 0;

        int wins = 0;

    };

    void addPlayerStats(Stats & playerStats, GameStats game, vector<Score> playerHandScores, vector<Score> playerCribScores);
    void printPlayerStats(string player, Stats playerStats);

    string player1;
    string player2;

    Stats player1Stats;
    Stats player2Stats;

    int gamesSimulated;
};

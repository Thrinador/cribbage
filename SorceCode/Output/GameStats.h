#pragma once
#include <iostream>
#include <vector>

#include "../Core/Score.h"
#include "../Core/GlobalHelperFunctions.h"

using namespace std;

class GameStats {
public:
    GameStats() {};

    void addScores(Score p1Score, Score p2Score, Score cribScore, bool playersCrib);
    void calculateEndGameStats(string p1Name, string p2Name);

private:
    string totalFifteens(vector<Score> handScores, vector<Score> CribScores);
    string totalRuns(vector<Score> handScores, vector<Score> CribScores);
    string totalFlushes(vector<Score> handScores, vector<Score> CribScores);
    string totalOfAKind(vector<Score> handScores, vector<Score> CribScores);
    string totalNubs(vector<Score> handScores, vector<Score> CribScores);
    string totalPegs(vector<Score> handScores);

    string averageHand(vector<Score> handScores);
    string bestHand(vector<Score> handScores);
    string averageCrib(vector<Score> CribScores);
    string bestCrib(vector<Score> CribScores);
    string bestPeg(vector<Score> handScores);
    string averagePeg(vector<Score> handScores);

    vector<Score> p1HandScores;
    vector<Score> p2HandScores;
    vector<Score> p1CribHandScores;
    vector<Score> p2CribHandScores;
};

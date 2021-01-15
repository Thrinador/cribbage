/*--------------------------------------------------------------------
// file name:	Board.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A representation of a Cribbage board. Controls the deck
//              and Player classes. The play method acts as the driver for
//              the program.
// variables:	a bool representing if it is player1's turn or player2's
//              turn. Deck that is in charge of dealing the cards and
//              getting the cut for the board. Players 1 and 2 that
//              are the players in the game. A vector that is the crib cards
//--------------------------------------------------------------------*/

#pragma once
#include <vector>

#include "../Core/Score.h"

using namespace std;

class GameStats {
public:
    GameStats() {}

    void addScores(Score p1Score, Score p2Score, Score cribScore, bool playersCrib);
    void calculateEndGameStats(string p1Name, string p2Name);

    int totalFifteens(vector<Score> handScores, vector<Score> CribScores);
    int totalRuns(vector<Score> handScores, vector<Score> CribScores);
    int totalFlushes(vector<Score> handScores, vector<Score> CribScores);
    int totalOfAKind(vector<Score> handScores, vector<Score> CribScores);
    int totalNubs(vector<Score> handScores, vector<Score> CribScores);
    int totalPegs(vector<Score> handScores);

    int averageHand(vector<Score> handScores);
    int bestHand(vector<Score> handScores);
    int averageCrib(vector<Score> CribScores);
    int bestCrib(vector<Score> CribScores);
    int bestPeg(vector<Score> handScores);
    int averagePeg(vector<Score> handScores);

    void reset();

    vector<Score> p1HandScores;
    vector<Score> p2HandScores;
    vector<Score> p1CribHandScores;
    vector<Score> p2CribHandScores;
    bool winner;
};

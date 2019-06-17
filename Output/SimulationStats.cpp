#include "SimulationStats.h"

void SimulationStats::addGame(GameStats game) {
    addPlayerStats(player1Stats, game, game.p1HandScores, game.p1CribHandScores);
    addPlayerStats(player2Stats, game, game.p2HandScores, game.p2CribHandScores);
    if (game.winner) player1Stats.wins++;
    else player2Stats.wins++;
}

void SimulationStats::printSimulationResults() {
    printPlayerStats(player1, player1Stats);
    cout << "------------------------------------------------------------------" << endl;
    printPlayerStats(player2, player2Stats);

    cin.get();
}

void SimulationStats::addPlayerStats(Stats & stats, GameStats game, vector<Score> handScores, vector<Score> cribScores) {
    stats.totalCrib += game.averageCrib(cribScores);
    stats.totalHand += game.averageHand(handScores);

    if (game.bestCrib(cribScores) > stats.bestCrib) 
        stats.bestCrib = game.bestCrib(cribScores);
    
    if (game.bestHand(handScores) > stats.bestHand)
        stats.bestHand = game.bestCrib(handScores);

    if (game.bestPeg(handScores) > stats.bestPeg)
        stats.bestPeg = game.bestPeg(handScores);

    stats.totalFifteens += game.totalFifteens(handScores, cribScores);
    stats.totalFlushes += game.totalFlushes(handScores, cribScores);
    stats.totalNubs += game.totalNubs(handScores, cribScores);
    stats.totalOfAKind += game.totalOfAKind(handScores, cribScores);
    stats.totalPegs += game.totalPegs(handScores);
    stats.totalRuns += game.totalRuns(handScores, cribScores);
}

void SimulationStats::printPlayerStats(string player, Stats playerStats) {
    cout << player << endl;
    cout << "Win percentage " << playerStats.wins << endl;
    cout << "Average crib points per game " << ((double)playerStats.totalCrib) / gamesSimulated << endl;
    cout << "Average hand points per game " << ((double)playerStats.totalHand) / gamesSimulated << endl;
    cout << endl;
    cout << "Best single crib " << playerStats.bestCrib << endl;
    cout << "Best single hand " << playerStats.bestHand << endl;
    cout << "Best single pegging game " << playerStats.bestPeg << endl;
    cout << endl;
    cout << "Average points from fifteens per game " << ((double)playerStats.totalFifteens) / gamesSimulated << endl;
    cout << "Average points from flushes per game " << ((double)playerStats.totalFlushes) / gamesSimulated << endl;
    cout << "Average points from nubs per game " << ((double)playerStats.totalNubs) / gamesSimulated << endl;
    cout << "Average points from of a kind per game " << ((double)playerStats.totalOfAKind) / gamesSimulated << endl;
    cout << "Average points from pegging per game " << ((double)playerStats.totalPegs) / gamesSimulated << endl;
    cout << "Average points from runs per game " << ((double)playerStats.totalRuns) / gamesSimulated << endl;
}

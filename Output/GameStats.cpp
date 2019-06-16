#include "GameStats.h"

void GameStats::addScores(Score p1Score, Score p2Score, Score cribScore, bool playersCrib) {
    p1HandScores.push_back(p1Score);
    p2HandScores.push_back(p2Score);
    if(playersCrib) p1CribHandScores.push_back(cribScore);
    else p2CribHandScores.push_back(cribScore);
}

void GameStats::calculateEndGameStats(string p1Name, string p2Name) {
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "| Criteria                    |";
    printName(p1Name);
    printName(p2Name);
    cout << endl;
    cout << "|-----------------------------|-------------------------------------------|" << endl;
    cout << "| Total points from fifteens  | " << totalFifteens(p1HandScores, p1CribHandScores) << "                 | " << totalFifteens(p2HandScores, p2CribHandScores) << "                 |" << endl;
    cout << "| Total points from runs      | " << totalRuns(p1HandScores, p1CribHandScores) << "                 | " << totalRuns(p2HandScores, p2CribHandScores) << "                 |" << endl;
    cout << "| Total points from of a kind | " << totalOfAKind(p1HandScores, p1CribHandScores) << "                 | " << totalOfAKind(p2HandScores, p2CribHandScores) << "                 |" << endl;
    cout << "| Total points from flushes   | " << totalFlushes(p1HandScores, p1CribHandScores) << "                 | " << totalFlushes(p2HandScores, p2CribHandScores) << "                 |" << endl;
    cout << "| Total points from nubs      | " << totalNubs(p1HandScores, p1CribHandScores) << "                 | " << totalNubs(p2HandScores, p2CribHandScores) << "                 |" << endl;
    cout << "| Total points from Pegging   | " << totalPegs(p1HandScores) << "                 | " << totalPegs(p2HandScores) << "                 |" << endl;
    cout << "|-----------------------------|-------------------------------------------|" << endl;
    cout << "| Best Hand                   | " << bestHand(p1HandScores) << "                 | " << bestHand(p2HandScores) << "                 |" << endl;
    cout << "| Best Crib                   | " << bestCrib(p1CribHandScores) << "                 | " << bestCrib(p2CribHandScores) << "                 |" << endl;
    cout << "| Best Pegging                | " << bestPeg(p1HandScores) << "                 | " << bestPeg(p2HandScores) << "                 |" << endl;
    cout << "| Average Hand                | " << averageHand(p1HandScores) << "               | " << averageHand(p2HandScores) << "               |" << endl;
    cout << "| Average Crib                | " << averageCrib(p1CribHandScores) << "               | " << averageCrib(p2CribHandScores) << "               |" << endl;
    cout << "| Average Pegging             | " << averagePeg(p1HandScores) << "               | " << averagePeg(p2HandScores) << "               |" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    cout << "Press enter to continue.";
    cin.get();
}

string GameStats::totalFifteens(vector<Score> handScores, vector<Score> CribScores) {
    int total = 0;
    for (Score s : handScores) {
        total += s.fifteens;
    }

    for (Score s : CribScores) {
        total += s.fifteens;
    }

    return format(total);
}

string GameStats::totalRuns(vector<Score> handScores, vector<Score> CribScores)
{
    int total = 0;
    for (Score s : handScores) {
        total += s.runs;
    }

    for (Score s : CribScores) {
        total += s.runs;
    }

    return format(total);
}

string GameStats::totalFlushes(vector<Score> handScores, vector<Score> CribScores)
{
    int total = 0;
    for (Score s : handScores) {
        total += s.flush;
    }

    for (Score s : CribScores) {
        total += s.flush;
    }

    return format(total);
}

string GameStats::totalOfAKind(vector<Score> handScores, vector<Score> CribScores)
{
    int total = 0;
    for (Score s : handScores) {
        total += s.ofAKind;
    }

    for (Score s : CribScores) {
        total += s.ofAKind;
    }

    return format(total);
}

string GameStats::totalNubs(vector<Score> handScores, vector<Score> CribScores)
{
    int total = 0;
    for (Score s : handScores) {
        total += s.nubs;
    }

    for (Score s : CribScores) {
        total += s.nubs;
    }

    return format(total);
}

string GameStats::totalPegs(vector<Score> handScores)
{
    int total = 0;
    for (Score s : handScores) {
        total += s.pegging;
    }

    return format(total);
}

string GameStats::averageHand(vector<Score> handScores)
{
    double total = 0;
    for (Score s : handScores) {
        total += s.getTotal();
    }
    total /= handScores.size();
    return format(total);
}

string GameStats::bestHand(vector<Score> handScores)
{
    int max = 0;
    for (Score s : handScores) {
        if (s.getTotal() > max) {
            max = s.getTotal();
        }
    }

    return format(max);
}

string GameStats::averageCrib(vector<Score> cribScores)
{
    double total = 0;
    for (Score s : cribScores) {
        total += s.getTotal();
    }
    total /= cribScores.size();
    return format(total);
}

string GameStats::bestCrib(vector<Score> cribScores)
{
    int max = 0;
    for (Score s : cribScores) {
        if (s.getTotal() > max) {
            max = s.getTotal();
        }
    }

    return format(max);
}

string GameStats::bestPeg(vector<Score> handScores)
{
    int max = 0;
    for (Score s : handScores) {
        if (s.pegging > max) {
            max = s.pegging;
        }
    }

    return format(max);
}

string GameStats::averagePeg(vector<Score> handScores)
{
    double total = 0;
    for (Score s : handScores) {
        total += s.pegging;
    }
    total /= handScores.size();
    return format(total);
}

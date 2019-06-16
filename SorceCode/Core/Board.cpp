/*--------------------------------------------------------------------
// file name:	Board.cpp
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
#include "Board.h"

/*------------------------------------------------------------------
// name:		checkForPeggingPoints
// description:	given a vector of cards and an int, checks to see if
//              any points are awarded. Points can come from the vector
//              containing same id Cards, cards in a row, nubs, or having
//              sum equal to 15 / 31.
// parameters:	vector of the past cards, int of the current sum.
// returns:		int that is the number of points awarded.
// called by:	pegging
//----------------------------------------------------------------*/
int Board::checkForPeggingPoints(vector<Card> v, int sum) {
    //Not enough Cards to peg any points
    int s = v.size();
    if(s < 2) return 0;

    int score = 0;
    if (sum == 15 || sum == 31) score += 2;

    //Of a Kind Check
    if (v[s - 1].id == v[s - 2].id) {
        if(s > 2 && v[s - 2].id == v[s - 3].id) 
            if(s > 3 && v[s - 3].id == v[s - 4].id) return 12 + score; //4 of a kind
            else return 6 + score; //3 of a kind
        else return 2 + score; //pair
    }

    //Runs Check.
    if (s > 2) {
        vector<int> rowCheck;
        for (int i = 1; i < 4; i++) rowCheck.push_back(v[s - i].id);
        if (inARow(rowCheck)) { //3 in a row
            score += 3;
            int counter = 4;
            while (s >= counter) {
                rowCheck.push_back(v[v.size() - counter].id);
                if (inARow(rowCheck)) score++;
                else break;
            }
        }
    }
    return score;
}

/*------------------------------------------------------------------
// name:		deal
// description:	resets the players hands
// parameters:	none
// returns:		none
// called by:	play
//----------------------------------------------------------------*/
void Board::deal() {
    vector<Card> cards1;
    vector<Card> cards2;
    for (int i = 0; i < 6; i++) {
        cards1.push_back(deck->draw());
        cards2.push_back(deck->draw());
    }
    player1->resetHand(&cards1);
    player2->resetHand(&cards2);
}

/*------------------------------------------------------------------
// name:		inARow
// description:	given a vector checks to see if that vecotor is all in
//              a row that is each number is one larger then the previous.
// parameters:	vector being checked.
// returns:		bool that says wether or not the vector is in a row.
// called by:	checkForPeggingPoints
//----------------------------------------------------------------*/
bool Board::inARow(vector<int> v) {
    sort(v.begin(), v.end());
    for (unsigned int i = 1; i < v.size(); i++)
        if (v[i - 1] + 1 != v[i]) return false;
    return true;
}

/*------------------------------------------------------------------
// name:		pegging
// description:	allows all the players to take turns pegging. This is
//              done through a large while loops that tracks to see if
//              all players have played their hands. It will give points
//              to players who score points here.
// parameters:	a bool representing who starts the pegging stage.
// returns:		a bool that tells the play method if anyone has won.
// called by:	play
//----------------------------------------------------------------*/
void Board::pegging(Score &p1, Score &p2) {
    int sum = 0;
    vector<Card> pastCards;
    bool turn = !this->turn;
    
    //While either player has cards left to play
    while (player1->getPlayingHand().size() > 0 || player2->getPlayingHand().size() > 0) {
        //If neither player can play then reset the pegging
        if (!player1->canPlay(sum) && !player2->canPlay(sum)) {
            if(sum != 31){
                if (!turn) {
                    p2.pegging += 1;
                    player2->addScore(1);
                    cout << player2->getName();
                } else {
                    p1.pegging += 1;
                    player1->addScore(1);
                    cout << player2->getName();;
                }
                cout << " pegged 1 points" << endl;
                if (hasWon()) break;
            }
            sum = 0;
            pastCards.clear();
        }

        Card play;
        if(turn) play = player2->playCard(pastCards, sum);
        else {
            play = player1->playCard(pastCards, sum);
            ClearScreen();
        }
        
        //Player played a valid Card.
        if (play.id != 0) {
            pastCards.push_back(play);
            sum += play.value;
            int score = checkForPeggingPoints(pastCards, sum);
            if (score > 0) {
                if (turn) {
                    p2.pegging += score;
                    player2->addScore(score);
                    cout << player2->getName();
                } else {
                    p1.pegging += score;
                    player1->addScore(score);
                    cout << player2->getName();;
                }
                cout <<" pegged " << score << " points" << endl;
                if(hasWon()) break;
            }
        }
        turn = !turn;
    }

    int score = sum == 31 ? 2 : 1;
    if (turn) {
        p1.pegging += score;
        player1->addScore(score);
    }
    else {
        p2.pegging += score;
        player2->addScore(score);
    }
}

void Board::calculateScores(Score & p1Score, Score & p2Score, Score & cribScore) {
    //Calculate the hand scores
    p1Score = calculateHandScore(player1->getHoldingHand(), cutCard, p1Score.pegging);
    p2Score = calculateHandScore(player2->getHoldingHand(), cutCard, p2Score.pegging);
    cribScore = calculateHandScore(crib, cutCard, 0);

    //Adding the points that each player recived.
    int p1Total = p1Score.getTotalNoPegging();
    int p2Total = p2Score.getTotalNoPegging();
    int cribTotal = cribScore.getTotalNoPegging();

    player1->addScore(p1Total);
    player2->addScore(p2Total);
    turn ? player1->addScore(cribTotal) : player2->addScore(cribTotal);
}

/*------------------------------------------------------------------
// name:		play
// description:	the driver for this program. It loops through the play
//              of the game until one of the players has won the game.
// parameters:	none
// returns:		none
// called by:	main
//----------------------------------------------------------------*/
void Board::play() {
    turn = true;
    Score p1Score;
    Score p2Score;
    Score cribScore;

    while (true) {
        deal();
        
        getCribCards();
        
        cut();
        if (hasWon()) break;

        pegging(p1Score, p2Score);
        if (hasWon()) break;

        calculateScores(p1Score, p2Score, cribScore);
        if (hasWon()) break;
        
        printTable(p1Score, p2Score, cribScore);
        
        stats.addScores(p1Score, p2Score, cribScore, turn);
        turn = !turn;
        deck->resetDeck();
        p1Score = Score();
        p2Score = Score();
        cribScore = Score();
    }
    printTable(p1Score, p2Score, cribScore);
    printWinner();   
    stats.calculateEndGameStats(player1->getName(), player2->getName());
}

/*------------------------------------------------------------------
// name:		printTable
// description:	prints the summary for the round. It clears the console
//              screen, then prints a table that shows where points were
//              given and the total points for each player.
// parameters:	two vectors that are the information of where each player
//              got points.
// returns:		none.
// called by:	play
//----------------------------------------------------------------*/
void Board::printTable(Score p1Scores, Score p2Scores, Score cribScores) {
    ClearScreen();
    cout << "Total Scores" << endl;
    cout << "-------------------" << endl << "| ";
    player1->print();
    cout << "  |" << endl << "| ";
    player2->print();
    cout << "  |" << endl << "-------------------" << endl << endl;

    cout << "Round Scores" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "|Criteria  |";

    string p1Name = player1->getName();
    string p2Name = player2->getName();
    printName(p1Name);
    printName(p2Name);
    if(turn) printName(p1Name + "'s Crib");
    else printName(p2Name + "'s Crib");
    cout << endl;

    cout << "|----------|---------------------|---------------------|---------------------|" << endl;
    cout << "|Hand      | Type    Suit        | Type    Suit        | Type    Suit        |" << endl;

    vector<Card> p1Hand = player1->getHoldingHand();
    vector<Card> p2Hand = player2->getHoldingHand();

    for (unsigned int i = 0; i < p1Hand.size(); i++) 
        cout << "|          | " << p1Hand[i] << "   | " << p2Hand[i] << "   | " << crib[i] << "   |" << endl;
    
    cout << "|----------|---------------------|---------------------|---------------------|" << endl;
    cout << "|Cut       | " << cutCard << "   | " << cutCard << "   | " << cutCard << "   |" << endl;
    cout << "|----------|---------------------|---------------------|---------------------|" << endl;
    cout << "|Scores    | 15's:      " << format(p1Scores.fifteens) << "      | 15's:      " 
         << format(p2Scores.fifteens) << "      | 15's:      " << format(cribScores.fifteens) << "      |" << endl;
    cout << "|          | Runs:      " << format(p1Scores.runs) << "      | Runs:      " 
         << format(p2Scores.runs) << "      | Runs:      " << format(cribScores.runs) << "      |" << endl;
    cout << "|          | Of a Kind: " << format(p1Scores.ofAKind) << "      | Of a Kind: " 
         << format(p2Scores.ofAKind) << "      | Of a Kind: " << format(cribScores.ofAKind) << "      |" << endl;
    cout << "|          | Flush:     " << format(p1Scores.flush) << "      | Flush:     " 
         << format(p2Scores.flush) << "      | Flush:     " << format(cribScores.flush) << "      |" << endl;
    cout << "|          | Nobs:      " << format(p1Scores.nubs) << "      | Nobs:      " 
         << format(p2Scores.nubs) << "      | Nobs:      " << format(cribScores.nubs) << "      |" << endl;
    cout << "|          | Pegging:   " << format(p1Scores.pegging) << "      | Pegging:   "
        << format(p2Scores.pegging) << "      |                     |" << endl;
    cout << "|----------|---------------------|---------------------|---------------------|" << endl;

    cout << "|Total     | " << format(p1Scores.getTotal()) << "                 | "
         << format(p2Scores.getTotal()) << "                 | " << format(cribScores.getTotal()) << "                 |" << endl;

    cout << "------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Press enter to continue.";
    cin.get();
}

void Board::printWinner() {
    ClearScreen();
    if (player1->getScore() > 120 && player2->getScore() > 120)
        if (turn) cout << player2->getName() << " has won the game. Good Job!" << endl;
        else cout << player1->getName() << " has won the game. Good Job!" << endl;
    else if (player1->getScore() > player2->getScore())
        cout << player1->getName() << " has won the game. Good Job!" << endl;
    else cout << player2->getName() << " has won the game. Good Job!" << endl;
    cout << endl;

    cout << endl;
    cout << "Press enter to continue.";
    cin.get();
}

void Board::getCribCards() {
    //Get the crib cards from players and set them to the crib
    crib = player1->getCribCards(turn);
    vector<Card> cards2 = player2->getCribCards(turn);
    crib.insert(crib.end(), cards2.begin(), cards2.end());
}

void Board::cut() {
    cutCard = deck->draw();

    //If the Cut was a Jack then the person whose crib it is gets 2 points
    if (cutCard.id == 11) {
        if (turn) {
            player1->addScore(2);
            cout << "You gained 2 points from the Jack cut" << endl;
        }
        else {
            player2->addScore(2);
            cout << "Computer gained 2 points from the Jack cut" << endl;
        }
    }
}




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
#include <string>
#include <algorithm>

#include "Deck.h"
#include "GlobalHelperFunctions.h"
#include "../Players/Player.h"
#include "../Output/GameStats.h"

using namespace std;

class Board {
public:
    /*------------------------------------------------------------------
    // name:		Board
    // description:	The default constructor for the Board it sets the 
    //              Players and deck.
    // parameters:	none
    // called by:	main
    //----------------------------------------------------------------*/
    Board(Player* p1, Player* p2) : player1(p1), player2(p2), deck(new Deck()), turn(true) {}
    
    /*------------------------------------------------------------------
    // name:		play
    // description:	the driver for this program. It loops through the play
    //              of the game until one of the players has won the game.
    // parameters:	none
    // returns:		none
    // called by:	main
    //----------------------------------------------------------------*/
    void play();

private:
    

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
    int checkForPeggingPoints(vector<Card> pastCards, int sum);

    /*------------------------------------------------------------------
    // name:		deal
    // description:	resets the players hands
    // parameters:	none
    // returns:		none
    // called by:	play
    //----------------------------------------------------------------*/
    void deal();

    /*------------------------------------------------------------------
    // name:		hasWon
    // description:	check to see if either player has won the game.
    // parameters:	none
    // returns:		a bool that is true if someone has won.
    // called by:	play, pegging
    //----------------------------------------------------------------*/
    bool hasWon() { return (player1->getScore() > 120 || player2->getScore() > 120); }

    /*------------------------------------------------------------------
    // name:		inARow
    // description:	given a vector checks to see if that vecotor is all in
    //              a row that is each number is one larger then the previous.
    // parameters:	vector being checked.
    // returns:		bool that says wether or not the vector is in a row.
    // called by:	checkForPeggingPoints
    //----------------------------------------------------------------*/
    bool inARow(vector<int> v);

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
    void pegging(Score &p1, Score &p2);

    void calculateScores(Score &p1Score, Score &p2Score, Score &cribScore);


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
    void printTable(Score p1Scores, Score p2Scores, Score cribScore);

    void printWinner();

    void getCribCards();

    void cut();

    Deck *deck;
    Player *player1;
    Player *player2;
    GameStats stats;
    bool turn;
    Card cutCard;
    vector<Card> crib;
};
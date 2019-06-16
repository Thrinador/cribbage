/*--------------------------------------------------------------------
// file name:	Human.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: The human player for the game of crib. This is where most
//              of the human interaction with the game happens.
// variables:   holdingHand which is the hand that gets calculated at the
//              end of each round. playingHand which is a copy of
//              holdingHand used for pegging. score which is the human's
//              current score.
//--------------------------------------------------------------------*/

#pragma once
#include "Player.h"
#include "../Core/GlobalHelperFunctions.h"

class Human : public Player {
public:
    Human();

    /*------------------------------------------------------------------
    // name:		Human
    // description:	overload constructor that sets the name of the human 
    //              to the string given.
    // parameters:	string which is the name of the player.
    // called by:	Board::intro
    //----------------------------------------------------------------*/
    Human(string name) { this->name = name; }

    /*------------------------------------------------------------------
    // name:		getCribCards
    // description:	given a bool that tells the player whether or not it
    //              is their turn prompts the human to give two cards to
    //              be put in the crib.
    // parameters:	bool that is whose crib it is.
    // returns:		vector of Cards that is the Cards to be put in the Crib
    // called by:	Board::play
    //----------------------------------------------------------------*/
    vector<Card> getCribCards(bool turn);

    /*------------------------------------------------------------------
    // name:		playCard
    // description:	gives the player the past cards that have been played and
    //              the rounds current sum. Wants the player to choose a Card
    //              to play, if they can't play they return a default Card.
    // parameters:	vector of cards that have been played, and int of current sum
    // called by:	Board::pegging
    //----------------------------------------------------------------*/
    Card playCard(vector<Card> pastCards, int sum);

private:

    /*------------------------------------------------------------------
    // name:		printCards
    // description:	makes a table of all the cards in the vector.
    // parameters:	vector of cards to be outputted.
    // called by:	printPegging, getCribCard
    //----------------------------------------------------------------*/
    void printCards(const vector<Card> v);

    /*------------------------------------------------------------------
    // name:		printPegging
    // description:	prints out information tables for when the player is pegging
    // parameters:	the pastCards that have been played and the current sum
    // called by:	playCard
    //----------------------------------------------------------------*/
    void printPegging(vector<Card> pastCards, int sum);
};
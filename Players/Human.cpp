/*--------------------------------------------------------------------
// file name:	Human.cpp
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
#include "Human.h"

using namespace std;

Human::Human() {
    cout << "Enter your name: ";

    string playerName;
    char in = 0;
    for (int i = 0, in = cin.get(); (in != '\n' && in != '\r' && i < 10); in = cin.get(), i++)
        playerName += in;
}

/*------------------------------------------------------------------
// name:		getCribCards
// description:	given a bool that tells the player whether or not it
//              is their turn prompts the human to give two cards to
//              be put in the crib.
// parameters:	bool that is whose crib it is.
// returns:		vector of Cards that is the Cards to be put in the Crib
// called by:	Board::play
//----------------------------------------------------------------*/
vector<Card> Human::getCribCards(bool turn) {
    char in1;
    char in2;
    while (true) {
        ClearScreen();
        if (turn) {
            cout << "It is currently your crib." << endl;
        }
        else {
            cout << "It is currently not your crib." << endl;
        }
        cout << endl;
        printCards(holdingHand);
        cout << "Enter two numbers representing the indexes of" << endl;
        cout << "the cards you want to place in the crib." << endl;

        cin >> in1;
        cin >> in2;
        in1 -= 48;
        in2 -= 48;
        if (in1 >= 0 && in1 < holdingHand.size() && in2 >= 0 && in2 < holdingHand.size() && in1 != in2) {
            break;
        }
    }
    vector<Card> cribIn;
    cribIn.push_back(holdingHand[in1]);
    cribIn.push_back(holdingHand[in2]);

    holdingHand.erase(holdingHand.begin() + in1);
    if (in1 < in2) {
        in2--;
    }
    holdingHand.erase(holdingHand.begin() + in2);

    playingHand = holdingHand;
    return cribIn;
}

/*------------------------------------------------------------------
// name:		playCard
// description:	gives the player the past cards that have been played and
//              the rounds current sum. Wants the player to choose a Card
//              to play, if they can't play they return a default Card.
// parameters:	vector of cards that have been played, and int of current sum
// called by:	Board::pegging
//----------------------------------------------------------------*/
Card Human::playCard(vector<Card> pastCards, int sum) {
    char input;
    if (playingHand.size() == 0) {
        return Card();
    } 
    if (!canPlay(sum)) {
        return Card();
    }
    while(true) {
        printPegging(pastCards, sum);
        cin >> input;
        input -= 48;
        cout << endl;
        if (input >= 0 && input < playingHand.size() && playingHand[input].value + sum <= 31) {
            break;
        }
        ClearScreen();
    }
    Card choice = playingHand[input];
    playingHand.erase(playingHand.begin() + input);
    return choice;
}

/*------------------------------------------------------------------
// name:		printCards
// description:	makes a table of all the cards in the vector.
// parameters:	vector of cards to be outputted.
// called by:	printPegging, getCribCard
//----------------------------------------------------------------*/
void Human::printCards(const vector<Card> v) {
    cout << "Your Cards" << endl;
    cout << "---------------------------" << endl;
    cout << "|Index | Card             |" << endl;
    cout << "|------|------------------|" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "| " << i << "    | " << v[i] << "|" << endl;
    }
    cout << "---------------------------" << endl;
}

/*------------------------------------------------------------------
// name:		printPegging
// description:	prints out information tables for when the player is pegging
// parameters:	the pastCards that have been played and the current sum
// called by:	playCard
//----------------------------------------------------------------*/
void Human::printPegging(vector<Card> pastCards, int sum) {
    cout << "Pegging" << endl;
    cout << "---------------------------" << endl;
    for (int i = pastCards.size() - 1; i >= 0; i--) {
        cout << "| " << pastCards[i] << "       |" << endl;
    }
    cout << "|-------------------------|" << endl;
    cout << "| Sum  " << format(sum) << "                 |" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    printCards(playingHand);

    cout << "Enter card index to play: ";
}
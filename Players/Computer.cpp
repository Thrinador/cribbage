/*--------------------------------------------------------------------
// file name:	Computer.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A simple computer, that plays cribbage.
// variables:   holdingHand which is the hand that gets calculated at the
//              end of each round. playingHand which is a copy of
//              holdingHand used for pegging. score which is the computer's
//              current score.
//--------------------------------------------------------------------*/

#pragma once
#include "Computer.h"

/*------------------------------------------------------------------
// name:		getCribCards
// description:	gives the computer a bool that represents whether or not it
//              is their crib and asks them for a vector of cards to be
//              put in the crib.
// parameters:	bool of whose crib it is.
// called by:	Board::play
//----------------------------------------------------------------*/
vector<Card> Computer::getCribCards(bool turn) {
    vector<Card> cribCards;
    cribCards.push_back(holdingHand.at(0));
    cribCards.push_back(holdingHand.at(1));

    holdingHand.erase(holdingHand.begin());
    holdingHand.erase(holdingHand.begin());

    playingHand = holdingHand;
    return cribCards;
}

/*------------------------------------------------------------------
// name:		playCard
// description:	gives the computer the past cards that have been played and
//              the rounds current sum. Computer always plays the first card.
// parameters:	vector of cards that have been played, and int of current sum
// called by:	Board::pegging
//----------------------------------------------------------------*/
Card Computer::playCard(vector<Card> pastCards, int sum) {
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card choice = playingHand[i];
        if (choice.value + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return choice;
        }
    }
    //Can't Play
    return Card();
}

vector<Card> Computer::getPartialHand(int i, int j) {
    vector<Card> partialHand;

    for (int k = 0; k < holdingHand.size(); k++) {
        if (k == i || k == j) continue;
        partialHand.push_back(holdingHand[k]);
    }

    return partialHand;
}

int Computer::calculatePartialHandScore(vector<Card> hand) {
    return score15(hand) + scoreFlush(hand) + scoreRuns(hand) + scoreOfAKind(hand);
}

double Computer::calculateCutValue(vector<Card> partialHand) {
    Deck d;
    double expectedValue = 0;
    for (int i = 0; i < 52; i++) {
        Card c = d.draw();
        if (cardInHand(c, partialHand)) {
            Score s = calculateHandScore(partialHand, c, 0);
            expectedValue += s.getTotalNoPegging();
        }
    }

    return expectedValue / 46;
}

double Computer::calculateCribCardValue(int i, int j) {
    return 0;
}

bool Computer::cardInHand(Card c, vector<Card> hand)
{
    for (Card handCard : hand) {
        if (c.id == handCard.id) {
            return true;
        }
    }

    return false;
}

int scoreFlush(const vector<Card> hand)
{
    for (int i = 1; i < hand.size(); i++) 
        if (hand[i - 1].suit != hand[i].suit) return 0;

    return 4;
}
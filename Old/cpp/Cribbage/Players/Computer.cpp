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
    Card c = pegAnyCard(pastCards, sum);
    if (c.id != 0) return c;

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
    int probs[MAX_DECK_VALUE];
    for (int i = 0; i < MAX_DECK_VALUE; i++) probs[i] = 4;

    for (Card c : partialHand) probs[c.id - 1]--;

    double expectedValue = 0;
    for (int value = 1; value <= MAX_DECK_VALUE; value++) {
        Card c(value, 0);
        if (cardInHand(c, partialHand)) {
            Score s = calculateHandScore(partialHand, c, 0);
            expectedValue += s.getTotalNoPegging() * probs[c.id - 1];
        }
    }
    return expectedValue / 46;
}

double Computer::calculateCribCardValue(Card c1, Card c2) {
    double value = 0;
    if (c1.id == c2.id) value += 3;
    if (c1.value + c2.value == 15) value += 3;
    if (c1.id - c2.id == 1 || c1.id - c2.id == -1) value += 2;
    if (c1.suit == c2.suit) value += .1;

    return value;
}

bool Computer::cardInHand(Card c, vector<Card> hand) {
    for (Card handCard : hand) if (c == handCard) return true;
    
    return false;
}

Card Computer::pegRun(vector<Card> pastCards, int sum) {
    //Try and get a run
    if (pastCards.size() >= 2) {
        for (int length = pastCards.size(); length >= 2; length--) {
            vector<Card> partPastCards(length);
            std::copy(pastCards.begin(), pastCards.begin() + length, partPastCards.begin());
            int cardType = checkCardsType(partPastCards);
            //Edge Case
            if (cardType == 1) {
                for (int i = 0; i < playingHand.size(); i++) {
                    Card choice = playingHand[i];
                    if (choice.value + sum <= 31 && (choice.id - partPastCards[0].id == -1 || choice.id - partPastCards[partPastCards.size() - 1].id == 1)) {
                        playingHand.erase(playingHand.begin() + i);
                        return choice;
                    }
                }
            }
            //Middle Case
            else if (cardType == 2) {
                int holeId = 0;
                for (int i = 1; i < partPastCards.size(); i++) {
                    if (partPastCards[i].id - partPastCards[i - 1].id == 2)
                        holeId = partPastCards[i].id - 1;
                }

                if (holeId + sum <= 31) {
                    for (int i = 0; i < playingHand.size(); i++) {
                        Card choice = playingHand[i];
                        if (choice.id == holeId) {
                            playingHand.erase(playingHand.begin() + i);
                            return choice;
                        }
                    }
                }
            }
        }
    }
    return Card();
}

Card Computer::pegPair(vector<Card> pastCards, int sum) {
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card c = playingHand[i];
        if (c.id == pastCards.back().id) {
            if (c.value + sum < 31) {
                playingHand.erase(playingHand.begin() + i);
                return c;
            }
            else {
                break;
            }
        }
    }
    return Card();
}

Card Computer::peg15Or31(vector<Card> pastCards, int sum) {
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card c = playingHand[i];
        if (c.value + sum == 15 || c.value + sum == 31) {
            playingHand.erase(playingHand.begin() + i);
            return c;
        }
    }
    return Card();
}

Card Computer::pegAnyCard(vector<Card> pastCards, int sum) {
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card choice = playingHand[i];
        if (choice.value + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return choice;
        }
    }
    return Card();
}


int Computer::checkCardsType(vector<Card>& partPastCards) {
    sort(partPastCards);
    bool seenHole = false;
    for (int i = 1; i < partPastCards.size(); i++) {
        if (partPastCards[i].id - partPastCards[i - 1].id == 2) {
            if (seenHole) return 0;

            seenHole = true;
        }
        else if (partPastCards[i].id - partPastCards[i - 1].id != 1) {
            return 0;
        }
    }

    if (seenHole) return 2;
    return 1;
}

int scoreFlush(const vector<Card> hand) {
    for (int i = 1; i < hand.size(); i++) 
        if (hand[i - 1].suit != hand[i].suit) return 0;

    return 4;
}
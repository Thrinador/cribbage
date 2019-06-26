#pragma once
#include "MediumBot.h"

vector<Card> MediumBot::getCribCards(bool turn) {
    int bestScore = 0;
    int bestI = 0;
    int bestJ = 1;

    for (unsigned int i = 0; i < holdingHand.size() - 1; i++) {
        for (unsigned int j = i + 1; j < holdingHand.size(); j++) {
            vector<Card> partialHand = getPartialHand(i, j);

            int score = calculatePartialHandScore(partialHand);
            if (score > bestScore) {
                bestScore = score;
                bestI = i;
                bestJ = j;
            }
        }
    }

    vector<Card> cribCards;
    cribCards.push_back(holdingHand.at(bestI));
    cribCards.push_back(holdingHand.at(bestJ));

    holdingHand.erase(holdingHand.begin() + bestJ);
    holdingHand.erase(holdingHand.begin() + bestI);

    playingHand = holdingHand;
    return cribCards;
}

Card MediumBot::playCard(vector<Card> pastCards, int sum) {
    if (playingHand.size() == 0) return Card();

    //If it needs to start, then always plays first card.
    if (sum == 0) {
        Card choice = playingHand[0];
        playingHand.erase(playingHand.begin());
        return choice;
    }

    //Try to get pair
    Card c = pegPair(pastCards, sum);
    if (c.id != 0) return c;

    //Try to get either 15 or 31
    c = peg15Or31(pastCards, sum);
    if (c.id != 0) return c;

    //Play any card
    c = pegAnyCard(pastCards, sum);
    if (c.id != 0) return c;

    //Can't play
    return Card();
}
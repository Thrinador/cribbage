#pragma once
#include "HardBot.h"

vector<Card> HardBot::getCribCards(bool turn) {
    double bestScore = 0;
    int bestI = 0;
    int bestJ = 1;

    for (unsigned int i = 0; i < holdingHand.size() - 1; i++) {
        for (unsigned int j = i + 1; j < holdingHand.size(); j++) {
            vector<Card> partialHand = getPartialHand(i, j);

            //The score is calculated in three parts. First the raw hand value is added. Next the potential value of
            //the cut is added to the hand. Finally, the value of the cards given to the crib are either added or 
            //subtracted depending on whether it is your crib.
            double score = calculatePartialHandScore(partialHand) + calculateCutValue(partialHand);
            if(turn == this->turn) score += calculateCribCardValue(i, j);
            else score -= calculateCribCardValue(i, j);

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

Card HardBot::playCard(vector<Card> pastCards, int sum) {
    if (playingHand.size() == 0) {
        return Card();
    }

    //If it needs to start, then always plays first card.
    //TODO add some logic about what card is a good one to start with.
    if (sum == 0) {
        Card choice = playingHand[0];
        playingHand.erase(playingHand.begin());
        return choice;
    }

    //Try and get a run
    //TODO

    //Try to get pair
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

    //Try to get either 15 or 31
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card c = playingHand[i];
        if (c.value + sum == 15 || c.value + sum == 31) {
            playingHand.erase(playingHand.begin() + i);
            return c;
        }
    }

    //Play any card
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card choice = playingHand[i];
        if (choice.value + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return choice;
        }
    }

    //Can't play
    return Card();
}
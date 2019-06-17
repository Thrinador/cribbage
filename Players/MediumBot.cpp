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
    if (playingHand.size() == 0) {
        return Card();
    }

    //If it needs to start, then always plays first card.
    if (sum == 0) {
        Card choice = playingHand[0];
        playingHand.erase(playingHand.begin());
        return choice;
    }

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
#pragma once

#include "Player.h"

class HardBot : public Player {

public:
    HardBot() { this->name = "Medium Bot"; }

    vector<Card> getCribCards(bool turn);

    Card playCard(vector<Card> pastCards, int sum);
};
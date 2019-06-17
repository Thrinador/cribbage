#pragma once

#include "Computer.h"

class HardBot : public Computer {

public:
    HardBot() { this->name = "Hard Bot"; }

    vector<Card> getCribCards(bool turn);

    Card playCard(vector<Card> pastCards, int sum);
};
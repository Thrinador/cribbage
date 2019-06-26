#pragma once

#include "Computer.h"
#include <algorithm>

class HardBot : public Computer {

public:
    HardBot() { this->name = "Hard Bot"; }

    vector<Card> getCribCards(bool turn);

    Card playCard(vector<Card> pastCards, int sum);
};
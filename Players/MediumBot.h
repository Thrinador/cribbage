#pragma once
#include "Computer.h"

class MediumBot : public Computer {

public:
    MediumBot() { this->name = "Medium Bot"; }

    vector<Card> getCribCards(bool turn);

    Card playCard(vector<Card> pastCards, int sum);
};
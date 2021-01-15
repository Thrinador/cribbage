#pragma once
#include "../Players/Player.h"
#include "../Players/MediumBot.h"

bool simulating = true;

#if (simulating)
int numberOfGames;
bool doesPlayer1AlwaysStart;
#endif

Player* player1 = new MediumBot();
Player* player2 = new MediumBot();

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "MoveData.h"

void playGame(MoveData &data);
void processMove(int userMove, int computerMove, MoveData &data);
std::string numToName(int i);

#endif // GAME_H_INCLUDED

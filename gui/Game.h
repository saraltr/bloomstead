#pragma once

#include <vector>
#include "State.h"

// create and initialize a 2D garden grid of the given size
std::vector<std::vector<Plant>> CreateGarden(int rows, int cols);

// create the list of menu options, based on player energy
std::vector<MenuOption> CreateMenuOptions(const PlayerState &player);

// update the "enabled" state of menu options depending on current player energy
void UpdateMenuOptions(std::vector<MenuOption> &menuOptions, const PlayerState &player);

// initialize player state (level, energy, etc.)
void InitPlayer(PlayerState &player);

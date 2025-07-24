#pragma once
#include <vector>
#include "State.h"

// renders the garden grid and plant icons
void DrawGarden(const std::vector<std::vector<Plant>> &garden, const PlayerState &player);

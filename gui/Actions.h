#pragma once
#include <vector>
#include "State.h"

// perform a gameplay action based on the label
void PerformAction(const std::string &label, std::vector<std::vector<Plant>> &garden, PlayerState &player, bool &running);

#pragma once
#include "raylib.h"
#include <string>

enum GrowthStage
{
    EMPTY = 0,
    SEEDLING,
    BLOOMING,
    MATURE,
    DEAD
};

struct Plant
{
    GrowthStage stage = EMPTY;
    bool watered = false;
    bool pests = false;
    bool weeds = false;
    int daysNeglected = 0;
};

struct MenuOption
{
    std::string label;
    std::string tooltip;
    bool enabled;
    Rectangle rect;
};

struct PlayerState
{
    int energy = 3;
    int maxEnergy = 3;
    int level = 1;
    int seedsCollected = 0;
};

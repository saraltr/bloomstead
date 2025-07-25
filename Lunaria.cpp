#include "Lunaria.h"
#include <iostream>

// constructor sets name, value, and rarity using base plant constructor
Lunaria::Lunaria() : Plant("Lunaria", 20, "Rare") {}

// returns how much water is needed to grow to the next stage
// lunaria is rare so  requires 5 water per stage to grow
int Lunaria::nextStage() const
{
    return 5;
}

// display string for lunaria
std::string Lunaria::getType() const
{
    return "🌟 Lunaria";
}

// defines the growth logic
void Lunaria::grow()
{
    // grows only if no pests/weeds and enough water
    if (!hasPests && !hasWeeds && waterLevel >= nextStage())
    {
        // advance stage if not already mature
        if (stage != GrowthStage::Mature)
        {
            stage = static_cast<GrowthStage>(static_cast<int>(stage) + 1);
            waterLevel -= nextStage(); // consume water for growth
        }
    }
}
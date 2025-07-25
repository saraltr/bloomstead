#include "Carrot.h"

// constructor sets name, value, and rarity using the base plant constructor
Carrot::Carrot() : Plant("Carrot", 5, "Common") {}

// returns the display string for carrot
std::string Carrot::getType() const
{
    return "🥕 Carrot";
}

// defines the growth logic
void Carrot::grow()
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

// returns how much water is needed to grow to the next stage
int Carrot::nextStage() const
{
    return 1; // only needs 1 water to grow a stage
}

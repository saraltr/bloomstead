#include "Rose.h"
#include <iostream>

Rose::Rose() : Plant("Rose") {}

int Rose::nextStage() const
{
    return 3;
}

std::string Rose::getType() const
{
    return "🌹 Rose";
}

void Rose::grow()
{
    if (!hasPests && !hasWeeds && waterLevel >= nextStage())
    {
        if (stage != GrowthStage::Mature)
        {
            stage = static_cast<GrowthStage>(static_cast<int>(stage) + 1);
            waterLevel -= nextStage();
        }
    }
}
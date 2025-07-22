#include "Carrot.h"

Carrot::Carrot() : Plant("Carrot") {}

std::string Carrot::getType() const
{
    return "🥕 Carrot";
}

void Carrot::grow()
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

int Carrot::nextStage() const
{
    return 1; // Only needs 1 water to grow a stage
}

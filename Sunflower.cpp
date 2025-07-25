#include "Sunflower.h"

Sunflower::Sunflower() : Plant("Sunflower", 5, "Common") {}

std::string Sunflower::getType() const
{
    return "🌻 Sunflower";
}

void Sunflower::grow()
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

int Sunflower::nextStage() const
{
    return 1; // only needs 1 water to grow a stage
}

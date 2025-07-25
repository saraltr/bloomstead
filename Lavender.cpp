#include "Lavender.h"
#include <iostream>

Lavender::Lavender() : Plant("Lavender", 10, "Uncommon") {}

int Lavender::nextStage() const
{
    return 3;
}

std::string Lavender::getType() const
{
    return "🪻 Lavender";
}

void Lavender::grow()
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
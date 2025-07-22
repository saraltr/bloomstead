#include "Lunaria.h"
#include <iostream> 

Lunaria::Lunaria() : Plant("Lunaria") {}

int Lunaria::nextStage() const
{
    return 5;
}

std::string Lunaria::getType() const
{
    return "🌟 Lunaria";
}

void Lunaria::grow(){
    if (!hasPests && !hasWeeds && waterLevel >= nextStage())
    {
        if (stage != GrowthStage::Mature)
        {
            stage = static_cast<GrowthStage>(static_cast<int>(stage) + 1);
            waterLevel -= nextStage();
        }
    }
}
#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "Plant.h"

class Sunflower : public Plant
{
public:
    Sunflower();
    void grow() override;
    std::string getType() const override;
    int nextStage() const override;
};

#endif
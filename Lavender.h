#ifndef LAVENDER_H
#define LAVENDER_H

#include "Plant.h"

// carrot, rose, lavender, lunaria and sunflower classes inherits from plant
class Lavender : public Plant
{
public:
    Lavender();
    void grow() override;
    std::string getType() const override;
    int nextStage() const override;
};

#endif
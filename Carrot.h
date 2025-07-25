#ifndef CARROT_H
#define CARROT_H

// base plant class
#include "Plant.h"

// carrot, rose, lavender, lunaria and sunflower classes inherits from plant
class Carrot : public Plant
{
public:
    // constructor
    Carrot();

    // returns the type of the plant
    std::string getType() const override;

    // defines how the plant grows through stages
    void grow() override;

    // returns the next growth stage
    int nextStage() const override;
};

#endif

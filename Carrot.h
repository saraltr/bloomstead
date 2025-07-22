#ifndef CARROT_H
#define CARROT_H

#include "Plant.h"

class Carrot : public Plant
{
public:
    Carrot();
    std::string getType() const override;
    void grow() override;
    int nextStage() const override;
};

#endif

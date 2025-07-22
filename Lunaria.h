#ifndef LUNARIA_H
#define LUNARIA_H

#include "Plant.h"

class Lunaria : public Plant
{
public:
    Lunaria();
    void grow() override;
    std::string getType() const override;
    int nextStage() const override;
};

#endif
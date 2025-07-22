#ifndef ROSE_H
#define ROSE_H

#include "Plant.h"

class Rose : public Plant
{
public:
    Rose();
    void grow() override;
    std::string getType() const override;
    int nextStage() const override;
};

#endif
#include "Plant.h"
#include <iostream>
using namespace std;

// constructor with all default values for a new plant
Plant::Plant(const std::string &name, int price, const std::string &rarity)
    : name(name), price(price), rarity(rarity), planted(false), waterLevel(0), stage(GrowthStage::Seedling),
      hasPests(false), hasWeeds(false),
      pestDamageCount(0), weedDamageCount(0), alive(true)
{
}

// checks if pest or weed damage has reached fatal threshold
void Plant::checkDeath()
{
    if (pestDamageCount >= damageThreshold || weedDamageCount >= damageThreshold)
    {
        alive = false;
        stage = GrowthStage::Dead;
        cout << "🪦" << name << " has died due to ";
        if (pestDamageCount >= damageThreshold)
            cout << "severe pest damage";
        if (pestDamageCount >= damageThreshold && weedDamageCount >= damageThreshold)
            cout << " and ";
        if (weedDamageCount >= damageThreshold)
            cout << "severe weed damage";
        cout << ".\n";
    }
}

// logic for growing to the next stage
void Plant::grow()
{
    if (!planted)
    {
        cout << name << " is not planted yet.\n";
        return;
    }
    if (!alive)
    {
        cout << "🪦 " << name << " is dead and cannot grow.\n";
        return;
    }

    if (!hasPests && !hasWeeds && waterLevel >= nextStage())
    {
        if (stage != GrowthStage::Mature)
        {
            stage = static_cast<GrowthStage>(static_cast<int>(stage) + 1);
            waterLevel -= nextStage();
        }
    }
    else if (hasPests || hasWeeds)
    {
        cout << name << " couldn't grow due to "
             << (hasPests ? "pests" : "")
             << (hasPests && hasWeeds ? " and " : "")
             << (hasWeeds ? "weeds" : "") << ".\n";
    }
}

// adds water to the plant
void Plant::water()
{
    if (!alive)
        return;
    waterLevel++;
}

// moves growth stage one step backward if the plant was not treated
void Plant::reduceGrowth()
{
    if (!alive)
        return;

    if (stage != GrowthStage::Seedling)
    {
        stage = static_cast<GrowthStage>(static_cast<int>(stage) - 1);
    }
}

int Plant::getWaterLevel() const
{
    return waterLevel;
}

GrowthStage Plant::getGrowthStage() const
{
    return stage;
}

// returns a string description of current growth stage
std::string Plant::getStageName() const
{
    switch (stage)
    {
    case GrowthStage::Seedling:
        return "Seedling 🌱";
    case GrowthStage::Blooming:
        return "Blooming 🌸";
    case GrowthStage::Mature:
        return "Mature 🌼";
    case GrowthStage::Dead:
        return "Dead 🪦";
    default:
        return "Unknown";
    }
}

// base class always needs 1 water to grow
int Plant::nextStage() const
{
    return 1;
}

// base plant type string
std::string Plant::getType() const
{
    return "🌿 Generic Plant";
}

// pests functions
void Plant::applyPestDamage()
{
    hasPests = true;
}

void Plant::increasePestDamage()
{
    if (!alive)
        return;

    pestDamageCount++;
    checkDeath();
}

void Plant::clearPests()
{
    hasPests = false;
    pestDamageCount = 0;
}

bool Plant::checkPests() const
{
    return hasPests;
}

// weeds functions
void Plant::applyWeedGrowth()
{
    hasWeeds = true;
}

void Plant::increaseWeedDamage()
{
    if (!alive)
        return;

    weedDamageCount++;
    checkDeath();
}

void Plant::clearWeeds()
{
    hasWeeds = false;
    weedDamageCount = 0;
}

bool Plant::checkWeeds() const
{
    return hasWeeds;
}

// returns whether the plant is still alive
bool Plant::isAlive() const
{
    return alive;
}

// resets the plant to its initial state
void Plant::reset()
{
    waterLevel = 0;
    stage = GrowthStage::Seedling;
    hasPests = false;
    hasWeeds = false;
    pestDamageCount = 0;
    weedDamageCount = 0;
    alive = true;
}

// marks the plant as planted (so it can start growing)
void Plant::plant()
{
    planted = true;
}

// checks if the plant has been planted
bool Plant::isPlanted() const
{
    return planted;
}

#include "Garden.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

// destructor to delete all dynamically allocated plants to prevent memory leaks
Garden::~Garden()
{
    for (auto p : plants)
        delete p;
}

// adds a new plant pointer to the garden's plant list
void Garden::addPlant(Plant *plant)
{
    plants.push_back(plant);
}

// waters every plant 
void Garden::waterAllPlants()
{
    for (auto p : plants)
        p->water();
}

// triggers growth for each plant
void Garden::growAllPlants()
{
    for (auto p : plants)
        p->grow();
}

// returns true if any plant in the garden currently has pests
bool Garden::hasPests() const
{
    for (const auto &plant : plants)
    {
        if (plant->checkPests())
            return true;
    }
    return false;
}

// returns true if any plant in the garden currently has weeds
bool Garden::hasWeeds() const
{
    for (const auto &plant : plants)
    {
        if (plant->checkWeeds())
            return true;
    }
    return false;
}

// displays information about each planted plant
void Garden::display() const
{
    int displayIndex = 1;
    for (const auto &plant : plants)
    {
        if (!plant->isPlanted())
            continue; // skip plants not yet planted

        std::cout << displayIndex++ << ". " << plant->getType()
                  << " | Water: " << plant->getWaterLevel()
                  << " | Stage: " << plant->getStageName()
                  << (plant->checkPests() ? " | 🐛 Pests" : "")
                  << (plant->checkWeeds() ? " | 🌾 Weeds" : "")
                  << "\n";
    }
}

// applies pest damage to plants that are alive with a random chance per plant
void Garden::pestsDamage()
{
    for (auto p : plants)
    {
        if (!p->isAlive())
            continue;

        int damageChance = rand() % 100;
        if (damageChance < 60) // 60% chance to apply pest damage
        {
            p->applyPestDamage();
            std::cout << "🐛 " << p->getType() << " has pests!\n";
        }
    }
}

// applies weed growth to alive plants with a random chance
void Garden::weedsGrow()
{
    for (auto p : plants)
    {
        if (!p->isAlive())
            continue;

        int weedChance = rand() % 100;
        if (weedChance < 50) // 50% chance weeds grow around plant
        {
            p->applyWeedGrowth();
            std::cout << "🌾 Weeds grew around " << p->getType() << "!\n";
        }
    }
}

// removes pests from plants that currently have them
void Garden::treatAllPests()
{
    for (auto p : plants)
    {
        if (p->checkPests())
        {
            p->clearPests();
            std::cout << "🧼 Removed pests from " << p->getType() << ".\n";
        }
    }
}

// removes weeds from plants that currently have them
void Garden::removeAllWeeds()
{
    for (auto p : plants)
    {
        if (p->checkWeeds())
        {
            p->clearWeeds();
            std::cout << "🧽 Removed weeds from " << p->getType() << ".\n";
        }
    }
}

// returns reference to the vector containing all plants in the garden
std::vector<Plant *> &Garden::getPlants()
{
    return plants;
}

// removes dead plants from the garden and deletes them to free memory
// returns the count of removed plants
int Garden::removeDeadPlants()
{
    int countRemoved = 0;
    auto it = plants.begin();

    while (it != plants.end())
    {
        if (!(*it)->isAlive())
        {
            delete *it;            // free plant memory
            it = plants.erase(it); // remove from vector and update iterator
            countRemoved++;
        }
        else
        {
            ++it;
        }
    }
    return countRemoved;
}

// checks if garden has space for new plants
// returns true if any dead plants can be replaced or garden size is less than max capacity (5)
bool Garden::hasSpace() const
{
    for (const auto &plant : plants)
    {
        if (!plant->isAlive())
            return true; // space found because of dead plant
    }
    return plants.size() < 5; // otherwise checks if garden is under max capacity
}

// harvests mature plants, adds seeds to player inventory & removes harvested plants from garden
void Garden::harvestMaturePlants(Player &player)
{
    bool harvested = false;
    auto it = plants.begin();

    while (it != plants.end())
    {
        Plant *plant = *it;
        if (plant->isAlive() && plant->getGrowthStage() == GrowthStage::Mature)
        {
            std::string seedName = plant->getName();

            player.addSeed(seedName); // add harvested seed to player's inventory
            std::cout << "🌼 You harvested a " << seedName << " seed!\n";

            delete plant;          // free memory of harvested plant
            it = plants.erase(it); // remove plant from garden vector
            harvested = true;
        }
        else
        {
            ++it;
        }
    }

    if (!harvested)
    {
        std::cout << "❌ No mature plants available for harvest.\n";
    }
}

#ifndef GARDEN_H
#define GARDEN_H

#include <vector>
#include "Plant.h"
#include "Player.h"

// class representing the garden to hold and manage plants
class Garden
{
private:
    std::vector<Plant *> plants; // container to store pointers to plants in the garden

public:
    ~Garden(); // destructor to clean up allocated plants

    std::vector<Plant *> &getPlants(); // returns reference to the vector of plants

    void addPlant(Plant *plant); // adds a new plant pointer to the garden

    void waterAllPlants(); // waters all plants in the garden

    void growAllPlants(); // triggers growth update for all plants

    void pestsDamage(); // applies pest damage effects to plants

    void weedsGrow(); // triggers weed growth around plants

    void removeAllWeeds(); // removes weeds from all plants

    void treatAllPests(); // removes pests from all plants

    void display() const; // displays the current state of the garden

    bool hasPests() const; // returns true if any plant has pests

    bool hasWeeds() const; // returns true if any plant has weeds

    bool hasSpace() const; // returns true if garden has room for more plants

    int removeDeadPlants(); // removes dead plants from garden and returns count removed

    void harvestMaturePlants(Player &player); // harvests seeds from mature plants and adds them to the player's inventory
};

#endif

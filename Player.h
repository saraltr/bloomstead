#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <map>
#include <string>

class Player
{
private:
    // stores seed types and their quantities
    std::map<std::string, int> seedInventory;
    // player money
    int money;

public:
    Player();

    // adds a seed to inventory
    void addSeed(std::string type);
    // checks if player has at least one seed
    bool hasSeed(std::string type) const;
    // uses a seed
    void useSeed(std::string type);
    // displays current seed inventory with counts
    void showInventory() const;
    // returns seed type by inventory position
    std::string getSeedByIndex(int index) const;
    // checks if inventory is empty
    bool isInventoryEmpty() const;

    // current amount of money
    int getMoney() const;

    // adds money to the player's total
    void addMoney(int amount);

    // deducts money from the player
    void deductMoney(int amount);
};

#endif
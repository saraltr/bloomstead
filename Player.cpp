#include "Player.h"
#include <iostream>

// constructor initializes money to zero and empty inventory
Player::Player() : money(0) {}

// increases the count of a seed type or adds it if not present
void Player::addSeed(std::string type)
{
    seedInventory[type]++;
    std::cout << "🌱 Added " << type << " seed to your inventory.\n";
}

// checks if the inventory contains at least one seed of the given type
bool Player::hasSeed(std::string type) const
{
    auto it = seedInventory.find(type);
    return it != seedInventory.end() && it->second > 0;
}

// uses a seed, reduces count & removes type if count reaches zero
void Player::useSeed(std::string type)
{
    if (hasSeed(type))
    {
        seedInventory[type]--;
        std::cout << "🌿 Planted one " << type << " seed.\n";
        if (seedInventory[type] == 0)
        {
            seedInventory.erase(type);
        }
    }
    else
    {
        std::cout << "⚠️ You don't have any " << type << " seeds.\n";
    }
}

// returns true if no seeds are in the inventory
bool Player::isInventoryEmpty() const
{
    return seedInventory.empty();
}

// prints the player's seed inventory
void Player::showInventory() const
{
    std::cout << "\n🎒 Seed Inventory:\n";
    if (seedInventory.empty())
    {
        std::cout << "  (empty)\n";
        return;
    }

    int index = 1;
    for (const auto &pair : seedInventory)
    {
        std::cout << "  " << index << ". " << pair.first << ": " << pair.second << "\n";
        index++;
    }
}

// retrieves a seed type based on a 1 based index in the inventory map
// returns an empty string if index is invalid
std::string Player::getSeedByIndex(int index) const
{
    if (index < 1 || index > (int)seedInventory.size())
        return "";

    int current = 1;
    for (const auto &pair : seedInventory)
    {
        if (current == index)
            return pair.first;
        current++;
    }
    return "";
}
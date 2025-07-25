#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <vector>
#include "Player.h"
#include "Plant.h"
#include "Garden.h"

struct MarketItem
{
    std::string name;
    int price;
    std::string rarity;
};

class Market
{
private:
    std::vector<MarketItem> shopItems;

public:
    Market();
    void displayShop(Player &player) const;
    void buySeed(Player &player, int choice);
    void sellPlant(Player &player, int choice);
    void visitMarket(Player &player, Garden &garden);
};

#endif

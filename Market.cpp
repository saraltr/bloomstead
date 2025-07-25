#include "Market.h"
#include <iostream>

// constructor with available seeds to sell
Market::Market()
{
    shopItems.push_back({"Carrot", 5, "Common"});
    shopItems.push_back({"Rose", 10, "Uncommon"});
    shopItems.push_back({"Sunflower", 5, "Common"});
    shopItems.push_back({"Lavender", 10, "Uncommon"});
    shopItems.push_back({"Lunaria", 20, "Rare"});
}

// shop menu
void Market::displayShop(Player &player) const
{
    std::cout << "\n🛒 Welcome to the Garden Shop:\n";
    std::cout << "\n💰 You have $ " << player.getMoney() << "\n";
    // display the different seeds available to purchase
    for (size_t i = 0; i < shopItems.size(); ++i)
    {
        std::cout << i + 1 << ". " << shopItems[i].name
                  << " (" << shopItems[i].rarity
                  << ") - $" << shopItems[i].price << "\n";
    }
}

// let the user buy desired seed
void Market::buySeed(Player &player, int choice)
{
    // check if choice is within valid range
    if (choice < 1 || choice > (int)shopItems.size())
    {
        std::cout << "❌ Invalid choice.\n";
        return;
    }

    // get selected item
    const MarketItem &item = shopItems[choice - 1];

    // check if player has enough money
    if (player.getMoney() >= item.price)
    {
        // add seed to inventory and deduct money
        player.addSeed(item.name);
        player.deductMoney(item.price);
        std::cout << "✅ Bought " << item.name << " seed for $" << item.price << ".\n";
    }
    else
    {
        std::cout << "💰 Not enough money.\n";
    }
}

// sell a plant from the player's inventory
void Market::sellPlant(Player &player, int choice)
{
    // get seed name from inventory by index
    std::string seedName = player.getSeedByIndex(choice);

    // check for invalid input
    if (seedName.empty())
    {
        std::cout << "❌ Invalid choice.\n";
        return;
    }

    // make sure player actually has that seed
    if (!player.hasSeed(seedName))
    {
        std::cout << "⚠️ You don't have any " << seedName << " seeds to sell.\n";
        return;
    }

    // look up the price of the seed from shopItems
    int price = 0;
    for (const MarketItem &item : shopItems)
    {
        if (item.name == seedName)
        {
            price = item.price;
            break;
        }
    }

    // if no matching price found, return
    if (price == 0)
    {
        std::cout << "❌ Cannot sell unknown seed type: " << seedName << "\n";
        return;
    }

    // remove one seed and add money to player
    player.useSeed(seedName);
    player.addMoney(price);
    std::cout << "✅ Sold 1 " << seedName << " seed for $" << price << ".\n";
}

// main market loop for buying and selling seeds/plants
void Market::visitMarket(Player &player, Garden &garden)
{
    bool inMarket = true;
    while (inMarket)
    {
        // display market menu and player's current money
        std::cout << "\n--- Market Menu ---\n";
        std::cout << "\n💰 You have $" << player.getMoney() << "\n";
        std::cout << "\n1. Buy seeds 🌱\n";
        std::cout << "2. Sell plants from your inventory 💐\n";
        std::cout << "3. Exit market 🔙\n";
        std::cout << "Enter your choice: ";

        int marketChoice;
        std::cin >> marketChoice;

        switch (marketChoice)
        {
        case 1:
            // buying seeds
            displayShop(player);
            std::cout << "Enter seed number to buy (0 to cancel): ";
            int buyChoice;
            std::cin >> buyChoice;
            if (buyChoice != 0)
            {
                buySeed(player, buyChoice);
            }
            break;
        case 2:
            // selling seeds
            player.showInventory();
            std::cout << "Enter plant number to sell (0 to cancel): ";
            int sellChoice;
            std::cin >> sellChoice;
            if (sellChoice != 0)
            {
                sellPlant(player, sellChoice);
            }
            break;
        case 3:
            // exit market
            inMarket = false;
            break;
        default:
            // invalid input
            std::cout << "Invalid market option.\n";
        }
    }
}

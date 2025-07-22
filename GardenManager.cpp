#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "Garden.h"
#include "Carrot.h"
#include "Rose.h"
#include "Lunaria.h"
#include "Player.h"

using namespace std;

const int MAX_ENERGY = 3; // maximum energy player has each day

// main menu options
void displayMenu(const vector<string> &options)
{
  cout << "\nchoose an action:\n";
  for (size_t i = 0; i < options.size(); ++i)
  {
    cout << i + 1 << ". " << options[i] << "\n";
  }
}

// random pests event
bool pestEvent(Garden &garden)
{
  int chance = rand() % 100;
  if (chance < 50)
  {
    cout << "🐛 Oh no! pests appeared in your garden!\n";
    garden.pestsDamage(); // apply damage to plants from pests
    return true;
  }
  return false;
}

// random weeds event
bool weedEvent(Garden &garden)
{
  int chance = rand() % 100;
  if (chance < 60)
  {
    cout << "🌿 Weeds have grown around your plants!\n";
    garden.weedsGrow(); // apply weed growth
    return true;
  }
  return false;
}

// wrapper to perform action if energy is available
void performActionIfEnergy(int &energy, function<void()> action)
{
  if (energy <= 0)
  {
    cout << "⚠️ You have no energy left. End the day to restore energy.\n";
    return;
  }
  action();
  energy--;
}

// watering all plants, costs 1 energy
void handleWater(Garden &garden, int &energy)
{
  performActionIfEnergy(energy, [&]()
                        {
        garden.waterAllPlants(); // water every plant in the garden
        cout << "💧 You watered all plants.\n"; });
}

// handle harvesting seeds from mature plants, costs 1 energy
void handleHarvest(Garden &garden, Player &player, int &energy)
{
  performActionIfEnergy(energy, [&]()
    {
      garden.harvestMaturePlants(player); // harvest seeds and add to player's inventory
    });
}

// factory map for creating plants by seed name
Plant *createPlant(const string &seed)
{
  static unordered_map<string, function<Plant *()>> factory = {
      {"Carrot", []()
       { return new Carrot(); }},
      {"Rose", []()
       { return new Rose(); }},
      {"Lunaria", []()
       { return new Lunaria(); }},
  };
  auto it = factory.find(seed);
  if (it != factory.end())
    return it->second();
  return nullptr;
}

// handle planting a seed from the player's inventory, costs 1 energy
void handlePlant(Garden &garden, Player &player, int &energy)
{
  if (energy <= 0)
  {
    cout << "⚠️ You have no energy left. End the day to restore energy.\n";
    return;
  }

  // check if there's space for new plants in the garden
  if (!garden.hasSpace())
  {
    cout << "🚫 Your garden is full. Remove some plants before planting more.\n";
    return;
  }

  player.showInventory(); // show seeds available for planting

  // check if player has any seeds to plant
  if (player.isInventoryEmpty())
  {
    cout << "You have no seeds to plant.\n";
    return;
  }

  // ask player to choose which seed to plant
  cout << "Enter the seed number to plant: ";
  int seedNumber;
  cin >> seedNumber;

  // get the seed name
  string seed = player.getSeedByIndex(seedNumber);
  if (seed.empty() || !player.hasSeed(seed))
  {
    cout << "⚠️ Invalid seed selection.\n";
    return;
  }

  // create a new plant object based on seed
  Plant *newPlant = createPlant(seed);

  // if a new plant is created update garden and inventory
  if (newPlant)
  {
    newPlant->plant();
    garden.addPlant(newPlant);
    player.useSeed(seed); // remove one seed from inventory
    energy--;
    cout << "🌱 You planted a " << seed << "!\n";
  }
  else
  {
    cout << "⚠️ Failed to plant seed.\n";
  }
}

// remove dead plants from garden, costs 1 energy if any removed
void handleDeadPlants(Garden &garden, int &energy)
{
  if (energy <= 0)
  {
    cout << "⚠️ You have no energy left. End the day to restore energy.\n";
    return;
  }

  int removed = garden.removeDeadPlants();

  if (removed == 0)
    cout << "✅ No dead plants to remove.\n";
  else
  {
    cout << "🪦 Dead plants removed.\n";
    energy--;
  }
}

// treat pests in the garden, costs 1 energy
void handleTreatPests(Garden &garden, int &energy)
{
  performActionIfEnergy(energy, [&]()
                        {
        garden.treatAllPests(); // remove pests from plants
        cout << "🛡️ You treated the pests.\n"; });
}

// handle removing weeds from the garden, costs 1 energy
void handleRemoveWeeds(Garden &garden, int &energy)
{
  performActionIfEnergy(energy, [&]()
                        {
        garden.removeAllWeeds(); // remove weeds from plants
        cout << "🧹 You removed the weeds.\n"; });
}

// end of day: restore energy, grow plants, and trigger events
void handleEndDay(Garden &garden, Player &player, int &energy)
{
  energy = MAX_ENERGY; // reset energy
  cout << "🌙 A new day begins! Energy restored.\n";

  garden.growAllPlants(); // attempt to grow all plants
  cout << "🌱 All plants tried to grow.\n";

  // check for pest and weed damage warnings on each alive plant
  for (Plant *plant : garden.getPlants())
  {
    if (!plant->isAlive())
      continue;

    if (plant->checkPests())
    {
      plant->increasePestDamage(); // increase pest damage effects
      cout << "⚠️ " << plant->getType() << " has pests.\n";
      if (plant->isAlive())
        cout << "⚠️ " << plant->getType() << " is weakening from pests. treat it soon.\n";
    }

    if (plant->checkWeeds())
    {
      plant->increaseWeedDamage(); // increase weed damage effects
      if (plant->isAlive())
        cout << "⚠️ " << plant->getType() << " may die if weeds aren’t removed.\n";
    }
  }

  // random pest and weed events that can occur after growth
  if (pestEvent(garden))
    cout << "🐞 Treat pests or risk damage.\n";

  if (weedEvent(garden))
    cout << "🌾 Remove weeds or risk damage.\n";
}

int main()
{
  srand(time(nullptr)); // seed random number generator with current time

  Player player;   // create player object
  Garden myGarden; // create garden object

  // add initial plants to garden
  bool tutorial = true;
  if (tutorial)
  {
    Carrot *c = new Carrot();
    c->plant();
    myGarden.addPlant(c);

    Rose *r = new Rose();
    r->plant();
    myGarden.addPlant(r);
  }
  tutorial = false;

  int energy = MAX_ENERGY; // initialize player's energy for the day
  bool running = true;

  while (running)
  {
    cout << "\nenergy left today: " << energy << "\n";

    // build menu options dynamically
    struct MenuOption
    {
      string label;
      function<void()> action;
      bool enabled;
    };

    vector<MenuOption> menuOptions = {
        {"View your garden 🌿", [&]()
         { myGarden.display(); }, true},
        {"Water all plants 💧 (costs 1 energy)", [&]()
         { handleWater(myGarden, energy); }, energy > 0},
        {"Harvest seeds from mature plants 🌼 (costs 1 energy)", [&]()
         { handleHarvest(myGarden, player, energy); }, energy > 0},
        {"Plant a seed from inventory 🌱 (costs 1 energy)", [&]()
         { handlePlant(myGarden, player, energy); }, energy > 0},
        {"Remove dead plants 🪦 (costs 1 energy)", [&]()
         { handleDeadPlants(myGarden, energy); }, energy > 0},
        {"Treat pests 🐞 (costs 1 energy)", [&]()
         { handleTreatPests(myGarden, energy); }, myGarden.hasPests() && energy > 0},
        {"Remove weeds 🌾 (costs 1 energy)", [&]()
         { handleRemoveWeeds(myGarden, energy); }, myGarden.hasWeeds() && energy > 0},
        {"End day 🌙 (Restore energy & grow plants)", [&]()
         { handleEndDay(myGarden, player, energy); }, true},
        {"Exit 👋", [&]()
         { running = false; cout << "👋 Goodbye! Thanks for gardening.\n"; }, true}};

    // only enabled options for display
    vector<string> enabledLabels;
    vector<int> enabledIndices; // map user input to action index
    for (size_t i = 0; i < menuOptions.size(); ++i)
    {
      if (menuOptions[i].enabled)
      {
        enabledLabels.push_back(menuOptions[i].label);
        enabledIndices.push_back(i);
      }
    }

    displayMenu(enabledLabels);

    cout << "\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > (int)enabledLabels.size())
    {
      cout << "⚠️ Invalid option. Try again.\n";
      continue;
    }

    // execute the corresponding action
    menuOptions[enabledIndices[choice - 1]].action();
  }

  return 0;
}

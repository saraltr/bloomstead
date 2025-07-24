#include "Actions.h"
#include <cstdlib>

// performs action based on menu label
void PerformAction(const std::string &label, std::vector<std::vector<Plant>> &garden, PlayerState &player, bool &running)
{
    // water all alive and non empty plants
    if (label == "Water all plants" && player.energy > 0)
    {
        for (auto &row : garden)
            for (auto &plant : row)
                if (plant.stage != DEAD && plant.stage != EMPTY)
                    plant.watered = true;
        player.energy--;
    }
    // harvest seeds from mature plants and level up if needed
    else if (label == "Harvest seeds" && player.energy > 0)
    {
        int harvested = 0;
        for (auto &row : garden)
        {
            for (auto &plant : row)
            {
                if (plant.stage == MATURE)
                {
                    harvested++;
                    // reset to empty
                    plant = {};
                }
            }
        }
        player.energy--;
        player.seedsCollected += harvested;

        // check if player levels up
        if (player.seedsCollected >= 5 * player.level)
        {
            player.level++;
            player.maxEnergy++;
            player.energy = player.maxEnergy;
        }
    }
    // plant a seed in the first empty spot found
    else if (label == "Plant a seed" && player.energy > 0)
    {
        for (auto &row : garden)
        {
            for (auto &plant : row)
            {
                if (plant.stage == EMPTY)
                {
                    plant.stage = SEEDLING;
                    plant.watered = false;
                    plant.pests = false;
                    plant.weeds = false;
                    player.energy--;
                    return;
                }
            }
        }
    }
    // remove all dead plants
    else if (label == "Remove dead plants" && player.energy > 0)
    {
        for (auto &row : garden)
            for (auto &plant : row)
                if (plant.stage == DEAD)
                    plant = {};
        player.energy--;
    }
    // remove pests from all affected plants
    else if (label == "Treat pests" && player.energy > 0)
    {
        for (auto &row : garden)
            for (auto &plant : row)
                if (plant.pests)
                    plant.pests = false;
        player.energy--;
    }
    // remove weeds from all affected plants
    else if (label == "Remove weeds" && player.energy > 0)
    {
        for (auto &row : garden)
            for (auto &plant : row)
                if (plant.weeds)
                    plant.weeds = false;
        player.energy--;
    }
    // end the day by restoring energy, growing plants, and trigger the possibility of having pests/weeds
    else if (label == "End Day")
    {
        player.energy = player.maxEnergy;

        const int MAX_NEGLECT_DAYS = 3;
        const float PEST_PROBABILITY = 0.4f;
        const float WEED_PROBABILITY = 0.5f;

        // update plant state
        for (auto &row : garden)
        {
            for (auto &plant : row)
            {
                if (plant.stage == EMPTY || plant.stage == DEAD)
                    continue;

                bool neglected = (plant.pests || plant.weeds || !plant.watered);

                if (neglected)
                {
                    plant.daysNeglected++;
                    if (plant.daysNeglected >= MAX_NEGLECT_DAYS)
                    {
                        plant = {};
                        plant.stage = DEAD;
                        continue;
                    }
                }
                else
                {
                    plant.daysNeglected = 0;

                    // progress plant stage if healthy
                    switch (plant.stage)
                    {
                    case SEEDLING:
                        plant.stage = BLOOMING;
                        break;
                    case BLOOMING:
                        plant.stage = MATURE;
                        break;
                    default:
                        break;
                    }
                }

                // reset water status for next day
                plant.watered = false;
            }
        }

        // randomly add pests and weeds to some plants
        for (auto &row : garden)
        {
            for (auto &plant : row)
            {
                if (plant.stage != EMPTY && plant.stage != DEAD)
                {
                    if (!plant.pests && ((float)rand() / RAND_MAX) < PEST_PROBABILITY)
                        plant.pests = true;
                    if (!plant.weeds && ((float)rand() / RAND_MAX) < WEED_PROBABILITY)
                        plant.weeds = true;
                }
            }
        }
    }
    // exit the game
    else if (label == "Exit")
    {
        running = false;
    }
}

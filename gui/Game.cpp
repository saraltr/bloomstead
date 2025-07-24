#include "Game.h"
#include "raylib.h"

// create a garden grid and start empty
std::vector<std::vector<Plant>> CreateGarden(int rows, int cols)
{
    return std::vector<std::vector<Plant>>(rows, std::vector<Plant>(cols));
}

// create menu options, add tooltips, enabled state and style the buttons
std::vector<MenuOption> CreateMenuOptions(const PlayerState &player)
{
    return {
        {"Plant a seed", "plant a new seed in an empty spot.", player.energy > 0, {550, 135, 320, 48}},
        {"Water all plants", "water every plant to help them grow.", player.energy > 0, {550, 195, 320, 48}},
        {"Harvest seeds", "collect seeds from mature plants.", player.energy > 0, {550, 255, 320, 48}},
        {"Remove dead plants", "clear out dead plants to free space.", player.energy > 0, {550, 315, 320, 48}},
        {"Treat pests", "get rid of pesky pests harming plants.", player.energy > 0, {550, 375, 320, 48}},
        {"Remove weeds", "clear weeds choking your plants.", player.energy > 0, {550, 435, 320, 48}},
        {"End Day", "restore energy & grow plants.", true, {550, 495, 320, 48}},
        {"Exit", "exit the game.", true, {550, 555, 320, 48}},
    };
}

// update menu options enabled state based on player's current energy
void UpdateMenuOptions(std::vector<MenuOption> &menuOptions, const PlayerState &player)
{
    for (auto &option : menuOptions)
    {
        // always enable end day and exit options
        if (option.label == "End Day" || option.label == "Exit")
            option.enabled = true;
        else
            // enable others only if player has energy
            option.enabled = (player.energy > 0);
    }
}

// initialize the player state with default values
void InitPlayer(PlayerState &player)
{
    player.level = 1;
    player.seedsCollected = 0;
    player.maxEnergy = 3;
    player.energy = player.maxEnergy;
}

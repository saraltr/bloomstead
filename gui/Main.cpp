#include "raylib.h"
#include "Game.h"
#include "UI.h"
#include "Actions.h"
#include "Garden.h"
#include "Assets.h"
#include "State.h"

int main()
{
    // set up window size and frame rate
    const int screenWidth = 950;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "🌿 Garden Manager");
    SetTargetFPS(60);

    // load textures and fonts
    LoadGameTextures();

    // initialize player and game state
    PlayerState player;
    InitPlayer(player);

    auto garden = CreateGarden(5, 5);
    auto menuOptions = CreateMenuOptions(player);

    bool running = true;

    // main game loop
    while (!WindowShouldClose() && running)
    {
        // get mouse position
        Vector2 mousePos = GetMousePosition();

        // update enabled/disabled state of menu options
        UpdateMenuOptions(menuOptions, player);

        // begin drawing the different elements
        BeginDrawing();
        ClearBackground(WHITE);

        // draw game elements
        DrawGarden(garden, player);
        DrawLegend(20, 530);
        DrawEnergyBar(player.energy, player.maxEnergy, 550, 65, 320, 24);
        DrawTextEx(pixantiquaFont, "Choose an action:", {550, 95}, 20, 1, GREEN);

        std::string hoveredTooltip;

        // draw menu buttons and handle input
        for (auto &option : menuOptions)
        {
            bool hovered = CheckCollisionPointRec(mousePos, option.rect);
            DrawButton(option, hovered);

            if (hovered)
                hoveredTooltip = option.tooltip;

            if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && option.enabled)
            {
                PerformAction(option.label, garden, player, running);
            }
        }

        // draw tooltip if hovering over a button
        if (!hoveredTooltip.empty())
            DrawTooltip(hoveredTooltip, mousePos);

        EndDrawing();
    }

    // clean up resources
    UnloadGameTextures();
    CloseWindow();
    return 0;
}

#include "Garden.h"
#include "Assets.h"
#include <string>

// size of each garden cell in pixels
const int CELL_SIZE = 70;
// margin space between cells
const int CELL_MARGIN = 8;

void DrawGarden(const std::vector<std::vector<Plant>> &garden, const PlayerState &player)
{
    // welcome message
    // using raylib's free of use pixantiqua font
    DrawTextEx(pixantiquaFont, "Welcome to Bloomstead!", {20, 30}, 28, 1, PINK);

    // display the current garden level
    DrawTextEx(pixantiquaFont, TextFormat("You Garden is Level: %d", player.level), {20, 65}, 20, 1, GREEN);

    // show the total seeds harvested by the player so far
    DrawTextEx(pixantiquaFont, TextFormat("Seeds harvested: %d", player.seedsCollected), {20, 95}, 20, 1, BLUE);

    // loop through each row of the garden grid
    for (int row = 0; row < (int)garden.size(); ++row)
    {
        // loop through each plant in the current row
        for (int col = 0; col < (int)garden[row].size(); ++col)
        {
            const Plant &plant = garden[row][col];
            // calculate x,y position for this cell on screen based on row, col, size and margin
            int x = 20 + col * (CELL_SIZE + CELL_MARGIN);
            int y = 130 + row * (CELL_SIZE + CELL_MARGIN);

            // default cell background color is brown
            Color cellColor = BROWN;

            // change cell color based on plant's growth stage
            switch (plant.stage)
            {
            case EMPTY:
                cellColor = BROWN; // empty cells are brown soil
                break;
            case SEEDLING:
                cellColor = GREEN; // seedlings are bright green
                break;
            case BLOOMING:
                cellColor = ORANGE; // blooming plants are orange
                break;
            case MATURE:
                cellColor = YELLOW; // mature plants are yellow
                break;
            case DEAD:
                cellColor = BLACK; // dead plants are black
                break;
            }

            // if plant is watered and alive, show a blue overlay
            if (plant.stage != EMPTY && plant.stage != DEAD && plant.watered)
                cellColor = BLUE;

            // draw the cell rectangle with rounded corners and designed color
            DrawRectangleRounded({(float)x, (float)y, (float)CELL_SIZE, (float)CELL_SIZE}, 0.2f, 6, cellColor);

            // draw a gray border around each cell
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, GRAY);

            // scaling factor for icons inside the cell
            float iconScale = 0.4f;

            // draw pest icon if plant has pests and is alive
            if (plant.stage != EMPTY && plant.pests)
            {
                Vector2 pos = {
                    x + CELL_SIZE / 2.0f - (bugIcon.width * iconScale) / 2.0f,
                    y + 4.0f};
                DrawTextureEx(bugIcon, pos, 0.0f, iconScale, WHITE);
            }

            // draw weeds icon if plant has weeds and is alive
            if (plant.stage != EMPTY && plant.weeds)
            {
                Vector2 pos = {
                    x + CELL_SIZE / 2.0f - (weedsIcon.width * iconScale) / 2.0f,
                    y + CELL_SIZE - (weedsIcon.height * iconScale) - 4.0f};
                DrawTextureEx(weedsIcon, pos, 0.0f, iconScale, WHITE);
            }

            // calculate centered position for icons in the cell
            auto centerIconPosition = [&](Texture2D &icon) -> Vector2
            {
                float iconWidth = icon.width * iconScale;
                float iconHeight = icon.height * iconScale;
                return {
                    x + (CELL_SIZE - iconWidth) / 2.0f,
                    y + (CELL_SIZE - iconHeight) / 2.0f};
            };

            // draw plant stage icons only if plant is healthy without pests or weeds
            if (!plant.pests && !plant.weeds)
            {
                if (plant.stage == SEEDLING)
                {
                    Vector2 pos = centerIconPosition(seedIcon);
                    DrawTextureEx(seedIcon, pos, 0.0f, iconScale, WHITE);
                }
                else if (plant.stage == BLOOMING)
                {
                    Vector2 pos = centerIconPosition(bloomIcon);
                    DrawTextureEx(bloomIcon, pos, 0.0f, iconScale, WHITE);
                }
                else if (plant.stage == MATURE)
                {
                    Vector2 pos = centerIconPosition(matureIcon);
                    DrawTextureEx(matureIcon, pos, 0.0f, iconScale, WHITE);
                }
                else if (plant.stage == DEAD)
                {
                    Vector2 pos = centerIconPosition(deadIcon);
                    DrawTextureEx(deadIcon, pos, 0.0f, iconScale, WHITE);
                }
            }
        }
    }
}

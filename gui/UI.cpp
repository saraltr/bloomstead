#include "UI.h"
#include "Assets.h"
#include <algorithm>
#include <vector>

// function to draw a menu option button with a label and a hover effect
void DrawButton(const MenuOption &option, bool hovered)
{
    //  background color based on whether the option is enabled and hovered
    Color bgColor = option.enabled ? (hovered ? Fade(Color{180, 220, 240, 255}, 1.0f) : Color{230, 240, 250, 255}) : Fade(GRAY, 0.5f);
    // shadow color to create a bit of depth under the button
    Color shadowColor = Fade(BLACK, 0.25f);

    // draw a shadow slightly offset from button position
    DrawRectangleRounded({option.rect.x + 3, option.rect.y + 3, option.rect.width, option.rect.height}, 0.2f, 6, shadowColor);
    // draw main button rectangle with rounded corners
    DrawRectangleRounded(option.rect, 0.2f, 6, bgColor);
    // border lines
    DrawRectangleLines((int)option.rect.x, (int)option.rect.y, (int)option.rect.width, (int)option.rect.height, DARKGRAY);

    // choose text color based on enabled state
    Color textColor = option.enabled ? BLUE : DARKGRAY;
    int fontSize = 18;
    float spacing = 1.0f;

    // measure text size to center vertically within button
    Vector2 textSize = MeasureTextEx(pixantiquaFont, option.label.c_str(), fontSize, spacing);
    float padding = 15.0f;
    Vector2 textPos = {
        option.rect.x + padding,
        option.rect.y + (option.rect.height - textSize.y) / 2};

    // draw the button label text
    DrawTextEx(pixantiquaFont, option.label.c_str(), textPos, fontSize, spacing, textColor);

    // if button is not to end the day or exit the game draw energy icon to the right
    if (option.label != "End Day" && option.label != "Exit")
    {
        float iconScale = 0.4f;
        float iconWidth = energyIcon.width * iconScale;
        float iconHeight = energyIcon.height * iconScale;
        // position icon near right edge of button with padding
        float iconX = option.rect.x + option.rect.width - iconWidth - padding;
        float iconY = option.rect.y + (option.rect.height - iconHeight) / 2;

        DrawTextureEx(energyIcon, {iconX, iconY}, 0.0f, iconScale, WHITE);
    }
}

// function to draw a tooltip box near the mouse with the provided text
void DrawTooltip(const std::string &text, Vector2 mousePos)
{
    int padding = 8;
    int fontSize = 16;
    // measure text width for tooltip size
    int textWidth = MeasureText(text.c_str(), fontSize);
    int textHeight = fontSize + 4;

    // create rectangle for tooltip offset slightly from mouse cursor
    Rectangle tooltipRect = {mousePos.x + 15, mousePos.y + 15, (float)(textWidth + 2 * padding), (float)(textHeight + 2 * padding)};

    // adjust tooltip position if it would go off right edge of screen
    if (tooltipRect.x + tooltipRect.width > GetScreenWidth())
        tooltipRect.x = GetScreenWidth() - tooltipRect.width - 10;
    // adjust tooltip if it would go off bottom edge of screen
    if (tooltipRect.y + tooltipRect.height > GetScreenHeight())
        tooltipRect.y = GetScreenHeight() - tooltipRect.height - 10;

    // draw a semi transparent black background for tooltip
    DrawRectangleRounded(tooltipRect, 0.3f, 6, Fade(BLACK, 0.8f));
    // draw tooltip text inside the rectangle with padding
    DrawText(text.c_str(), (int)(tooltipRect.x + padding), (int)(tooltipRect.y + padding), fontSize, WHITE);
}

// function to draw the player's energy bar
void DrawEnergyBar(int energy, int maxEnergy, int x, int y, int width, int height)
{
    int fontSize = 20;
    float spacing = 1.0f;

    // draw the energy label above the bar
    Vector2 textPos = {(float)x, (float)(y - 28)};
    DrawTextEx(pixantiquaFont, "Energy", textPos, fontSize, spacing, BLUE);

    // measure the size of the label text to position the icon next to it
    Vector2 textSize = MeasureTextEx(pixantiquaFont, "Energy", fontSize, spacing);
    float iconScale = 0.4f;
    float iconWidth = energyIcon.width * iconScale;
    float iconHeight = energyIcon.height * iconScale;
    float iconX = x + textSize.x + 8;
    float iconY = y - 28 + (fontSize - iconHeight) / 2;
    // draw energy icon next to label
    DrawTextureEx(energyIcon, {iconX, iconY}, 0.0f, iconScale, WHITE);

    // draw the background of the energy bar as a light gray rectangle
    DrawRectangle(x, y, width, height, LIGHTGRAY);

    const float minUnitWidth = 12.0f;
    // calculate width per energy unit so it’s not too small
    float unitWidth = std::max(minUnitWidth, width / (float)maxEnergy);
    float totalUnitWidth = unitWidth * maxEnergy;

    // adjust unit width if total width exceeds bar width
    if (totalUnitWidth > width)
        unitWidth = width / (float)maxEnergy;

    float barX = x;

    // draw filled units representing current energy in sky blue color
    for (int i = 0; i < energy; i++)
    {
        float unitX = barX + i * unitWidth;
        float actualWidth = unitWidth;

        // if units are wide enough add padding for spacing between bars
        if (unitWidth > 14)
        {
            unitX += 2;
            actualWidth -= 4;
        }

        DrawRectangle(unitX, y + 2, actualWidth, height - 4, SKYBLUE);
    }

    // draw the border around the entire energy bar
    DrawRectangleLines(x, y, width, height, DARKBLUE);
}

// function to draw a legend explaining garden cell states
void DrawLegend(int x, int y)
{
    int boxSize = 20;   // size of the color box
    int spacing = 30;   // vertical spacing between legend items
    int fontSize = 16;

    // struct to hold color and label pairs for legend entries
    struct LegendItem
    {
        Color color;
        const char *label;
    };

    // list of legend items with associated colors and descriptions
    std::vector<LegendItem> legend = {
        {BROWN, "Empty soil"},
        {GREEN, "Seedling"},
        {ORANGE, "Blooming"},
        {BLUE, "Watered plant"},
        {YELLOW, "Mature plant"},
        {DARKGRAY, "Dead plant"},
    };

    // title text
    DrawText("Legend:", x, y, fontSize + 2, DARKBLUE);

    // draw each legend item with color box and label text
    for (size_t i = 0; i < legend.size(); ++i)
    {
        int itemY = y + 30 + i * spacing;
        DrawRectangle(x, itemY, boxSize, boxSize, legend[i].color);
        DrawRectangleLines(x, itemY, boxSize, boxSize, GRAY);
        DrawText(legend[i].label, x + boxSize + 10, itemY + 2, fontSize, DARKGRAY);
    }
}

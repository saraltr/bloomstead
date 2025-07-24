#pragma once
#include "raylib.h"
#include <string>
#include "State.h"

// draw menu buttons
void DrawButton(const MenuOption &option, bool hovered);

// draw tooltip near the mouse position
void DrawTooltip(const std::string &text, Vector2 mousePos);

// draw the player's energy bar
void DrawEnergyBar(int energy, int maxEnergy, int x, int y, int width, int height);

// draw the legend that explains the garden's cells logic
void DrawLegend(int x, int y);
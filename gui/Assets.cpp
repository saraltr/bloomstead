#include "Assets.h"

Texture2D bugIcon;
Texture2D weedsIcon;
Texture2D seedIcon;
Texture2D bloomIcon;
Texture2D matureIcon;
Texture2D deadIcon;
Texture2D energyIcon;

Font pixantiquaFont;

void LoadGameTextures()
{
    bugIcon = LoadTexture("assets/bug.png");
    weedsIcon = LoadTexture("assets/weeds.png");
    seedIcon = LoadTexture("assets/seedling.png");
    bloomIcon = LoadTexture("assets/blossom.png");
    deadIcon = LoadTexture("assets/skull.png");
    matureIcon = LoadTexture("assets/mature.png");
    energyIcon = LoadTexture("assets/zap.png");
    pixantiquaFont = LoadFont("assets/fonts/pixantiqua.fnt");
}

void UnloadGameTextures()
{
    UnloadTexture(bugIcon);
    UnloadTexture(weedsIcon);
    UnloadTexture(seedIcon);
    UnloadTexture(bloomIcon);
    UnloadTexture(deadIcon);
    UnloadTexture(matureIcon);
    UnloadFont(pixantiquaFont);
}

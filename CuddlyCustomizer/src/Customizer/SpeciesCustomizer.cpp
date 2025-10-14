#include "SpeciesCustomizer.h"
#include <algorithm>
#include "raylib.h"

SpeciesCustomizer::SpeciesCustomizer() {
    outfit.species = CAT;  
    outfit.hatIndex = -1;
    outfit.necklaceIndex = -1;
    outfit.color = 0; // used to track which sprite to show
}

SpeciesCustomizer::~SpeciesCustomizer() {
    UnloadAssets();
}

void SpeciesCustomizer::LoadAssets() {
    // Cats
    whiteCat = LoadTexture("assets/white_cat.png");
    orangeCat = LoadTexture("assets/orange_cat.png");
    pinkCat = LoadTexture("assets/Pink_cat.png");

    // Bunnies
    whiteBunny = LoadTexture("assets/bunny_white.png");
    blackBunny = LoadTexture("assets/black_bunny.png");
    pinkBunny = LoadTexture("assets/pink_bunny.png");

    // Accessories
    hatSprite = LoadTexture("assets/hats/tophat.png");
    necklaceSprite = LoadTexture("assets/necklace/bowtie.png");
}

void SpeciesCustomizer::UnloadAssets() {
    // Cats
    if (whiteCat.id > 0) UnloadTexture(whiteCat);
    if (orangeCat.id > 0) UnloadTexture(orangeCat);
    if (pinkCat.id > 0) UnloadTexture(pinkCat);

    // Bunnies
    if (whiteBunny.id > 0) UnloadTexture(whiteBunny);
    if (blackBunny.id > 0) UnloadTexture(blackBunny);
    if (pinkBunny.id > 0) UnloadTexture(pinkBunny);

    // Accessories
    if (hatSprite.id > 0) UnloadTexture(hatSprite);
    if (necklaceSprite.id > 0) UnloadTexture(necklaceSprite);
}

void SpeciesCustomizer::HandleInput() {
    // Switch species
    if (IsKeyPressed(KEY_C)) outfit.species = CAT;
    if (IsKeyPressed(KEY_B)) outfit.species = BUNNY;

    // Switch between sprites
    if (outfit.species == CAT) {
        if (IsKeyPressed(KEY_ONE)) outfit.color = 0; // white
        if (IsKeyPressed(KEY_TWO)) outfit.color = 1; // orange
        if (IsKeyPressed(KEY_THREE)) outfit.color = 2; // pink
    } else { // BUNNY
        if (IsKeyPressed(KEY_ONE)) outfit.color = 0; // white
        if (IsKeyPressed(KEY_TWO)) outfit.color = 1; // black
        if (IsKeyPressed(KEY_THREE)) outfit.color = 2; // pink
    }

    // Accessories
    if (IsKeyPressed(KEY_H)) outfit.hatIndex = (outfit.hatIndex == -1) ? 0 : -1;
    if (IsKeyPressed(KEY_N)) outfit.necklaceIndex = (outfit.necklaceIndex == -1) ? 0 : -1;
}

void SpeciesCustomizer::Draw(int screenWidth, int screenHeight, float maxScale) {
    Texture2D baseSprite;

    if (outfit.species == CAT) {
        switch (outfit.color) {
            case 0: baseSprite = whiteCat; break;
            case 1: baseSprite = orangeCat; break;
            case 2: baseSprite = pinkCat; break;
            default: baseSprite = whiteCat; break;
        }
    } else { // BUNNY
        switch (outfit.color) {
            case 0: baseSprite = whiteBunny; break;
            case 1: baseSprite = blackBunny; break;
            case 2: baseSprite = pinkBunny; break;
            default: baseSprite = whiteBunny; break;
        }
    }

    // Scaling
    float scaleX = (screenWidth * 0.5f) / baseSprite.width;
    float scaleY = (screenHeight * 0.7f) / baseSprite.height;
    float scale = std::min(scaleX, scaleY);
    scale = std::min(scale, maxScale);

    float posX = (screenWidth - baseSprite.width * scale) / 2.0f;
    float posY = (screenHeight - baseSprite.height * scale) / 2.0f + screenHeight * 0.1f;

    // Draw character
    DrawTextureEx(baseSprite, {posX, posY}, 0.f, scale, WHITE);

    // Draw hat
    if (outfit.hatIndex >= 0) {
        float hatScale = scale;
        float hatX = posX + (baseSprite.width * scale - hatSprite.width * hatScale) / 2.0f;
        float hatY = posY - hatSprite.height * hatScale * 0.7f;
        DrawTextureEx(hatSprite, {hatX, hatY}, 0.f, hatScale, WHITE);
    }

    // Draw necklace
    if (outfit.necklaceIndex >= 0) {
        float neckScale = scale;
        float neckX = posX + (baseSprite.width * scale - necklaceSprite.width * neckScale) / 2.0f;
        float neckY = posY + baseSprite.height * scale * 0.75f;
        DrawTextureEx(necklaceSprite, {neckX, neckY}, 0.f, neckScale, WHITE);
    }
}

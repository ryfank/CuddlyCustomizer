#include "SpeciesCustomizer.h"
#include <algorithm>
#include "raylib.h"
#include <iostream>

SpeciesCustomizer::SpeciesCustomizer() {
    outfit.species = CAT;  
    outfit.hatIndex = -1;  // Start with nothing equipped
    outfit.necklaceIndex = -1;  // Start with nothing equipped
    outfit.color = 0;
}

SpeciesCustomizer::~SpeciesCustomizer() {
    UnloadAssets();
}

void SpeciesCustomizer::LoadAssets() {
    std::cout << "Loading game assets..." << std::endl;
    
    // Cats
    whiteCat = LoadTexture("assets/white_cat.png");
    orangeCat = LoadTexture("assets/orange_cat.png");
    pinkCat = LoadTexture("assets/pink_cat.png");

    // Bunnies
    whiteBunny = LoadTexture("assets/bunny_white.png");
    blackBunny = LoadTexture("assets/black_bunny.png");
    pinkBunny = LoadTexture("assets/pink_bunny.png");

    // Accessories
    hatSprite = LoadTexture("assets/hats/tophat.png");
    necklaceSprite = LoadTexture("assets/necklace/bowtie.png");
    
    // Debug info
    std::cout << "Hat loaded: " << (hatSprite.id > 0) << " (" << hatSprite.width << "x" << hatSprite.height << ")" << std::endl;
    std::cout << "Bowtie loaded: " << (necklaceSprite.id > 0) << " (" << necklaceSprite.width << "x" << necklaceSprite.height << ")" << std::endl;
}

void SpeciesCustomizer::UnloadAssets() {
    // Cats
    UnloadTexture(whiteCat);
    UnloadTexture(orangeCat);
    UnloadTexture(pinkCat);

    // Bunnies
    UnloadTexture(whiteBunny);
    UnloadTexture(blackBunny);
    UnloadTexture(pinkBunny);

    // Accessories
    UnloadTexture(hatSprite);
    UnloadTexture(necklaceSprite);
}

void SpeciesCustomizer::HandleInput() {
    // Species switching
    if (IsKeyPressed(KEY_P)) {
        outfit.species = (outfit.species == CAT) ? BUNNY : CAT;
        std::cout << "Species switched to: " << (outfit.species == CAT ? "Cat" : "Bunny") << std::endl;
    }

    // Color switching
    if (IsKeyPressed(KEY_ONE)) { outfit.color = 0; std::cout << "Color: White" << std::endl; }
    if (IsKeyPressed(KEY_TWO)) { outfit.color = 1; std::cout << "Color: Orange/Black" << std::endl; }
    if (IsKeyPressed(KEY_THREE)) { outfit.color = 2; std::cout << "Color: Pink" << std::endl; }

    // Accessories
    if (IsKeyPressed(KEY_H)) {
        outfit.hatIndex = (outfit.hatIndex == -1) ? 0 : -1;
        std::cout << "Hat: " << (outfit.hatIndex >= 0 ? "ON" : "OFF") << std::endl;
    }
    if (IsKeyPressed(KEY_N)) {
        outfit.necklaceIndex = (outfit.necklaceIndex == -1) ? 0 : -1;
        std::cout << "Necklace: " << (outfit.necklaceIndex >= 0 ? "ON" : "OFF") << std::endl;
    }
}

void SpeciesCustomizer::Draw(int screenWidth, int screenHeight, float maxScale) {
    Texture2D baseSprite;

    // Select base sprite based on species and color
    if (outfit.species == CAT) {
        switch (outfit.color) {
            case 0: baseSprite = whiteCat; break;
            case 1: baseSprite = orangeCat; break;
            case 2: baseSprite = pinkCat; break;
            default: baseSprite = whiteCat; break;
        }
    } else {
        switch (outfit.color) {
            case 0: baseSprite = whiteBunny; break;
            case 1: baseSprite = blackBunny; break;
            case 2: baseSprite = pinkBunny; break;
            default: baseSprite = whiteBunny; break;
        }
    }

    // Smart scaling to fit screen
    float scaleX = (screenWidth * 0.4f) / baseSprite.width;
    float scaleY = (screenHeight * 0.6f) / baseSprite.height;
    float scale = std::min(std::min(scaleX, scaleY), maxScale);

    float posX = (screenWidth - baseSprite.width * scale) / 2.0f;
    float posY = (screenHeight - baseSprite.height * scale) / 2.0f + 50;

    // Draw the base character
    DrawTextureEx(baseSprite, {posX, posY}, 0.0f, scale, WHITE);

    // Draw hat
    if (outfit.hatIndex >= 0 && hatSprite.id > 0) {
        float hatScale = scale * 0.8f;
        float hatX = posX + (baseSprite.width * scale - hatSprite.width * hatScale) / 2.0f;
        float hatY = posY + (baseSprite.height * scale * 0.05f);
        DrawTextureEx(hatSprite, {hatX, hatY}, 0.0f, hatScale, WHITE);
    }

    // draw bowtie
    if (outfit.necklaceIndex >= 0 && necklaceSprite.id > 0) {
        float neckScale = scale * 0.8f;
        float neckX = posX + (baseSprite.width * scale - necklaceSprite.width * neckScale) / 2.0f;
        float neckY = posY + (baseSprite.height * scale * 0.10f);
        
        DrawTextureEx(necklaceSprite, {neckX, neckY}, 0.0f, neckScale, WHITE);
    
      
    }
}
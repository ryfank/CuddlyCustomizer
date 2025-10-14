#ifndef SPECIESCUSTOMIZER_H
#define SPECIESCUSTOMIZER_H

#include "raylib.h"
#include "../Outfit.h"

class SpeciesCustomizer {
public:
    SpeciesCustomizer();
    ~SpeciesCustomizer();

    Outfit outfit;

    void LoadAssets();
    void HandleInput();
    void Draw(int screenWidth, int screenHeight, float maxScale);
    void UnloadAssets();

private:
    // Cat sprites
    Texture2D whiteCat;
    Texture2D orangeCat;
    Texture2D pinkCat;

    // Bunny sprites
    Texture2D whiteBunny;
    Texture2D blackBunny;
    Texture2D pinkBunny;

    // Accessories
    Texture2D hatSprite;
    Texture2D necklaceSprite;

    // Internal: track which sprite to show
    int spriteIndex;
};

#endif

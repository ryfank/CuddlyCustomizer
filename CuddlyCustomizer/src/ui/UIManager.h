#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "raylib.h"
#include "../Outfit.h"  // Ensure this path is correct relative to UIManager.cpp

// Scoped enum for animal colors, preventing macro pollution
enum class AnimalColor {
    White,
    Orange,
    Pink,
    Black,

    // Add more colors here as needed
};

namespace UIManager {
    void DrawUI(const Outfit& outfit);
}
#endif // UIMANAGER_H

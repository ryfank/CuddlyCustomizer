#include "UIManager.h"
#include "raylib.h"
#include "../Outfit.h"

namespace UIManager {

void DrawUI(const Outfit& outfit) {
    // Instructions
    DrawText("H: Toggle Hat", 20, 20, 20, DARKGRAY);
    DrawText("N: Toggle Necklace", 20, 50, 20, DARKGRAY);
    DrawText("S: Save Outfit", 20, 80, 20, DARKGRAY);
    DrawText("P: Switch Species", 20, 110, 20, DARKGRAY);

    // Outfit status
    DrawText(outfit.HasHat() ? "Hat: ON" : "Hat: OFF", 20, 150, 20, MAROON);
    DrawText(outfit.HasNecklace() ? "Necklace: ON" : "Necklace: OFF", 20, 180, 20, MAROON);

    // Species
    const char* speciesStr = (outfit.species == CAT) ? "Cat" : "Bunny";
    DrawText(TextFormat("Species: %s", speciesStr), 20, 210, 20, DARKGRAY);
}

}  // namespace UIManager

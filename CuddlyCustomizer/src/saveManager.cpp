#include "saveManager.h"
#include <fstream>
#include <string>
#include "Outfit.h"

// We'll save hatIndex, necklaceIndex, species as 3 signed bytes for simplicity
// XOR encryption done on each byte with key bytes cycling if needed

Outfit loadOutfit(const std::string& key) {
    Outfit outfit;

    std::ifstream file("outfit.dat", std::ios::binary);
    if (file.is_open()) {
        char encrypted[3];
        file.read(encrypted, 3);
        if (file.gcount() == 3) {
            // XOR decrypt with key bytes, cycle key if shorter than 3
            for (int i = 0; i < 3; ++i) {
                encrypted[i] ^= key[i % key.size()];
            }
            // Assign values, convert signed char to int safely
            outfit.hatIndex = static_cast<int>(encrypted[0]);
            outfit.necklaceIndex = static_cast<int>(encrypted[1]);
            outfit.species = static_cast<Species>(encrypted[2]);
        }
        file.close();
    }
    else {
        // Default outfit
        outfit.hatIndex = -1;
        outfit.necklaceIndex = -1;
        outfit.species = CAT;
    }

    return outfit;
}

void saveOutfit(const Outfit& outfit, const std::string& key) {
    std::ofstream file("outfit.dat", std::ios::binary);
    if (file.is_open()) {
        char encrypted[3];
        encrypted[0] = static_cast<char>(outfit.hatIndex);
        encrypted[1] = static_cast<char>(outfit.necklaceIndex);
        encrypted[2] = static_cast<char>(outfit.species);

        // XOR encrypt each byte with key bytes, cycling key if needed
        for (int i = 0; i < 3; ++i) {
            encrypted[i] ^= key[i % key.size()];
        }

        file.write(encrypted, 3);
        file.close();
    }
}

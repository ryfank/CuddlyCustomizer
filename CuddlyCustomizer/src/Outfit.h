#ifndef OUTFIT_H
#define OUTFIT_H

enum Species { CAT, BUNNY };

struct Outfit {
    Species species;        // Current species
    int hatIndex = -1;      // -1 = no hat, 0 = hat active
    int necklaceIndex = -1; // -1 = no necklace, 0 = necklace active
    int color; 
    
    // Convenience getters
    bool HasHat() const { return hatIndex != -1; }
    bool HasNecklace() const { return necklaceIndex != -1; }
};

#endif

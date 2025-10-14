#ifndef FIREFLIES_H
#define FIREFLIES_H


#include "raylib.h"
#include <vector>

struct Firefly {
    Vector2 pos;
    float speed;
    float radius;
    float alpha;
    Color color;
};

namespace Fireflies {
    void Init(int screenWidth, int screenHeight, int maxFireflies);
    void Update(int screenWidth, int screenHeight);
    void Draw();
}

#endif //FIREFLIES_H
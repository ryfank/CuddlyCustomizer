#include "Fireflies.h"
#include <vector>
#include <cmath>
#include <cstdlib>

static std::vector<Firefly> fireflies;

void Fireflies::Init(int screenWidth, int screenHeight, int maxFireflies) {
    fireflies.clear();
    for (int i = 0; i < maxFireflies; i++) {
        Firefly f;
        f.pos = { 
            static_cast<float>(GetRandomValue(0, screenWidth)), 
            static_cast<float>(GetRandomValue(0, screenHeight)) 
        };
        f.speed = static_cast<float>(GetRandomValue(5, 20)) / 100.0f;
        f.radius = static_cast<float>(GetRandomValue(4, 8));
        f.alpha = static_cast<float>(GetRandomValue(70, 150)) / 255.0f;

        int tone = GetRandomValue(220, 255);
        if (GetRandomValue(0, 1) == 0) {
            f.color = Color{
                static_cast<unsigned char>(tone),
                static_cast<unsigned char>(tone),
                static_cast<unsigned char>(tone),
                static_cast<unsigned char>(200)
            };
        } else {
            f.color = Color{
                255,
                static_cast<unsigned char>(GetRandomValue(180, 220)),
                240,
                static_cast<unsigned char>(200)
            };
        }

        fireflies.push_back(f);
    }
}

void Fireflies::Update(int screenWidth, int screenHeight) {
    for (auto& f : fireflies) {
        f.pos.y -= f.speed;
        f.pos.x += sinf(f.pos.y * 0.01f) * 0.2f;

        if (f.pos.y < -10) {
            f.pos.y = screenHeight + 10;
            f.pos.x = static_cast<float>(GetRandomValue(0, screenWidth));
        }
    }
}

void Fireflies::Draw() {
    for (const auto& f : fireflies) {
        DrawCircleV(f.pos, f.radius, Fade(f.color, f.alpha));
    }
}

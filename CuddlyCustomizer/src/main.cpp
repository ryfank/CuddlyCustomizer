#include <string>
#include "raylib.h"
#include "ui/UIManager.h"
#include "Fireflies.h"
#include "Outfit.h"
#include "saveManager.h"
#include "login/loginScreen.h"
#include "login/loginManager.h"
#include "Customizer/SpeciesCustomizer.h"

using std::string;

int main() {
    const int screenWidth = 1400;
    const int screenHeight = 800;

    // Window & audio
    InitWindow(screenWidth, screenHeight, "Cuddly Customizer");
    InitAudioDevice();
    SetTargetFPS(60);

    // Load assets
    Texture2D background = LoadTexture("assets/background.jpeg");
    Texture2D logo = LoadTexture("assets/Logo.png");
    Music music = LoadMusicStream("assets/lofi.mp3");
    PlayMusicStream(music);
    Sound buttonSound = LoadSound("assets/button.mp3");

    // Login system
    LoginManager loginManager;
    string encryptionKey;
    bool loggedIn = false;

    // ---------- Login Screen ----------
    while (!WindowShouldClose() && !loggedIn) {
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(logo, (screenWidth - logo.width) / 2, 20, WHITE);

        loggedIn = ShowLoginScreen(encryptionKey, loginManager, background, music, buttonSound);
        EndDrawing();
    }

    if (!loggedIn) {
        // Cleanup if window closed or login failed
        UnloadMusicStream(music);
        UnloadSound(buttonSound);
        UnloadTexture(background);
        UnloadTexture(logo);
        CloseAudioDevice();
        CloseWindow();
        return 0;
    }

    // ---------- Load saved outfit ----------
    Outfit outfit = loadOutfit(encryptionKey);

    // Fireflies
    Fireflies::Init(screenWidth, screenHeight, 80);

    // Species customizer
    SpeciesCustomizer customizer;
    customizer.LoadAssets();
    customizer.outfit = outfit;

    float characterMaxScale = 3.0f;

    // ---------- Main Customizer Loop ----------
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        // Handle input from UI or keys
        customizer.HandleInput();

        // Save outfit
        if (IsKeyPressed(KEY_S)) {
            outfit = customizer.outfit;
            saveOutfit(outfit, encryptionKey);
            PlaySound(buttonSound);
        }

        Fireflies::Update(screenWidth, screenHeight);

        // ---------- Draw ----------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);
        Fireflies::Draw();
        UIManager::DrawUI(customizer.outfit);
        customizer.Draw(screenWidth, screenHeight, characterMaxScale);

        EndDrawing();
    }

    // Cleanup
    customizer.UnloadAssets();
    UnloadMusicStream(music);
    UnloadSound(buttonSound);
    UnloadTexture(background);
    UnloadTexture(logo);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

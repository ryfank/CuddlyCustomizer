#include <string>
#include "raylib.h"
#include "ui/UIManager.h"
#include "Fireflies.h"
#include "Outfit.h"
#include "saveManager.h"
#include "login/loginScreen.h"
#include "login/loginManager.h"
#include "Customizer/SpeciesCustomizer.h"
#include <iostream>

using std::string;

int main() {
    const int screenWidth = 1400;
    const int screenHeight = 800;

    std::cout << "Starting Cuddly Customizer..." << std::endl;

    // Window & audio
    InitWindow(screenWidth, screenHeight, "Cuddly Customizer");
    InitAudioDevice();
    SetTargetFPS(60);

    std::cout << "Window initialized" << std::endl;

    // Load assets
    Texture2D background = LoadTexture("assets/background.jpeg");
    Texture2D logo = LoadTexture("assets/Logo.png");
    Music music = LoadMusicStream("assets/lofi.mp3");
    PlayMusicStream(music);
    Sound buttonSound = LoadSound("assets/button.mp3");

    std::cout << "Assets loaded:" << std::endl;
    std::cout << "Background ID: " << background.id << std::endl;
    std::cout << "Logo ID: " << logo.id << std::endl;

    // Login system
    LoginManager loginManager;
    string encryptionKey;
    bool loggedIn = false;

    std::cout << "Entering login screen..." << std::endl;

    // ---------- Login Screen ----------
    while (!WindowShouldClose() && !loggedIn) {
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(logo, (screenWidth - logo.width) / 2, 20, WHITE);

        loggedIn = ShowLoginScreen(encryptionKey, loginManager, background, music, buttonSound);
        
        // Debug: show if we're stuck in login
        DrawText("Login Screen - Debug", 10, 10, 20, RED);
        
        EndDrawing();
    }

    if (!loggedIn) {
        std::cout << "Login failed or window closed" << std::endl;
        UnloadMusicStream(music);
        UnloadSound(buttonSound);
        UnloadTexture(background);
        UnloadTexture(logo);
        CloseAudioDevice();
        CloseWindow();
        return 0;
    }

    std::cout << "Login successful! Loading main game..." << std::endl;

    // ---------- Load saved outfit ----------
    Outfit outfit = loadOutfit(encryptionKey);

    // Fireflies
    Fireflies::Init(screenWidth, screenHeight, 80);

    // Species customizer
    SpeciesCustomizer customizer;
    customizer.LoadAssets();
    customizer.outfit = outfit;

    float characterMaxScale = 3.0f;

    std::cout << "Entering main game loop..." << std::endl;

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

        // Debug text to see if we're in main game
        DrawText("Main Game - Debug", 10, 10, 20, GREEN);
        
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

    std::cout << "Game closed normally" << std::endl;
    return 0;
}
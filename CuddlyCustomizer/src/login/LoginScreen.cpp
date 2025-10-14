#include "loginScreen.h"
#include "raylib.h"
#include "loginManager.h"
#include "../Fireflies.h"
#include <string>

bool ShowLoginScreen(std::string& encryptionKey, LoginManager& loginManager, Texture2D& background, Music& music, Sound& buttonSound) {
    std::string username;
    std::string password;
    bool typingUsername = true;

    // Shifted rectangles - only defined once here!
    Rectangle usernameBox = { 500, 340, 400, 50 };
    Rectangle passwordBox = { 500, 440, 400, 50 };
    Rectangle loginButton = { 580, 540, 240, 50 };

    Texture2D logo = LoadTexture("../assets/logo.png"); // Adjust path if needed
    Fireflies::Init(GetScreenWidth(), GetScreenHeight(), 80);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        Fireflies::Update(GetScreenWidth(), GetScreenHeight());

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, usernameBox)) {
                typingUsername = true;
                PlaySound(buttonSound);
            } else if (CheckCollisionPointRec(mouse, passwordBox)) {
                typingUsername = false;
                PlaySound(buttonSound);
            } else if (CheckCollisionPointRec(mouse, loginButton)) {
                PlaySound(buttonSound);
                if (loginManager.verifyCredentials(username, password)) {
                    encryptionKey = password;
                    UnloadTexture(logo);
                    return true;
                }
            }
        }

        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125) {
                if (typingUsername) username += (char)key;
                else password += (char)key;
                PlaySound(buttonSound);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (typingUsername && !username.empty()) {
                username.pop_back();
                PlaySound(buttonSound);
            } else if (!typingUsername && !password.empty()) {
                password.pop_back();
                PlaySound(buttonSound);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        Fireflies::Draw();

        // Logo position (slightly moved down)
        float tabHeight = 80.0f;
        float padding = 10.0f;
        float verticalOffset = -10.0f;

        float scale = 0.4f;
        float logoWidth = logo.width * scale;
        float logoX = 1400.0f / 2.0f - logoWidth / 2.0f;
        float logoY = tabHeight + padding + verticalOffset;

        DrawTextureEx(logo, (Vector2){ logoX, logoY }, 0.0f, scale, WHITE);

        // Draw rectangles and text
        DrawRectangleRec(usernameBox, (Color){180, 150, 220, 180});
        DrawRectangleRec(passwordBox, (Color){180, 150, 220, 180});
        DrawRectangleRec(loginButton, (Color){180, 150, 220, 180});

        DrawText("Username:", 500, 310, 20, PINK);
        DrawText(username.c_str(), 510, 355, 20, BLACK);

        std::string maskedPass(password.length(), '*');
        DrawText("Password:", 500, 410, 20, PINK);
        DrawText(maskedPass.c_str(), 510, 455, 20, BLACK);

        DrawText("Login", (int)(loginButton.x) + 80, (int)(loginButton.y) + 15, 20, BLACK);

        EndDrawing();
    }

    UnloadTexture(logo);
    return false;
}

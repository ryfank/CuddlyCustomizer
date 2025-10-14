#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <string>
#include "loginManager.h"
#include "raylib.h"  // for Texture2D, Music, Sound

bool ShowLoginScreen(std::string& encryptionKey, LoginManager& loginManager, Texture2D& background, Music& music, Sound& buttonSound);

#endif

extern "C" {
#include "raylib.h"
}

#include <iostream>
#include <filesystem>

int main() {
    std::cout << "starting window\n";

    InitWindow(800, 600, "math game");

    SetTargetFPS(1000);

    auto currentDir = std::filesystem::current_path();
    std::filesystem::current_path("../../../assets");

    // Inserting textures, fonts
    Texture2D bg1 = LoadTexture("bg1.png");
    Texture2D credits = LoadTexture("creditsbutton.png");
    Texture2D settings = LoadTexture("settingsbutton.png");
    Font font1 = LoadFont("fonts/JetBrainsMono-ExtraBold.ttf");
    Font font2 = LoadFont("fonts/JetBrainsMono-MediumItalic.ttf");

    int xcre = 0;
    int xset = 0;

    // For bounce effect
    int beyondlimitcre = 0;
    bool justtouchcreditsbutton = false;
    int beyondlimitset = 0;
    bool justtouchsettingsbutton = false;

    std::filesystem::current_path(currentDir);

    while (!WindowShouldClose()) {
        // Make the title move while moving the mouse
        Vector2 mousePos = GetMousePosition();
        float mouseX = mousePos.x;
        float mouseY = mousePos.y;

        Vector2 titlepos = {220 + (mouseX / 25), 200 + (mouseY / 25)};
        Vector2 menubgpos = {-55 + (mouseX / 50), -50 + (mouseY / 50)};
        Vector2 creditspos = {-95, 53};
        Vector2 creditstextpos = {-105, 62};
        Vector2 settingspos = {-95, 100};
        Vector2 settingstextpos = {-108, 112};

        // Rectangle representing the button's bounds
        Rectangle textureBoundscredits = {creditspos.x, creditspos.y, (float)credits.width, (float)credits.height};
        Rectangle textureBoundssettings = {settingspos.x, settingspos.y, (float)settings.width, (float)settings.height};

        // Define boolean checks if mouse was hovered on sth
        bool mouseOvercredits = CheckCollisionPointRec(mousePos, textureBoundscredits);
        bool mouseOversettings = CheckCollisionPointRec(mousePos, textureBoundssettings);

        // Check credits button touch and animation
        if (mouseOvercredits) {
            justtouchcreditsbutton = true;
            if (beyondlimitcre == 0) {
                xcre += 1;
                creditspos.x += xcre;
                creditstextpos.x += xcre;
                if (creditspos.x > 0) beyondlimitcre = 1;
            } else {
                creditspos.x = 0;
                creditstextpos.x = 3;
            }
            if (!mouseOvercredits) {
                xcre -= 1;
                creditspos.x += xcre;
                creditstextpos.x += xcre;
                if (creditspos.x <= -95) beyondlimitcre = 1;
            }
        } else {
            beyondlimitcre = 0;
            if (justtouchcreditsbutton) {
                xcre -= 1;
                creditspos.x += xcre;
                creditstextpos.x += xcre;
                if (creditspos.x <= -95) justtouchcreditsbutton = false;
            } else {
                creditspos.x = -95;
                creditstextpos.x = -105;
            }
        }
        
        // Check options button touch and animation
        if (mouseOversettings) {
            justtouchsettingsbutton = true;
            if (beyondlimitset == 0) {
                xset += 1;
                settingspos.x += xset;
                settingstextpos.x += xset;
                if (settingspos.x > 0) beyondlimitset = 1;
            } else {
                settingspos.x = 0;
                settingstextpos.x = 3;
            }
            if (!mouseOversettings) {
                xset -= 1;
                settingspos.x += xset;
                settingstextpos.x += xset;
                if (settingspos.x <= -95) beyondlimitset = 1;
            }
        } else {
            beyondlimitset = 0;
            if (justtouchsettingsbutton) {
                xset -= 1;
                settingspos.x += xset;
                settingstextpos.x += xset;
                if (settingspos.x <= -95) justtouchsettingsbutton = false;
            } else {
                settingspos.x = -95;
                settingstextpos.x = -108;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(bg1, menubgpos, 0, 1.1, WHITE);
        DrawTextureEx(credits, creditspos, 0, 1, WHITE);
        DrawTextureEx(settings, settingspos, 0, 1, WHITE);
        DrawTextEx(font1, "Math random", titlepos, 70, 2, RED);
        DrawTextEx(font2, "Credits", creditstextpos, 30, 2, WHITE);
        DrawTextEx(font2, "Settings", settingstextpos, 27, 2, WHITE);
        EndDrawing();
    }

    UnloadTexture(bg1);
    UnloadFont(font1);

    CloseWindow();

    return 0;
}

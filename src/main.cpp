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

    Texture2D bg1 = LoadTexture("bg1.png");
    Font font1 = LoadFont("fonts/JetBrainsMono-ExtraBold.ttf");

    std::filesystem::current_path(currentDir);

    while (!WindowShouldClose()) {
        // Make the title move while moving the mouse
        Vector2 mousePos = GetMousePosition();
        float mouseX = mousePos.x;
        float mouseY = mousePos.y;

        Vector2 titlepos = {220 + (mouseX / 25), 200 + (mouseY / 25)};
        Vector2 menubgpos = {-55 + (mouseX / 50), -50 + (mouseY / 50)};

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(bg1, menubgpos, 0, 1.1, WHITE);
        DrawTextEx(font1, "Math random", titlepos, 70, 2, RED);
        EndDrawing();
    }

    UnloadTexture(bg1);
    UnloadFont(font1);

    CloseWindow();

    return 0;
}

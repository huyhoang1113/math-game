extern "C" {
#include "raylib.h"
}

#include <iostream>

int main() {
    std::cout << "starting window\n";

    InitWindow(800, 600, "math game");

    SetTargetFPS(1000);

    Texture2D background = LoadTexture("assets/bg1.png");

    while (!WindowShouldClose()) {
        // Make the title move while moving the mouse
        Vector2 mousePos = GetMousePosition();
        float mouseX = mousePos.x;
        float mouseY = mousePos.y;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawText("Math random", 230 + (mouseX / 20), 200 + (mouseY / 20), 50, RED);
        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow();

    return 0;
}

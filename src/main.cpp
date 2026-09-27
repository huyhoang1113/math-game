extern "C" {
#include "raylib.h"
}

#include <iostream>

int main() {
    std::cout << "starting window\n";

    InitWindow(800, 600, "math game");

    SetTargetFPS(1000);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("math game", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

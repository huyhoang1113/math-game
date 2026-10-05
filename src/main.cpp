extern "C" {
#include "raylib.h"
}

#include <iostream>
#include <filesystem>
#include<string>
#include <sstream>
#include<random>
#include<array>
#include<vector>

std::vector<std::vector<std::string>> objectspawn;
std::vector<std::vector<int>> posobject;

void Spawn() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> posx(0, 800);
    std::uniform_int_distribution<int> posy(0, 600);
    posobject.push_back({posx(gen), posy(gen)});
    std::uniform_int_distribution<int> expression(1, 5);
    std::uniform_int_distribution<int> random(0, 1);
    int randgen = random(gen);
    int exp = expression(gen);
    std::string obj;
    std::uniform_int_distribution<int> numgen(exp > 2 ? -9 : 1, 9);
    if (exp == 1) obj = "+";
    if (exp == 2) obj = "-";
    if (exp == 3) obj = "*";
    if (exp == 4) obj = "/";
    if (exp == 5) obj = "^";
    objectspawn.push_back({obj, std::to_string(numgen(gen))});
}

int main() {
    std::cout << "starting window\n";

    InitWindow(800, 600, "Math random");

    SetTargetFPS(1000);

    auto currentDir = std::filesystem::current_path();
    std::filesystem::current_path("../../../assets");

    // Inserting textures, fonts
    Texture2D bg1 = LoadTexture("bg1.png");
    Texture2D credits = LoadTexture("creditsbutton.png");
    Texture2D settings = LoadTexture("settingsbutton.png");
    Texture2D playbutton = LoadTexture("play.png");
    Font font1 = LoadFont("fonts/JetBrainsMono-ExtraBold.ttf");
    Font font2 = LoadFont("fonts/JetBrainsMono-MediumItalic.ttf");
    Font font3 = LoadFont("fonts/JetBrainsMono-Bold.ttf");

    int xcre = 0;
    int xset = 0;

    // The core thing
    long double result = 0;

    // Check if play
    bool startgame = false;

    // For button animation
    int beyondlimitcre = 0;
    bool justtouchcreditsbutton = false;
    int beyondlimitset = 0;
    bool justtouchsettingsbutton = false;
    std::filesystem::current_path(currentDir);

    // Menu clones
    const int clones = 30;
    Vector2 posistionsmenu[clones];
    Vector2 visualposistionsmenu[clones];
    float directionmenu[clones];
    float visualdirectionmenu[clones];
    Vector2 textSizemenu[clones];
    float textsizes[clones];
    float speeds[clones];
    std::string clonetext[clones];
    std::string expressions[clones];
    float randomturn[clones];
    for (int i = 0; i < clones; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> posx(0, 800);
        std::uniform_int_distribution<int> posy(0, 600);
        std::uniform_int_distribution<int> direction(0, 360);
        std::uniform_int_distribution<int> textSize(30, 75);
        std::uniform_int_distribution<int> speed(2, 3);
        std::uniform_int_distribution<int> expression(1, 5);
        std::uniform_int_distribution<int> random(0, 1);
        int randgen = random(gen);
        int exp = expression(gen);
        int number;
        std::uniform_int_distribution<int> numgen(exp > 2 ? -9:1, 9);
        number = numgen(gen);
        if (exp == 1) expressions[i] = "+";
        if (exp == 2) expressions[i] = "-";
        if (exp == 3) expressions[i] = "*";
        if (exp == 4) expressions[i] = "/";
        if (exp == 5) expressions[i] = "^";
        float x = posx(gen);
        float y = posy(gen);
        float dir = direction(gen);
        float clonespeed = speed(gen);
        textsizes[i] = textSize(gen);
        posistionsmenu[i] = {x, y};
        directionmenu[i] = dir;
        visualdirectionmenu[i] = dir;
        if (number < 0) clonetext[i] = expressions[i] + "(" + std::to_string(number) + ")";
        else clonetext[i] = expressions[i] + std::to_string(number);
        textSizemenu[i] = MeasureTextEx(font3, clonetext[i].c_str(), textsizes[i], 2);
        speeds[i] = clonespeed;
        if (randgen == 0) randomturn[i]=0.05;
        else randomturn[i] = -0.05;
    }

    // Spawn random
    float timer = 0;
    float spawnTime = 0.5;

    while (!WindowShouldClose()) {
        // Make the title move while moving the mouse
        Vector2 mousePos = GetMousePosition();
        float mouseX = mousePos.x;
        float mouseY = mousePos.y;

        Vector2 titlepos = {180 + (mouseX / 20), 160 + (mouseY / 20)};
        Vector2 playpos = {325 + (mouseX / 20), 290 + (mouseY / 20)};
        Vector2 menubgpos = {-55 + (mouseX / 50), -50 + (mouseY / 50)};
        Vector2 creditspos = {-95, 53};
        Vector2 creditstextpos = {-105, 62};
        Vector2 settingspos = {-95, 120};
        Vector2 settingstextpos = {-108, 132};

        // Rectangle representing the button's bounds
        Rectangle textureBoundscredits = {creditspos.x, creditspos.y, (float)credits.width, (float)credits.height};
        Rectangle textureBoundssettings = {settingspos.x, settingspos.y, (float)settings.width, (float)settings.height};
        Rectangle textureBoundsplayb = {playpos.x, playpos.y, (float)playbutton.width, (float)playbutton.height};

        // Define boolean checks if mouse was hovered on sth
        bool mouseOvercredits = CheckCollisionPointRec(mousePos, textureBoundscredits);
        bool mouseOversettings = CheckCollisionPointRec(mousePos, textureBoundssettings);
        bool mouseOverplayb = CheckCollisionPointRec(mousePos, textureBoundsplayb);

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

        // Check if play button got pressed
        if (mouseOverplayb && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) startgame = true;

        std::stringstream ss;
        // Gameplay or Menu run
        if (startgame) { 
            ss << result;
            timer += GetFrameTime();
            if (timer >= spawnTime) {
                Spawn();
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> timerand(1, 2);
                spawnTime = timerand(gen);
                timer = 0;
            }
            
        } else {
            for (int i = 0; i < clones; i++) {
                visualdirectionmenu[i] += randomturn[i];
                float radians = directionmenu[i] * DEG2RAD;
                Vector2 dir = {cosf(radians), sinf(radians)};
                posistionsmenu[i].x += dir.x / speeds[i];
                posistionsmenu[i].y += dir.y / speeds[i];
                if (posistionsmenu[i].x <= 0 || posistionsmenu[i].x >= 800) {
                    dir.x = -dir.x;
                    randomturn[i] = -randomturn[i];
                }
                if (posistionsmenu[i].y <= 0 || posistionsmenu[i].y >= 600) {
                    dir.y = -dir.y;
                    randomturn[i] = -randomturn[i];
                }
                directionmenu[i] = atan2f(dir.y, dir.x) * RAD2DEG;
                visualposistionsmenu[i].x = posistionsmenu[i].x + (mouseX / 40);
                visualposistionsmenu[i].y = posistionsmenu[i].y + (mouseX / 40);
            }
        }

        // String
        std::string stringresult = std::to_string(result);
        stringresult = ss.str();
        int gamefontSize = 60;
        int textWidth = MeasureText(stringresult.c_str(), gamefontSize);
        int posX = (800 - textWidth) / 2;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (startgame) {
            DrawTextureEx(bg1, {1,0}, 0, 1, WHITE);
            DrawTextEx(font3, stringresult.c_str(), {(float)posX, 267}, gamefontSize, 2, RED);
            if (objectspawn.size() != 0) for (int i = 0; i < objectspawn.size(); i++) {
                std::string spawn;
                if (stod(objectspawn[i][1]) < 0) spawn = objectspawn[i][0] + "(" + objectspawn[i][1] + ")";
                else spawn = objectspawn[i][0] + objectspawn[i][1];
                Vector2 spawnpos = {posobject[i][0], posobject[i][1]};
                DrawTextEx(font3, spawn.c_str(), spawnpos, gamefontSize, 2, BLACK);
            }
        } else {
            DrawTextureEx(bg1, menubgpos, 0, 1.1, WHITE);
            for (int i = 0; i < clones; i++) {
                Vector2 origin = {textSizemenu[i].x / 2, textSizemenu[i].y / 2};
                DrawTextPro(font3, clonetext[i].c_str(), visualposistionsmenu[i], origin, visualdirectionmenu[i], textsizes[i], 2, BLACK);
            }
            DrawTextureEx(credits, creditspos, 0, 1, WHITE);
            DrawTextureEx(settings, settingspos, 0, 1, WHITE);
            DrawTextureEx(playbutton, playpos, 0, 1, WHITE);
            DrawTextEx(font1, "Math random", titlepos, 85, 2, RED);
            DrawTextEx(font2, "Credits", creditstextpos, 30, 2, WHITE);
            DrawTextEx(font2, "Settings", settingstextpos, 27, 2, WHITE);
        }
        EndDrawing();
    }

    UnloadTexture(bg1);
    UnloadTexture(credits);
    UnloadTexture(settings);
    UnloadTexture(playbutton);
    UnloadFont(font1);
    UnloadFont(font2);
    UnloadFont(font3);

    CloseWindow();

    return 0;
}

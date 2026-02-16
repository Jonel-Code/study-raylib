
#include "vector"
#include "string"
#include "raylib.h"
#include "./src/named_colors.cpp"
#include "./src/pong_game/pong_game.cpp"

int main()
{
    int WindowWidth = 800;
    int WindowHeight = 450;
    InitWindow(WindowWidth, WindowHeight, "Pong");

    // Camera2D camera{0};
    // camera.target = Vector2{0.0f, 0.0f};
    // camera.offset = Vector2{0.0f, (float)(WindowHeight)};
    // camera.rotation = 0.0f;
    // camera.zoom = 1.0f;

    auto Pong = new PongGame();
    Pong->Initialize();

    float fps = 0;

    while (!WindowShouldClose())
    {
        fps = GetFrameTime();
        BeginDrawing();
        ClearBackground(CORNFLOWER_BLUE);
        auto str = std::to_string(fps);
        DrawText(str.c_str(), 10, 10, 20, WHITE);
        // BeginMode2D(camera);
        Pong->Update();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

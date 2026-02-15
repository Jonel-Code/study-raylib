
#include "vector"
#include "string"
#include "raylib.h"
#include "./src/named_colors.cpp"
#include "./src/systems/traversal_system.cpp"
#include "./src/systems/level_system.cpp"

int main()
{
    int WindowWidth = 800;
    int WindowHeight = 450;
    InitWindow(WindowWidth, WindowHeight, "Clicker");

    Vector2 PlayOrigin{10, 10};
    Vector2 PlayEnd{(float)(WindowWidth - 20), (float)(WindowHeight - 20)};
    Vector2 BallMinSpeed{-100, -100};
    Vector2 BallMaxSpeed{100, 100};
    /// NOTE: currently, have a lot of balls (starts around 2000) will make skidding frequent, need to investigate the cause
    auto Balls = CreateRandomTraversingEntities<500>(
        PlayOrigin,
        PlayEnd,
        BallMinSpeed,
        BallMaxSpeed);

    auto BoxLevel = CreateBoxLevel(
        Vector2{10, 10},
        WindowWidth - 20,
        WindowHeight - 20);

    float fps = 0;

    while (!WindowShouldClose())
    {
        fps = GetFrameTime();
        BeginDrawing();
        ClearBackground(CORNFLOWER_BLUE);
        RenderTraversingEntities(Balls);
        UpdateTraversingEntities(Balls);
        ContainTraversingEntities(Balls, BoxLevel);
        auto str = std::to_string(fps);
        DrawText(str.c_str(), 10, 10, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}


#include "vector"
#include "raylib.h"
#include "./src/printer.cpp"
#include "./src/controllable_pawn.cpp"
#include "./src/named_colors.cpp"
#include "./src/level_bound_system.cpp"
#include "./src/moving_ball.cpp"
#include "./src/bouncing_ball_system.cpp"

int main()
{
    int WindowWidth = 800;
    int WindowHeight = 450;
    InitWindow(WindowWidth, WindowHeight, "Clicker");
    LevelBoundSystem *levelBoundSystem = LevelBoundSystem::Instance();
    levelBoundSystem->Init(Vector2{10, 10}, WindowWidth - 20, WindowHeight - 20);

    ControllablePawn *playerPawn = new ControllablePawn(50);

    std::vector<MovingBall *> ballPool = {
        new MovingBall(
            Vector2{(float)WindowWidth / 2.f, -(float)WindowHeight / 2.f},
            Vector2{200, 500}),
        new MovingBall(
            Vector2{(float)WindowWidth / 2.f, -(float)WindowHeight / 2.f},
            Vector2{-100, 100}),
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(CORNFLOWER_BLUE);
        levelBoundSystem->Update();
        playerPawn->Update();
        BatchHandleBouncingBall(ballPool);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

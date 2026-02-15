
#include "vector"
#include "string"
#include "raylib.h"
#include "./src/printer.cpp"
#include "./src/controllable_pawn.cpp"
#include "./src/named_colors.cpp"
#include "./src/level_bound_system.cpp"
#include "./src/moving_ball.cpp"
#include "./src/bouncing_ball_system.cpp"
#include "./src/systems/traversal_system.cpp"
#include "./src/systems/level_system.cpp"

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

    Vector2 PlayOrigin{10, 10};
    Vector2 PlayEnd{(float)(WindowWidth - 20), (float)(WindowHeight - 20)};
    Vector2 BallMinSpeed{-100, -100};
    Vector2 BallMaxSpeed{100, 100};
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
        levelBoundSystem->Update();
        // playerPawn->Update();
        // BatchHandleBouncingBall(ballPool);
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

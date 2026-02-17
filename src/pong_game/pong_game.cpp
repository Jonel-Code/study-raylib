#pragma once

#include "vector"
#include "cmath"
#include "iostream"
#include "raylib.h"

struct PongWall
{
    Vector2 Start;
    Vector2 End;
};

struct PongBall
{
    Vector2 Location;
    Vector2 Movement;
    Color RenderColor;
    float Size;
};

struct PongPlayer
{
    Vector2 Location;
    float Width;
    float Height;
    int KeyMoveUp;
    int KeyMoveDown;
    float MovementSpeed;
};

struct PongGameState
{
    std::vector<PongWall> Walls;
    std::vector<PongBall> Balls;
    std::vector<PongPlayer> Players;
    std::vector<int> PlayerScores;
};

Vector2 CaclulateMovementReflection(Vector2 &Movement, Vector2 Start, Vector2 End)
{
    auto MovementMag = std::sqrt((Movement.x * Movement.x) + (Movement.y * Movement.y));
    Vector2 normMovement{Movement.x / MovementMag, Movement.y / MovementMag};
    auto deltaX = End.x - Start.x;
    auto deltaY = End.y - Start.y;
    /// normalize segment is the perpendicular line of the segment
    Vector2 normSegment{-deltaY, deltaX};
    auto normSegmentMagSqr = (normSegment.x * normSegment.x) + (normSegment.y * normSegment.y);
    auto moveDotSegment = (normMovement.x * normSegment.x) + (normMovement.y * normSegment.y);
    auto normMS = 2 * (moveDotSegment / normSegmentMagSqr);
    return Vector2{
        ((normMovement.x - (normMS * normSegment.x)) * MovementMag),
        ((normMovement.y - (normMS * normSegment.y))) * MovementMag,
    };
}

class PongGame
{

protected:
    PongGameState *GameState;
    PongGameState *DirtyGameState;

    void RenderWalls()
    {
        for (auto &&wall : GameState->Walls)
        {
            DrawLine((int)wall.Start.x, (int)wall.Start.y, (int)wall.End.x, (int)wall.End.y, BLACK);
        }
    }

    void RenderBalls()
    {
        for (auto &&ball : GameState->Balls)
        {
            DrawCircle((int)ball.Location.x, (int)ball.Location.y, ball.Size, BLACK);
        }
    }

    PongWall CalculatePlayerWall(Vector2 Center, int Height)
    {
        float radius = (float)(Height / 2);
        float startY = Center.y - radius;
        float endY = Center.y + radius;
        float x = Center.x;
        return PongWall{
            Vector2{x, startY},
            Vector2{x, endY},
        };
    }

    void RenderPlayers()
    {
        for (auto &&player : GameState->Players)
        {
            auto wall = CalculatePlayerWall(player.Location, (int)player.Height);
            DrawLine((int)wall.Start.x, (int)wall.Start.y, (int)wall.End.x, (int)wall.End.y, BLACK);
        }
    }

    void RenderPlayerScores()
    {
    }

    void Render()
    {
        RenderWalls();
        RenderBalls();
        RenderPlayers();
        RenderPlayerScores();
    }

    void TryReflectBall(PongBall &ball, PongWall Wall, float Magnitude = 1)
    {
        static float frameTimeCheck = 0.0016f;
        if (CheckCollisionCircleLine(ball.Location, ball.Size, Wall.Start, Wall.End))
        {
            auto reflection = CaclulateMovementReflection(ball.Movement, Wall.Start, Wall.End);
            // detect if the reflection movement will still cause the ball to collide in the future frame (skidding effect)
            auto futureX = ball.Location.x + (reflection.x * Magnitude * frameTimeCheck);
            auto futureY = ball.Location.y + (reflection.y * Magnitude * frameTimeCheck);
            auto delta = GetFrameTime();
            if (!CheckCollisionCircleLine(Vector2{futureX, futureY}, ball.Size, Wall.Start, Wall.End))
            {
                ball.Movement.x = reflection.x * Magnitude;
                ball.Movement.y = reflection.y * Magnitude;
            }
        }
    }

    void CheckInteractions()
    {
        // check of ball interact with a wall or player and modify the respective data

        for (auto &ball : DirtyGameState->Balls)
        {
            for (auto &wall : DirtyGameState->Walls)
            {
                TryReflectBall(ball, wall);
            }

            for (auto &player : DirtyGameState->Players)
            {
                auto playerWall = CalculatePlayerWall(player.Location, (int)player.Height);
                TryReflectBall(ball, playerWall, 1.1f);
            }
        }
    }

    void UpdateWalls()
    {
        //
    }

    void UpdateBalls()
    {
        auto frameTime = GetFrameTime();
        for (auto &&ball : DirtyGameState->Balls)
        {
            ball.Location.x += ball.Movement.x * frameTime;
            ball.Location.y += ball.Movement.y * frameTime;
        }
    }

    void UpdatePlayers()
    {
        auto frameTime = GetFrameTime();
        for (auto &&player : DirtyGameState->Players)
        {
            if (IsKeyDown(player.KeyMoveUp))
            {
                player.Location.y -= frameTime * player.MovementSpeed;
            }

            if (IsKeyDown(player.KeyMoveDown))
            {
                player.Location.y += frameTime * player.MovementSpeed;
            }
        }
    }

    void UpdatePlayerScores()
    {
        //
    }

    void UpdateGameState()
    {
        SyncDirtyGameState();
        CheckInteractions();
        UpdateWalls();
        UpdateBalls();
        UpdatePlayers();
        UpdatePlayerScores();
    }

    void SyncDirtyGameState()
    {
        if (GameState != nullptr)
        {
            *DirtyGameState = *GameState;
        }
    }

    void CommitGameState()
    {
        if (GameState != nullptr && DirtyGameState != nullptr)
        {
            /// this should perform the deep copy of dirtygamestate to the GameState
            *GameState = *DirtyGameState;
        }
    }

public:
    PongGame()
    {
        GameState = new PongGameState();
        DirtyGameState = new PongGameState();
    }
    ~PongGame()
    {
        delete GameState;
        delete DirtyGameState;
    }
    void Initialize()
    {
        float ms = 200;
        float offset = 10;
        Vector2 Origin{offset, offset};
        auto width = GetScreenWidth() - offset;
        auto height = GetScreenHeight() - offset;

        GameState->Balls.reserve(1);
        GameState->Balls.push_back(PongBall{
            Vector2{(float)(width / 2), (float)(height / 2)},
            Vector2{150, 150},
            BLACK,
            20,
        });

        Vector2 ul{Origin.x, Origin.y};
        Vector2 ur{(float)width, Origin.y};
        Vector2 ll{Origin.x, (float)height};
        Vector2 lr{(float)width, (float)height};

        GameState->Walls.reserve(2);
        GameState->Walls.push_back(PongWall{ul, ur});
        GameState->Walls.push_back(PongWall{ll, lr});

        GameState->Players.reserve(2);
        GameState->Players.push_back(PongPlayer{
            ul,
            10,
            100,
            KEY_W,
            KEY_S,
            ms,
        });
        GameState->Players.push_back(PongPlayer{
            ur,
            10,
            100,
            KEY_I,
            KEY_K,
            ms,
        });
    }

    void Update()
    {
        /// this update should be running parallel to the render
        UpdateGameState();
        Render();
        /// commits the updated gamestate to be used in the next frame
        CommitGameState();
    }
};
#pragma once

#include "vector"
#include "cmath"
#include "iostream"
#include "raylib.h"

class ControllablePawn
{
public:
    ControllablePawn()
    {
        //
    }
    ControllablePawn(int PawnNormalSpeed, int PawnSize = 10)
    {
        NormalSpeed = PawnNormalSpeed;
        SprintSpeed = PawnNormalSpeed * 2;
        Size = (float)PawnSize;
        BaseSize = PawnSize;
    }

    void Update()
    {
        HandleInput();
        RenderPawn();
    }

protected:
    Vector2 WorldLocation{0, 0};

    void Move(Vector2 Direction, int Magnitude = 1)
    {
        float frameTime = GetFrameTime();
        float vectorAngle = std::atan2(Direction.y, Direction.x);
        float normX = std::cosf(vectorAngle) * Magnitude * frameTime;
        float normY = std::sinf(vectorAngle) * Magnitude * frameTime;
        WorldLocation.x += normX;
        WorldLocation.y += normY;
    }

    void ChangeSize(float Magnitude)
    {
        float frameTime = GetFrameTime();
        Size += BaseSize * Magnitude * frameTime;
        if (Size < BaseSize)
        {
            Size = (float)BaseSize;
        }
    }

private:
    float Size = 10.f;
    int BaseSize = 10;
    Vector2 FrameMove{0, 0};
    int CurrentSpeed = 10;
    int NormalSpeed = 10;
    int SprintSpeed = 20;

    void HandleInput()
    {
        /// directional move
        if (IsKeyDown(KEY_W))
        {
            FrameMove.y += 1;
        }
        if (IsKeyDown(KEY_A))
        {
            FrameMove.x -= 1;
        }
        if (IsKeyDown(KEY_S))
        {
            FrameMove.y -= 1;
        }
        if (IsKeyDown(KEY_D))
        {
            FrameMove.x += 1;
        }

        /// speed up
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            if (CurrentSpeed != SprintSpeed)
            {
                CurrentSpeed = SprintSpeed;
            }
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT))
        {
            if (CurrentSpeed != NormalSpeed)
            {
                CurrentSpeed = NormalSpeed;
            }
        }

        /// Grown Shrink
        if (IsKeyDown(KEY_SPACE))
        {
            ChangeSize(10);
        }
        if (IsKeyDown(KEY_LEFT_ALT))
        {
            ChangeSize(-10);
        }

        if (FrameMove.x != 0 || FrameMove.y != 0)
        {
            Move(FrameMove, CurrentSpeed);
            FrameMove.x = 0;
            FrameMove.y = 0;
        }
    }

    void RenderPawn()
    {
        /// use negative value of world location since raylib renders from top-left to bottom right making the y value inverted
        DrawCircle((int)WorldLocation.x, -(int)WorldLocation.y, Size, BLACK);
    }
};
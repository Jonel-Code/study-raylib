#pragma once

#include "iostream"
#include "raylib.h"
#include "utils.cpp"

class MovingBall
{

public:
    MovingBall(Vector2 Starting, Vector2 Direction, float Radius = 20)
    {
        WorldLocation = Starting;
        Movement = Direction;
        Size = Radius;
    }

    void Update()
    {
        Traverse();
        Render();
    }

    void ChangeDirection(Vector2 Direction)
    {
        Movement = Direction;
    }

    inline Vector2 *GetLocation()
    {
        return &WorldLocation;
    }

    inline float GetSize()
    {
        return Size;
    }

    inline Vector2 GetMovementDirection(){
        return Movement;
    }

protected:
    Vector2 WorldLocation{0, 0};
    Vector2 Movement{10, 10};
    float Size = 10.f;

    void Traverse()
    {
        const float frameTime = GetFrameTime();
        const float deltaX = Movement.x * frameTime;
        const float deltaY = Movement.y * frameTime;
        WorldLocation.x += deltaX;
        WorldLocation.y += deltaY;
    }

    void Render()
    {
        DrawCircle((int)WorldLocation.x, -(int)WorldLocation.y, Size, BLACK);
    }
};
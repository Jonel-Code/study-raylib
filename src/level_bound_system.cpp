#pragma once

#include "iostream"
#include "cmath"
#include "raylib.h"

struct Line
{
    Vector2 Start, End;
};

class LevelBoundSystem
{
public:
    static LevelBoundSystem *Instance()
    {
        static LevelBoundSystem *Singleton;
        if (Singleton == nullptr)
        {
            Singleton = new LevelBoundSystem();
        }
        return Singleton;
    }

    void Init(Vector2 Origin, int InWidth, int InHeight)
    {
        OriginPosition = Origin;
        Width = InWidth;
        Height = InHeight;
        CalculateBounds();
    }

    void Update()
    {
        Render();
    }

    bool CheckCircleCollision(Vector2 Location, float Radius)
    {

        for (auto &&line : BoundingLines)
        {
            if (CheckCollisionCircleLine(Location, Radius, line.Start, line.End))
            {
                return true;
            }
        }

        return false;
    }

    Line *GetCollisionLine(Vector2 Location, float Radius)
    {
        for (auto &line : BoundingLines)
        {
            if (CheckCollisionCircleLine(Location, Radius,
                                         Vector2{line.Start.x, -line.Start.y},
                                         Vector2{line.End.x, -line.End.y}))
            {
                return &line;
            }
        }
        return nullptr;
    }

private:
    LevelBoundSystem()
    {
        CalculateBounds();
    }

protected:
    Vector2 OriginPosition{0, 0};
    int Height = 100;
    int Width = 100;

    Line BoundingLines[4];

    void CalculateBounds()
    {
        Line top = {
            OriginPosition,
            Vector2{OriginPosition.x + Width, OriginPosition.y},
        };
        Line bottom = {
            Vector2{OriginPosition.x, OriginPosition.y + Height},
            Vector2{OriginPosition.x + Width, OriginPosition.y + Height},
        };
        Line left = {
            OriginPosition,
            Vector2{OriginPosition.x, OriginPosition.y + Height},
        };
        Line right = {
            Vector2{OriginPosition.x + Width, OriginPosition.y},
            Vector2{OriginPosition.x + Width, OriginPosition.y + Height},
        };

        BoundingLines[0] = top;
        BoundingLines[1] = bottom;
        BoundingLines[2] = left;
        BoundingLines[3] = right;
    }

    void Render()
    {
        for (auto &&line : BoundingLines)
        {

            DrawLine((int)line.Start.x, (int)line.Start.y, (int)line.End.x, (int)line.End.y, BLACK);
        }
    }
};
#pragma once

#include "vector"
#include "cmath"
#include "iostream"
#include "raylib.h"

// #define TRAVERSING_ENTITY_RADIUS = 20.0
static float GlobalBallSize  = 20;

template <int Size>
struct TraversingEntity
{
    Vector2 Location[Size];
    Vector2 Movement[Size];
};

template <int Size>
void UpdateTraversingEntities(TraversingEntity<Size> *Entites)
{
    float frameTime = GetFrameTime();
    for (int i = 0; i < Size; i++)
    {
        auto move = Entites->Movement[i];
        Entites->Location[i].x += move.x * frameTime;
        Entites->Location[i].y += move.y * frameTime;
    }
}

template <int Size>
void RenderTraversingEntities(TraversingEntity<Size> *Entities)
{

    for (int i = 0; i < Size; i++)
    {
        Vector2 location = Entities->Location[i];
        DrawCircle((int)location.x, (int)location.y, GlobalBallSize, BLACK);
    }
}

float _Fract(float value)
{
    return value - std::floorf(value);
}

int _RandomBySeed(float start, float end, int index, int randomSeed = 1923)
{
    static int pad = 39;

    float r = _Fract(std::sinf((index * pad) * (float)randomSeed));
    int ceil = (int)(end - start);
    float rMag = std::roundf(r * 100) / 99;
    float rRaw = rMag * (float)ceil;
    int rand = (int)(std::roundf(rRaw) + start);

    return rand;
}

template <int Size>
TraversingEntity<Size> *CreateRandomTraversingEntities(Vector2 Start, Vector2 End, Vector2 MinSpeed, Vector2 MaxSpeed)
{
    auto Entities = new TraversingEntity<Size>{};
    float offset = GlobalBallSize;
    for (int i = 0; i < Size; i++)
    {
        int x = _RandomBySeed(Start.x + offset, End.x - offset, i, 101);
        int y = _RandomBySeed(Start.y + offset, End.y - offset, i, 123);
        Entities->Location[i] = Vector2{(float)x, (float)y};

        int mx = _RandomBySeed(MinSpeed.x, MaxSpeed.x, i, 201);
        int my = _RandomBySeed(MinSpeed.y, MaxSpeed.y, i, 223);
        std::cout << "speed: " << mx << ' ' << my << '\n';
        Entities->Movement[i] = Vector2{(float)mx, (float)my};
    }
    return Entities;
}
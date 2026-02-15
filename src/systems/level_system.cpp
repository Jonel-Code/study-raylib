#pragma once

#include "vector"
#include "cmath"
#include "iostream"
#include "raylib.h"
#include "./traversal_system.cpp"

struct LevelBoundSegment
{
    Vector2 Start;
    Vector2 End;
};

static LevelBoundSegment EmptySegment = LevelBoundSegment{
    Vector2{0, 0},
    Vector2{0, 0},
};

inline bool IsEmptySegment(LevelBoundSegment &Segment)
{
    return Segment.Start.x == 0 && Segment.Start.y == 0 && Segment.End.x == 0 && Segment.End.y == 0;
}

LevelBoundSegment GetFirstCollidedSegment(Vector2 &Location, std::vector<LevelBoundSegment> *Segments)
{
    for (int i = 0; i < Segments->size(); i++)
    {
        auto segment = Segments->at(i);
        if (CheckCollisionCircleLine(Location, GlobalBallSize, segment.Start, segment.End))
        {
            return Segments->at(i);
        }
    }
    return EmptySegment;
}

Vector2 CaclulateMovementReflection(Vector2 &Movement, LevelBoundSegment &Segment)
{
    auto MovementMag = std::sqrt((Movement.x * Movement.x) + (Movement.y * Movement.y));
    Vector2 normMovement{Movement.x / MovementMag, Movement.y / MovementMag};
    auto Start = Segment.Start;
    auto End = Segment.End;
    auto deltaX = End.x - Start.x;
    auto deltaY = End.y - Start.y;
    /// normalize segment is the perpendicular line of the segment
    Vector2 normSegment{-deltaY, deltaX};
    auto normSegmentMagSqr = (normSegment.x * normSegment.x) + (normSegment.y * normSegment.y);
    auto moveDotSegment = (normMovement.x * normSegment.x) + (normMovement.y * normSegment.y);
    auto normMS = 2 * (moveDotSegment / normSegmentMagSqr);
    Vector2 reflection{
        (normMovement.x - (normMS * normSegment.x)) * MovementMag,
        (normMovement.y - (normMS * normSegment.y)) * MovementMag,
    };

    return reflection;
}

template <int Size>
void ContainTraversingEntities(TraversingEntity<Size> *Entities, std::vector<LevelBoundSegment> *Segments)
{
    for (int i = 0; i < Size; i++)
    {
        auto location = Entities->Location[i];
        auto CollidedSegment = GetFirstCollidedSegment(location, Segments);
        if (!IsEmptySegment(CollidedSegment))
        {
            Vector2 NewMovement = CaclulateMovementReflection(Entities->Movement[i], CollidedSegment);
            Entities->Movement[i].x = NewMovement.x;
            Entities->Movement[i].y = NewMovement.y;
        }
    }
}

std::vector<LevelBoundSegment> *CreateBoxLevel(Vector2 Origin, int Width, int Height)
{
    auto Level = new std::vector<LevelBoundSegment>{};
    Level->reserve(4);

    Vector2 ul{Origin.x, Origin.y};
    Vector2 ur{Origin.x + (float)Width, Origin.y};
    Vector2 ll{Origin.x, Origin.y + (float)Height};
    Vector2 lr{Origin.x + (float)Width, Origin.y + (float)Height};

    /// top
    Level->push_back(LevelBoundSegment{ul, ur});
    /// bottom
    Level->push_back(LevelBoundSegment{ll, lr});
    /// left
    Level->push_back(LevelBoundSegment{ul, ll});
    /// right
    Level->push_back(LevelBoundSegment{ur, lr});

    return Level;
}
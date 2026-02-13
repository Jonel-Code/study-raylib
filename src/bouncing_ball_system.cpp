#pragma once

#include "cmath"
#include "iostream"
#include "vector"
#include "raylib.h"
#include "moving_ball.cpp"
#include "level_bound_system.cpp"

void HandleBallBounce(MovingBall *Ball)
{
    auto lbs = LevelBoundSystem::Instance();

    if (auto line = lbs->GetCollisionLine(*Ball->GetLocation(), Ball->GetSize()))
    {
        auto currentMovement = Ball->GetMovementDirection();

        /// the following uses reflection formula for vector bouncing a line segment
        /// reflection = NormalizeVector - ((2 * ( NormalizedVector • NormalizeLineSegment ) / (NormalizeLineSegmentMagnitude^2) * NormalizeLineSegment) )

        auto vectorMagnitude = std::sqrt((currentMovement.x * currentMovement.x) + (currentMovement.y * currentMovement.y));
        Vector2 normalizeVector{
            currentMovement.x / vectorMagnitude,
            currentMovement.y / vectorMagnitude,
        };

        auto segmentStart = line->Start;
        auto segmentEnd = line->End;
        auto deltaX = segmentEnd.x - segmentStart.x;
        auto deltaY = segmentEnd.y - segmentStart.y;
        Vector2 normalizeLineSegment{-deltaY, deltaX};
        auto normalizeLineMagnitudeSqr = (normalizeLineSegment.x * normalizeLineSegment.x) + (normalizeLineSegment.y * normalizeLineSegment.y);
        auto vDotN = (normalizeVector.x * normalizeLineSegment.x) + (normalizeVector.y * normalizeLineSegment.y);
        auto normVn = 2 * (vDotN / normalizeLineMagnitudeSqr);

        Vector2 reflection{
            normalizeVector.x - (normVn * normalizeLineSegment.x),
            normalizeVector.y - (normVn * normalizeLineSegment.y),
        };

        Ball->ChangeDirection(Vector2{
            reflection.x * vectorMagnitude,
            reflection.y * vectorMagnitude,
        });
    }
}

void BatchHandleBouncingBall(std::vector<MovingBall *> Balls)
{

    for (auto &&ball : Balls)
    {
        ball->Update();
        HandleBallBounce(ball);
    }
}
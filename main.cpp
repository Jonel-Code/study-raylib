#include "raylib.h"
#include "./src/printer.cpp"
#include "./src/controllable_pawn.cpp"
#include "./src/named_colors.cpp"

int main()
{
    InitWindow(800, 450, "Clicker");
    ControllablePawn *PlayerPawn = new ControllablePawn(50);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(CORNFLOWER_BLUE);
        PlayerPawn->Update();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

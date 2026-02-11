#include "raylib.h"


int main()
{
    InitWindow(800,450, "Clicker");
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Clicker window text", 0,0,20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

#include <raylib.h>

int main()
{
    InitWindow(600,600,"Raylib");

    while(!WindowShouldClose()){
        // Update

        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(GetMousePosition().x - 100 ,GetMousePosition().y - 100,200,200,GREEN);
        EndDrawing();
    }
}
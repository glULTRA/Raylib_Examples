#include <raylib.h>

int main()
{
    InitWindow(800,600,"Raylib");

    Color color = BLUE;

    Rectangle rect = {100.0f,200.0f,150.0f,150.0f};
    Rectangle rect2 = {550.0f,200.0f,150.0f,150.0f};

    while(!WindowShouldClose()){
        // Update
        // Check right rectangle.
        if(CheckCollisionPointRec(GetMousePosition() , rect2)) color = YELLOW;
        // Check left rectangle.
        else if(CheckCollisionPointRec(GetMousePosition() , rect)) color = RED;
        // Check if none.
        else color = BLUE;
        

        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(rect.x, rect.y, rect.width, rect.height, color);
            DrawRectangle(rect2.x, rect2.y, rect2.width, rect2.height, color);
        EndDrawing();
    }
}
#include <raylib.h>

int main(){
    InitWindow(600,600,"Raylib");

    Vector2 mousePos = GetMousePosition();

    while(!WindowShouldClose()){
        // Update
        
        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(mousePos.x,mousePos.y,200,200,GREEN);
        EndDrawing();
    }
}
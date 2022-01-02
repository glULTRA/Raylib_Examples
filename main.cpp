#include <iostream>
#include <raylib.h>
#include <cmath>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612


int main()
{
    // Initialize Window
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}
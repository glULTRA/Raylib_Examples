#include <iostream>
#include <raylib.h>
#include <raymath.h>


#if defined(_WIN32)
    #define GLSL_VERSION 330
#else
    #define GLSL_VERSION 100
#endif

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612


int main()
{
    // Initialize Window
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Shader
    Shader shader = LoadShader("examples/res/Shader/glsl330/Mandelbrot.vs", "examples/res/Shader/glsl330/Mandelbrot.fs");

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawRectangle(0, 0, SCR_WIDTH, SCR_HEIGHT, WHITE);
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();
}
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
    Shader shader = LoadShader(0, TextFormat("examples/res/Shader/glsl%i/Mandelbrot.fs", GLSL_VERSION));

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(WHITE);
            BeginShaderMode(shader);

            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();
}
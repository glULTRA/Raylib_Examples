#include <iostream>
#include <cmath>
#include <vector>
#include <raylib.h>

#if defined(_WIN32)
    #define GLSL_VERSION 330
#else
    #define GLSL_VERSION 100
#endif

#define SCR_WIDTH 612
#define SCR_HEIGHT 612

int main()
{
    // Initialize Window
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Shader
    Shader shader = LoadShader(0, TextFormat("examples/res/Shader/glsl%i/Shader.fs", GLSL_VERSION));

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawCircle(306, 306, 50, GREEN);
            EndShaderMode();

        EndDrawing();
    }

    CloseWindow();
}
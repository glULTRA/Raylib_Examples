#include <iostream>
#include <raylib.h>
#include <cmath>
#include <raymath.h>


#if defined(_WIN32)
    #define GLSL_VERSION 330
#else
    #define GLSL_VERSION 100
#endif

#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612


int main()
{
    // Initialize Window
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Camera
    Camera3D camera = Camera{Vector3{2.0f, 4.0f, 6.0f}, Vector3{0.0f, 1.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f}};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_THIRD_PERSON);

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(WHITE);
            BeginMode3D(camera);
                
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
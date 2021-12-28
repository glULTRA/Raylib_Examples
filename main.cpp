#include <iostream>
#include <cmath>
#include <vector>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

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

    // Camera
    Camera3D camera = Camera3D{ { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    SetCameraMode(camera, CAMERA_THIRD_PERSON);

    // Model
    Model model = Model{1.0f};
    model = LoadModel("examples/res/Object/Model2/watermill.obj");


    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);
                DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 0.3f, WHITE);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
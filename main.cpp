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
    Model model2 = Model{1.0f};
    model = LoadModel("examples/res/Object/Model1/gltf/rigged_figure.glb");
    model2 = LoadModel("examples/res/Object/Model1/gltf/vertex_colored_object.glb");


    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);
        model.transform      = MatrixRotate(Vector3{1.0f, 0.0f, 0.0f}, 3.0f * time);
        model2.transform     = MatrixScale(0.5f,0.5f,0.5f);
        model2.transform     = MatrixMultiply(model2.transform ,MatrixRotate(Vector3{1.0f, 0.0f, 0.0f}, 3.0f * time));
        model2.transform     = MatrixMultiply(model2.transform ,MatrixTranslate(0.0f, 0.0f, std::sin(time)));

        static int slice = 10;
        static float space = 1.0f;

        if(IsKeyPressed(KEY_UP)) slice++;
        else if(IsKeyPressed(KEY_DOWN)) slice--;

        if(IsKeyPressed(KEY_W)) space+=0.1f;
        else if(IsKeyPressed(KEY_S)) space-=0.1f;

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(slice, space);
                DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
                DrawModel(model2, Vector3{2.0f, 0.0f, -1.0f}, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
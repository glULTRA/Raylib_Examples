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
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Camera
    Camera3D camera = Camera3D{ { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    SetCameraMode(camera, CAMERA_THIRD_PERSON);

    // Texture
    Image image = LoadImage("examples/res/Texture/heightmap.png");
    Texture2D texture = LoadTextureFromImage(image);
    
    // Mesh
    Mesh mesh = GenMeshHeightmap(image, Vector3{1.0f, 1.0f, 1.0f});
    // Model
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    UnloadImage(image);

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
                DrawGrid(10, 1.0f);
                DrawModel(model, Vector3{-3.0f, 0.0f, -3.0f}, 5.0f, BLUE);
            EndMode3D();
            DrawTexture(texture, 450, 50, WHITE);

        EndDrawing();
    }

    CloseWindow();
}
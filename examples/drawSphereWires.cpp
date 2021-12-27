#include <raylib.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612

int main()
{
    // Initialize Window
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Camera
    Camera3D camera = Camera3D{ { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
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
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10,1.5f);
                DrawSphereWires(Vector3{0.0f, 0.0f, 0.0f}, 1.4f, 16, 16, RED);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
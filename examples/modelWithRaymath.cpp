#include <raylib.h>
#include <raymath.h>
#include <cmath>

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
    Model model = Model{};
    Model model2 = Model{};
    model = LoadModel("res/Object/Model1/gltf/rigged_figure.glb");
    model2 = LoadModel("res/Object/Model1/gltf/vertex_colored_object.glb");


    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);
        model.transform     = MatrixRotate(Vector3{1.0f, 0.0f, 0.0f}, 3.0f * time);
        model2.transform    = MatrixTranslate(1.0f, 0.3f, 2.0f * std::cos(time));   

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10,1.5f);
                DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
                DrawModel(model2, Vector3{2.0f, 0.0f, -1.0f}, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
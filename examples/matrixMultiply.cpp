#include <cmath>
#include <raylib.h>
#include <raymath.h>

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
    Model model  = Model{1.0f};
    Model model2 = Model{1.0f};
    Model model3 = Model{1.0f};
    model   = LoadModel("res/Object/Model1/gltf/raylib_32x32.glb");
    model2  = LoadModel("res/Object/Model1/gltf/vertex_colored_object.glb");
    model3  = LoadModel("res/Object/Model1/gltf/girl.glb");


    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);
        model.transform     = MatrixScale(0.1f, 0.1f, 0.1f);
        model.transform     = MatrixMultiply(model.transform ,MatrixTranslate(0.0f, 0.0f, 4.0f));
        model.transform     = MatrixMultiply(model.transform ,MatrixRotate(Vector3{0.0f, 1.0f, 0.0f}, time));
        
        model2.transform    = MatrixScale(0.5f,0.5f,0.5f);
        model2.transform    = MatrixMultiply(model2.transform ,MatrixRotate(Vector3{1.0f, 0.0f, 0.0f}, 3.0f * time));
        model2.transform    = MatrixMultiply(model2.transform ,MatrixTranslate(0.0f, 0.0f, std::sin(time)));
        
        model3.transform    = MatrixRotate(Vector3{0.0f,1.0f,0.0f}, time);
        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10,1.5f);
                DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
                DrawModel(model2, Vector3{2.0f, 0.0f, -1.0f}, 1.0f, WHITE);
                DrawModel(model3, Vector3{-2.0f, 0.0f, -1.0f}, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
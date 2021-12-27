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
    Shader shader = LoadShader(0, TextFormat("res/Shader/glsl%i/Shader.fs", GLSL_VERSION));

    // Camera
    Camera3D camera = {0};
    camera.fovy = 45.0f;
    camera.position = Vector3{5.0f, 4.0f, 5.0f};
    camera.target = Vector3{0.0f, 2.0f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.projection = CAMERA_PERSPECTIVE;

    //SetCameraMode(camera, CAMERA_ORBITAL);

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        static float xColor = 0.0f;
        xColor = std::sin(time) / 2.0f + 0.5f;

        camera.position.x += std::cos(time);
        camera.position.y += std::sin(time);
        camera.position.z += std::sin(time);

        UpdateCamera(&camera);

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                BeginShaderMode(shader);
                    DrawGrid(10, 1.0f);
                    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, RED);
                    SetShaderValue(shader, GetShaderLocation(shader, "xColor"), &xColor, SHADER_UNIFORM_FLOAT);
                EndShaderMode();
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
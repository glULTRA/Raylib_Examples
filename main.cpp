#include <iostream>
#include <raylib.h>
#include <cmath>
#include <vector>

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
    Camera3D camera = Camera3D{Vector3{4.0f, 2.0f, 4.0f}, Vector3{0.0f, 1.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f}};
    camera.fovy = 45.0f;
    camera.projection  = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_THIRD_PERSON);

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        UpdateCamera(&camera);
        static float xzOffset = 1.0f;
        static float yoffset  =  0.1f;
        static float ypos = 0.0f;
        static float multiYpos[20][20];

        //xzOffset = (std::sin(time) / 2) + 0.5;
        yoffset  = (std::sin(time) / 2) + 0.5;

         for(int i = 0; i <= 10; i++){
            for(int j = 0; j <= 10; j++){
                if(i >= 5)
                    multiYpos[i][j] = yoffset * ((i - j)+1);
                else
                    multiYpos[i][j] = yoffset * ((i + j)+1);
            }
        }

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);
                for(int i = 0; i <= 10; i++){
                    for(int j = 0; j <= 10; j++){
                        DrawCube(Vector3{(float)(i * xzOffset), multiYpos[i][j], (float)(j * xzOffset)}, 0.5f , 0.5f, 0.5f, RED);
                        DrawCubeWires(Vector3{(float)(i * xzOffset), multiYpos[i][j], (float)(j * xzOffset)}, 0.6f , 0.6f, 0.6f, BLUE);
                    }
                }
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
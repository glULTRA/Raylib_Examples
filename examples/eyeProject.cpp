#include <stdio.h>
#include <raylib.h>
#include <cmath>

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Circle Attributes
    Vector2 ScelerationLeftPos  = Vector2{150.0f,300.0f};
    Vector2 ScelerationRightPos = Vector2{450.0f,300.0f};

    Vector2 EyeLeftPos  = Vector2{150.0f,300.0f};
    Vector2 EyeRightPos  = Vector2{450.0f,300.0f};


    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        EyeLeftPos  = GetMousePosition();
        EyeRightPos = GetMousePosition();
        if(!CheckCollisionPointCircle(ScelerationLeftPos, EyeLeftPos, 75-25)){
            float dy = EyeLeftPos.y - ScelerationLeftPos.y;
            float dx = EyeLeftPos.x - ScelerationLeftPos.x;
            float angle = atan2f(dy, dx);
            float dxx = (75 - 25) * cosf(angle);
            float dyy = (75 - 25) * sinf(angle);

            EyeLeftPos.x = ScelerationLeftPos.x + dxx;
            EyeLeftPos.y = ScelerationLeftPos.y + dyy;
        }
        if(!CheckCollisionPointCircle(ScelerationRightPos, EyeRightPos, 75-25)){
            float dy = EyeRightPos.y - ScelerationRightPos.y;
            float dx = EyeRightPos.x - ScelerationRightPos.x;
            float angle = atan2f(dy, dx);
            float dxx = (75 - 25) * cosf(angle);
            float dyy = (75 - 25) * sinf(angle);

            EyeRightPos.x = ScelerationRightPos.x + dxx;
            EyeRightPos.y = ScelerationRightPos.y + dyy;
        }


        /* <---------Render---------> */ 
        BeginDrawing();
            ClearBackground(Color{30,70,100});
            // Left Eye
            DrawCircleV(ScelerationLeftPos ,75, GRAY);
            DrawCircleV(EyeLeftPos ,25, ORANGE);
            DrawCircleV(EyeLeftPos ,12, BLACK);


            DrawCircleV(ScelerationRightPos,75, GRAY);
            DrawCircleV(EyeRightPos ,25, BLUE);
            DrawCircleV(EyeRightPos ,12, BLACK);            // Right Eye
        EndDrawing();
    }
}
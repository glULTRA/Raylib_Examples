#include <iostream>
#include <cmath>
#include <raylib.h>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

int main()
{
    // Initialize Window
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // DVD properities
    float DVD_Radius = 50.0f;
    Vector2 DVD_Pos = Vector2{SCR_WIDTH/2.0f, SCR_HEIGHT/2.0f};
    Vector2 DVD_Speed = Vector2{5.0f, 4.0f};
    
    Texture2D texture = LoadTexture("examples/res/Texture/dvd-logo.png");
    texture.width  = DVD_Radius;
    texture.height = DVD_Radius;


    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
        DVD_Pos.x += DVD_Speed.x;
        DVD_Pos.y += DVD_Speed.y;
        texture.width = DVD_Radius;
        texture.height = DVD_Radius;

        bool xSideCollision = DVD_Pos.x < DVD_Radius || DVD_Pos.x > (SCR_WIDTH - DVD_Radius);
        bool ySideCollision = DVD_Pos.y < DVD_Radius || DVD_Pos.y > (SCR_HEIGHT - DVD_Radius);

        if(xSideCollision) DVD_Speed.x *= -1.0f;
        if(ySideCollision) DVD_Speed.y *= -1.0f;

        if(xSideCollision || ySideCollision)
        {
            static int i = 0;
            i++;
            //bool isTook5Sec = time > 5.0f;
            if(i >= 100){
                DVD_Pos.x = SCR_WIDTH/2.0f;
                DVD_Pos.y = SCR_HEIGHT/2.0f;
                i = 0;
            }
        }

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(0,0);
            DrawCircleV(DVD_Pos, DVD_Radius, RED);
            DrawTexture(texture, DVD_Pos.x - (DVD_Radius/2.0f), DVD_Pos.y - (DVD_Radius/2.0f), WHITE);
            
            // GUI Controls
            DVD_Radius = GuiSliderBar(Rectangle{500, 10, 85, 30},"DVD Radius", "", DVD_Radius, 1.0f, 299.0f);

        EndDrawing();
    }
}
#include <iostream>
#include <raylib.h>
#include <cmath>
#include <raymath.h>


#if defined(_WIN32)
    #define GLSL_VERSION 330
#else
    #define GLSL_VERSION 100
#endif

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612


int main()
{
    // Initialize Window
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // Texture
    Texture2D foreground = LoadTexture("examples/res/Texture/cyberpunk_street_foreground.png");
    Texture2D midground  = LoadTexture("examples/res/Texture/cyberpunk_street_midground.png");

    // Texture Position
    float scale = 2.0f;
    Vector2 foreground_pos = Vector2{0.0f, (float) SCR_HEIGHT - (scale*foreground.height)};
    Vector2 midground_pos  = Vector2{0.0f, (float)(SCR_HEIGHT - 90) - (scale*foreground.height)};


    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();

        static float f_speed = 1.9f;
        static float m_speed = 0.5f;
        foreground_pos.x -= f_speed;
        midground_pos.x  -= m_speed;

        if(foreground_pos.x <= -foreground.width * scale) foreground_pos.x = 0;
        if(midground_pos.x <= -midground.width * scale) midground_pos.x = 0;

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(Color{30, 70, 100, 255});

            DrawTextureEx(midground, midground_pos, 0.0f, scale, WHITE);
            DrawTextureEx(midground, Vector2{midground_pos.x + (midground.width * scale), midground_pos.y}, 0.0f, scale, WHITE);

            DrawTextureEx(foreground, foreground_pos, 0.0f, scale, WHITE);
            DrawTextureEx(foreground, Vector2{foreground_pos.x + (foreground.width * scale), foreground_pos.y}, 0.0f, scale, WHITE);

            f_speed = GuiSliderBar(Rectangle{SCR_WIDTH - 100, 50, 70, 30}, "Foreground Speed", "", f_speed, 0.1f, 10.0f);
            m_speed = GuiSliderBar(Rectangle{SCR_WIDTH - 100, 80, 70, 30}, "Midground Speed", "", m_speed, 0.1f, 10.0f);
        EndDrawing();
    }

    CloseWindow();
}
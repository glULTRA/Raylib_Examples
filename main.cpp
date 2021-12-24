#include <iostream>
#include <cmath>
#include <raylib.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600
#define SCR_TITLE "Raylib"

int main(){
    // Initialize window
    InitWindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);

    // Sceleration
    Vector2 Sceleration = Vector2{150.0f,300.0f};
    float Sceleration_Radius = 75.0f;
    Vector2 Eye = Vector2{150.0f, 300.0f};
    float Eye_Radius = 25.0f;

    // FPS
    SetTargetFPS(60);

    // Game Loop
    while(!WindowShouldClose()){
        /* <---- Update ----> */
        Eye = GetMousePosition();

        // Check Collision With Sceleretation.
        if(!CheckCollisionPointCircle(Sceleration ,Eye, Sceleration_Radius - Eye_Radius)){
            float dy = Eye.y - Sceleration.y;
            float dx = Eye.x - Sceleration.x;
            float angle = atan2f(dy, dx);
            float dxx = (Sceleration_Radius - Eye_Radius) * cosf(angle);
            float dyy = (Sceleration_Radius - Eye_Radius) * sinf(angle);
            Eye.x = Sceleration.x + dxx;
            Eye.y = Sceleration.y + dyy;

            std::cout << angle << "\n";
        }

        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            /* <---- Drawing ----> */
            DrawCircleV(Sceleration, Sceleration_Radius, GRAY);  
            DrawCircleV(Eye, Eye_Radius, ORANGE);          

        EndDrawing();
    }
}
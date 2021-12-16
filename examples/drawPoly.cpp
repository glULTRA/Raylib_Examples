#include <stdio.h>
#include <raylib.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    Rectangle player = {20, 100, 100, 100};

    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */

        // Collision With Window

        // Sides and Rotations
        static int sides = 3;
        static float rotation = 0.0f; 
            if(IsKeyPressed(KEY_UP))
                sides++;
            else if(IsKeyPressed(KEY_DOWN))
                if(sides > 2)
                    sides--;
        
        if(IsKeyDown(KEY_RIGHT))
            rotation += 1.1f;
        else if(IsKeyDown(KEY_LEFT))
            rotation -= 1.1f;
            
        
        // Check Collision

        /* <---------Render---------> */ 
        BeginDrawing();
            ClearBackground(BLACK);
            //DrawRectangleGradientEx(player, RED,GREEN, BLUE, YELLOW);
            DrawFPS(10, 10);        
            DrawPoly({300,300}, sides, 100, rotation, RED);
            DrawText("Press Right/Left key to rotate.\n", 0, 470, 20, ORANGE);
            DrawText("Press Up/Down key to change sides.", 0, 500, 20, ORANGE);
        EndDrawing();
    }
}
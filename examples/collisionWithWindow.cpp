#include <stdio.h>
#include <raylib.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    Rectangle player = {20, 100, 100, 100};
    Vector2 mousePos = {0, 0};
    Color color = RED; // Default color
    

    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        mousePos = GetMousePosition();
        player.x = mousePos.x - 50;
        player.y = mousePos.y - 50;
        static int frameCounter = 0;
        frameCounter++;

        // Collision With Window
        if(player.x < 0.0f)
            player.x = 0.0f;
        if((player.x+player.width) > SCR_WIDTH)
            player.x = SCR_WIDTH - player.width;
        if(player.y < 0.0f)
            player.y = 0.0f;
        if((player.y + player.height) > SCR_HEIGHT)
            player.y = SCR_HEIGHT - player.height;
        
        // Check Collision

        /* <---------Render---------> */ 
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(player.x, player.y,player.width,player.height,GREEN);
            
        EndDrawing();
    }
}
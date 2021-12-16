#include <stdio.h>
#include <raylib.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    Rectangle rect = {300, 300, 100, 100};
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

    
        // Check Collision

        /* <---------Render---------> */ 
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(rect.x,rect.y,rect.width,rect.height,color);
            DrawRectangle(player.x, player.y,player.width,player.height,GREEN);
            if(CheckCollisionRecs(rect,player)){
                DrawText("Collided", 100,100,60,RED);
                color = ORANGE;
            }
            else{
                color = RED;
            }
        EndDrawing();
    }
}
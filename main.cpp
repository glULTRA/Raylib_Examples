#include <stdio.h>
#include <raylib.h>

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

// each 1 seconds is equal to each 60 frames of the game.

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    Rectangle rect = {100, 100, 200, 80};
    Vector2 mousePos = {0, 0};

    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        /* <---------Update---------> */
        mousePos = GetMousePosition();
        static int frameCounter = 0;
        frameCounter++;

    
        // Check Collision

        /* <---------Render---------> */ 
        BeginDrawing();
            ClearBackground(BLACK);
            if(frameCounter < 240){
                DrawText("Wait for 4 seconds", 100,100,50,RED);
            }
            else{
                DrawText("Boom", 100,100,50,GREEN);
            }
            if(frameCounter < 60){
                DrawText("\n1", 100,100,50,GREEN);
            }
            else if(frameCounter < 120){
                DrawText("\n2", 100,100,50,GREEN);
            }else if(frameCounter < 180){
                DrawText("\n3", 100,100,50,GREEN);
            }else if(frameCounter < 240){
                DrawText("\n4", 100,100,50,GREEN);
            }

        EndDrawing();
    }
}
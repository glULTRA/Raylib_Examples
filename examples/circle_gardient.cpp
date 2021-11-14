#include <raylib.h>
#include <cmath>
#include <stdio.h>

int main(){

    InitWindow(600,600,"Raylib");


    int frameCounter = 0;

    // Shape
    Rectangle rect = {200 ,200 , 200, 200};
    float speed = 1.2f;


    SetTargetFPS(60);

    while(!WindowShouldClose()){

        // Update
        if(IsKeyDown(KEY_W))
            rect.y -= speed;
        else if(IsKeyDown(KEY_S))
            rect.y += speed;
        
        if(IsKeyDown(KEY_A))
            rect.x -= speed;
        else if(IsKeyDown(KEY_D))
            rect.x += speed;

        // Drawing
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Hello i am ULTRA", 20,40, 20, WHITE);
            //DrawRectangle(rect.x ,rect.y ,rect.width, rect.height, RED);
            //DrawRectangleGradientEx(rect, RED, GREEN, YELLOW, BLUE);
            //DrawCircle(40,40,50, RED);
            //DrawTriangle({200,200}, {300, 200}, {250, 150},GREEN);
            DrawCircleGradient(150,300,100, WHITE, BLACK);
            DrawCircleGradient(450,300,100, WHITE, BLACK);
            DrawCircleGradient(300,300,100, WHITE, BLACK);

        EndDrawing();
    }
}
#include <raylib.h>

int main()
{
    InitWindow(800,600,"Raylib");

    Color color1 = BLUE;
    Color color2 = BLUE;
    Color color3 = BLUE;

    Rectangle rect  = {0.0f,200.0f,150.0f,150.0f};
    Rectangle rect2 = {650.0f,200.0f,150.0f,150.0f};
    Rectangle rect3 = {325.0f,200.0f,150.0f,150.0f};

    Vector2 rectPoint1 = {rect.x + 150,rect.y};
    Vector2 rectPoint2 = {rect2.x,rect2.y};

    Vector2 ballSpeed = {-0.09f, 0.2f};

    while(!WindowShouldClose()){
        // Update
        rect3.x += ballSpeed.x;
        if(CheckCollisionPointRec(rectPoint1, rect3))
            ballSpeed.x *= -1.0f;        
        else if(CheckCollisionPointRec(rectPoint2, rect3))
            ballSpeed.x *= -1.0f;
        
        

        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(rect.x, rect.y, rect.width, rect.height, color1);
            DrawRectangle(rect2.x, rect2.y, rect2.width, rect2.height, color2);
            DrawRectangle(rect3.x, rect3.y, rect3.width, rect3.height, color3);
        EndDrawing();
    }
}
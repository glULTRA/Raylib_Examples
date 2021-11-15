#include <raylib.h>
#include <ctime>
#include <cstdlib>
#include <vector>

int main()
{
    srand(time(NULL));
    InitWindow(600,600,"Raylib");

    Color colors[5] = {GREEN,RED,YELLOW,WHITE,BLUE};
    Vector2 pixel = {300.0f, 300.0f};
    std::vector<Vector2> pixels;

    while(!WindowShouldClose()){
        // Update
        static int interval = 0;
        static int currentDir = 0;
        interval++;
        if(interval == 10){
            currentDir = rand() % 4;
            interval = 0;
        }

        if(currentDir == 0){
            pixel.x += 1.0f;
        }
        else if (currentDir == 1){
            pixel.x -= 1.0f;
        }
        else if (currentDir == 2){
            pixel.y += 1.0f;
        }
        else if (currentDir == 3){
            pixel.y -= 1.0f;
        }


        pixels.push_back(pixel);

        // Render
        BeginDrawing();
            ClearBackground(BLACK);
            for(auto pix: pixels){
                DrawPixel(pix.x, pix.y, RED);
            }
        EndDrawing();
    }
}
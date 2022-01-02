#include <iostream>
#include <raylib.h>
#include <cmath>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#define SCR_WIDTH 612
#define SCR_HEIGHT 612


int main()
{
    // Initialize Window
    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Raylib");

    // pixels
    int speed = 1;
    Vector2 pixel = Vector2{(SCR_WIDTH / 2), (SCR_HEIGHT / 2)};
    Color color = RED;
    std::vector<Vector2> pixeles;
    std::vector<Color> colors;

    // FPS
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        /* <---------Update---------> */
        float time = GetTime();
       
        static int  rate            = 3;
        static int  orginalRate     = rate;
        static bool isToUp          = pixel.y > (SCR_HEIGHT/2)  - rate;
        static bool isToRight       = false;
        static bool isToDown        = false;
        static bool isToLeft        = false;
        static int  vecSize         = 0;
        static bool isReset         = false;
        static bool isReverse       = false;

        for(int i = 0; i < speed; i++){
            
            if(!isReverse)
            {
                if(isToUp){
                    isToUp = (pixel.y) > ((SCR_HEIGHT/2) - rate);
                    pixel.y -= 1.0f;
                    color = RED;
                    if(!isToUp)
                        isToRight = true;
                }
                else if(isToRight){
                    isToRight = pixel.x < (SCR_WIDTH/2) + rate;
                    pixel.x += 1.0f;
                    color = BLUE;
                    if(!isToRight)
                        isToDown = true;
                }
                else if(isToDown){
                    isToDown = pixel.y < (SCR_HEIGHT/2) + (rate);
                    pixel.y += 1.0f;
                    color  = GREEN;
                    if(!isToDown)
                        isToLeft = true;
                }
                else if(isToLeft){
                    isToLeft = pixel.x > (SCR_WIDTH/2) - (rate);
                    pixel.x -= 1.0f;
                    color = YELLOW;
                }
                else{
                    rate += orginalRate;
                    isToUp = true;
                }

                pixeles.push_back(pixel);
                colors.push_back(color);
            }
            else{
                if(pixeles.empty() || colors.empty()) break;
                pixeles.pop_back();
                colors.pop_back();
            }
            
        }

        if(isReset){
            pixel = Vector2{(SCR_WIDTH / 2), (SCR_HEIGHT / 2)};
            pixeles.clear();
            colors.clear();
            rate = orginalRate;
        }


        /* <---- Render ----> */
        BeginDrawing();
            ClearBackground(BLACK);
            for(int i = 0; i < pixeles.size(); i++){
                DrawPixelV(pixeles[i], colors[i]);
            }
            DrawRectangle(SCR_WIDTH-200, SCR_HEIGHT-200, 200, 200, Fade(LIGHTGRAY, 0.3f));
            speed = (int)GuiSliderBar(Rectangle{SCR_WIDTH - 110, SCR_HEIGHT - 50, 60, 30}, "Speed", "", speed, 1.0f, 100.0f);
            orginalRate = GuiSliderBar(Rectangle{SCR_WIDTH - 110, SCR_HEIGHT - 80, 60, 30}, "Space", "", orginalRate, 1.0f, 50.0f);
            isReset = GuiButton(Rectangle{SCR_WIDTH - 110, SCR_HEIGHT - 110, 60, 30}, "Reset");
            isReverse = GuiCheckBox(Rectangle{SCR_WIDTH - 110, SCR_HEIGHT - 140, 60, 30}, "Reverse", isReverse);

        EndDrawing();
    }

    CloseWindow();
}
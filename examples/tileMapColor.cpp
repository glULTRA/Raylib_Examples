#include <raylib.h>
#include <cmath>
#include <math.h>

#define XOFFSET 10
#define YOFFSET 10

int main() 
{
	InitWindow(612, 612, "My Window");
	
	Vector2 blockPos = {(GetScreenWidth() / float(XOFFSET)), (GetScreenHeight() / float(YOFFSET))};

	SetTargetFPS(60);
	while (!WindowShouldClose()) 
	{
		/* <---- UPDATE ----> */
		float time = GetTime();
		static float fontSize = 16;
		float xValue = (std::cos(time) / 2) + 0.5f;
		float yValue = (std::sin(time) / 2) + 0.5f;

		/* <---- RENDER ----> */
		BeginDrawing();
			ClearBackground(BLACK);
			for (int i = 0; i < XOFFSET; i++) {
				for (int j = 0; j < YOFFSET; j++) 
				{
                    Color color1{i * 10,0, 0, 255};
					DrawRectangle(blockPos.x * i, blockPos.y * j, blockPos.x + 1.0f, blockPos.y+ 1.0f, color1);
				}
			}
			DrawFPS(0, 0);
		EndDrawing();
	}
}
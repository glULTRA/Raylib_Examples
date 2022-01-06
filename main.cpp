#include <iostream>
#include <raylib.h>
#include <cmath>
#include <ctime>
#include <math.h>

#define MAPSIZEX 4
#define MAPSIZEY 8
#define BLOCKSIZE 50
#define OFFSET 5

// Tile Map
char tileMap[MAPSIZEX][MAPSIZEY] = {
	{'!', '#', '#', '@', '#', '#', '#', '#'}, 
	{'#', '#', '#', '@', '#', '#', '#', '#'}, 
	{'#', '#', '#', '@', '#', '#', '#', '#'}, 
	{'#', '#', '#', '#', '#', '#', '#', '#'}, 
};
Vector2 player_pos = {0,0}; // X-Y axies position and matrices position
Color colState[MAPSIZEX][MAPSIZEY];
Vector2 block_pos[MAPSIZEX][MAPSIZEY];

void GenerateRandomMap();
void DrawGameMap();
void UpdateGame();
void HandleInput();
void Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);

int main() 
{
	InitWindow(612, 612, "My Window");
	

	SetTargetFPS(60);
	while (!WindowShouldClose()) 
	{
		/* <---- UPDATE ----> */
		float time = GetTime();
		UpdateGame();
		float xValue = (std::cos(time) / 2) + 0.5f;
		float yValue = (std::sin(time) / 2) + 0.5f;

		/* <---- RENDER ----> */
		BeginDrawing();
			ClearBackground(BLACK);
			// Clear For Console
			system("cls");
			DrawGameMap();
		EndDrawing();
	}
}

void DrawGameMap()
{
	for(int i = 0; i < MAPSIZEX; i++){
		for(int j = 0; j < MAPSIZEY; j++)
		{
			if(tileMap[i][j] == ' ') continue;
			DrawRectangle(block_pos[i][j].x, block_pos[i][j].y, BLOCKSIZE, BLOCKSIZE, colState[i][j]);
		}
	}

	// For Console
	for(int i = 0; i < MAPSIZEX; i++){
		for(int j = 0; j < MAPSIZEY; j++)
		{
			std::cout << tileMap[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << player_pos.x << " " << player_pos.y << std::endl;
}
void UpdateGame()
{
	HandleInput();
	
	for(int i = 0; i < MAPSIZEX; i++)
	{
		for(int j = 0; j < MAPSIZEY; j++)
		{
			if(tileMap[i][j] == '!'){
				player_pos.x = j;
				player_pos.y = i;
			}
			if(tileMap[i][j] == '!')      // PLAYER
				colState[i][j] = GREEN;
			else if(tileMap[i][j] == '#') // SAND
				colState[i][j] = RED;
			else if(tileMap[i][j] == ' ') // PATH
				continue;
			else if(tileMap[i][j] == '@') // BLOCK
				colState[i][j] = BLUE;
			
			block_pos[i][j].x = (BLOCKSIZE + OFFSET)*j;
			block_pos[i][j].y = (BLOCKSIZE + OFFSET)*i;
		}
	}
}
void HandleInput(){
	for(int i = 0; i < MAPSIZEX; i++)
	{
		for(int j = 0; j < MAPSIZEY; j++)
		{
			if(IsKeyPressed(KEY_D)){
				if(tileMap[i][j] == '!'){
					if(j == MAPSIZEY-1) return;
					Movements(i, j, 1, 0);
					return;
				}
			}
			else if(IsKeyPressed(KEY_A)){
				if(tileMap[i][j] == '!'){
					if(j == 0) return;
					Movements(i, j,-1, 0);
					return;
				}
			}
			if(IsKeyPressed(KEY_S)){
				if(tileMap[i][j] == '!'){
					if(i == MAPSIZEX-1) return;
					Movements(i, j, 0, 1);
					return;
				}
			}
			else if(IsKeyPressed(KEY_W)){
				if(tileMap[i][j] == '!'){
					if(i == 0) return;
					Movements(i, j, 0,-1);
					return;
				}
			}

			// Breaking 
			if(IsKeyPressed(KEY_K)){
				if(player_pos.y == MAPSIZEX-1) break;
				BreakDir(i, j, 0, 1);
			}
			if(IsKeyPressed(KEY_I)){
				if(player_pos.y == 0) break;
				BreakDir(i, j, 0,-1);
			}
			if(IsKeyPressed(KEY_L)){
				if(player_pos.x == MAPSIZEY-1) break;
				BreakDir(i, j, 1, 0);
			}
			if(IsKeyPressed(KEY_J)){
				if(player_pos.x == 0) break;
				BreakDir(i, j,-1, 0);
			}
		}
	}
}

void Movements(int x, int y, int xDir, int yDir)
{
	if(tileMap[x+yDir][y+xDir] == ' ')
	{
		tileMap[x][y] = ' ';
		tileMap[x+yDir][y + xDir] = '!';
		colState[x+yDir][y+xDir] = GREEN;
		//return true;
	}
}

void BreakDir(int x, int y, int xDir, int yDir){
	if(tileMap[x][y] == '!')
	{
		if(tileMap[x+yDir][y+xDir] == '#'){
			tileMap[x+yDir][y+xDir] = ' ';
		}
	}
}
#include <iostream>
#include <raylib.h>
#include <cmath>
#include <ctime>
#include <math.h>

#define SCR_WIDTH 	612
#define SCR_HEIGHT 	612
#define MAPSIZEX 	25
#define MAPSIZEY 	25
#define BLOCKSIZE 	(SCR_WIDTH / MAPSIZEX)
#define OFFSET 		5
int blockLevel = 	50;

// Tile Map
char tileMap[MAPSIZEX][MAPSIZEY] = {
	{'!', '#', '#', '@', '#', '#', '#', '#'}, 
	{'#', '#', '#', '@', '#', '#', '#', '#'}, 
	{'#', '#', '#', '@', '#', '#', '#', '#'}, 
	{'#', '#', '#', '#', '#', '#', '#', '#'}, 
};
char mapList[3] = {'#', '@', '$'};
Vector2 player_pos = {0,0}; // X-Y axies position and matrices position
Color colState[MAPSIZEX][MAPSIZEY];
Vector2 block_pos[MAPSIZEX][MAPSIZEY];

void GenerateRandomMap();
void DrawtileMap();
void UpdateGame();
void HandleInput();
void Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);

int main() 
{
	// Set Random Numbers
	srand(time(NULL));
	// Initialize Window
	InitWindow(612, 612, "Dig Out");

	// Generate a random map.
	GenerateRandomMap();

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
			DrawtileMap();
		EndDrawing();
	}
}

void GenerateRandomMap()
{
	char getMapList[32];
    int interval  = 0;
    int counterOfDollar = 0;
    int counterOfBlock  = 0;
    int entireBlockInRow = 0;
    int entireBlockInCol = 0;
    for(int i = 0; i < MAPSIZEX; i++){
        for (int j = 0; j < MAPSIZEY; j++){
            // Skip Touching the player.
            if(i == 0 && j == 0) continue;
            // Touch other things.
            Retry:
                int getRandom = rand()%3;
                tileMap[i][j] = mapList[rand()%3];

                // We should set $ at 5 - 8 position at least.
                if(tileMap[i][j] == '$' && j < 5)
                    goto Retry;
                
                // We shouldn't make to much block maybe 10 is enough.
                if(tileMap[i][j] == '@')
                    counterOfBlock++;

                if(counterOfBlock > blockLevel)
                {
                    counterOfBlock--;
                    goto Retry;
                }
                // We should check if player's both side is not blocked.
                if(tileMap[i][j] == tileMap[0][1] || tileMap[i][j] == tileMap[1][0]){
                    if(tileMap[i][j] == '@'){
                        counterOfBlock--;
                        goto Retry;
                    }
                }

                // We should check if entire row or column is not blocked.
                entireBlockInRow = 0;
                entireBlockInCol = 0;
                for(int row = 0; row < 4; row++)
                {
                    if(tileMap[row][j] == '@')
                        entireBlockInRow++;
                    if(entireBlockInRow > 3)
                    {
                        entireBlockInRow--;
                        counterOfBlock--;
                        goto Retry;
                    }
                }
                for(int col = 0; col < 8; col++)
                {
                    if(tileMap[i][col] == '@')
                        entireBlockInRow++;
                    if(entireBlockInCol > 7)
                    {
                        entireBlockInCol--;
                        counterOfBlock--;
                        goto Retry;
                    }
                }
                // We should only set one dollar $.
                if(tileMap[i][j] == '$')
                    counterOfDollar++;
                if(counterOfDollar > 1)
                {
                    counterOfDollar--;
                    goto Retry;
                }
        }
    }
    if(counterOfBlock < blockLevel)
        GenerateRandomMap();
}

void DrawtileMap()
{
	for(int i = 0; i < MAPSIZEX; i++){
		for(int j = 0; j < MAPSIZEY; j++)
		{
			if(tileMap[i][j] == ' ') continue;
			DrawRectangle(block_pos[i][j].x, block_pos[i][j].y, BLOCKSIZE, BLOCKSIZE, colState[i][j]);
		}
	}

	// For Console
#if defined(CONSOLE_ON)
	for(int i = 0; i < MAPSIZEX; i++){
		for(int j = 0; j < MAPSIZEY; j++)
		{
			std::cout << tileMap[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << player_pos.x << " " << player_pos.y << std::endl;
#endif
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
			else if(tileMap[i][j] == '$') // JEWLLERY
				colState[i][j] = ORANGE;
			
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
	if(tileMap[x+yDir][y+xDir] == ' ' ||  tileMap[x+yDir][y+xDir] == '$')
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
#include <iostream>
#include <raylib.h>
#include <cmath>
#include <ctime>
#include <math.h>

#define SCR_WIDTH 	612
#define SCR_HEIGHT 	612
#define MAPSIZEX 	8
#define MAPSIZEY 	8
#define BLOCKSIZE 	(SCR_WIDTH / 15)
#define OFFSET 		5
int blockLevel 	= 	8;
int score 		= 	0;
int level 		= 	0;

// Tile Map
#if (MAPSIZEX == 4 && MAPSIZEY == 8)
	char tileMap[MAPSIZEX][MAPSIZEY] = {
		{'!', '#', '#', '@', '#', '#', '#', '#'}, 
		{'#', '#', '#', '@', '#', '#', '#', '#'}, 
		{'#', '#', '#', '@', '#', '#', '#', '#'}, 
		{'#', '#', '#', '#', '#', '#', '#', '#'}, 
	};
#else
	char tileMap[MAPSIZEX][MAPSIZEY] = {'!'};
#endif

char mapList[5] = {'#', '#', '#', '@', '$'};
Vector2 player_pos = {0,0}; // X-Y axies position and matrices position
Color colState[MAPSIZEX][MAPSIZEY];
Vector2 block_pos[MAPSIZEX][MAPSIZEY];
bool isWinTheGame = false;

void GenerateRandomMap();
void DrawtileMap();
void UpdateGame();
void HandleInput();
void Movements(int x, int y, int xDir, int yDir);
void BreakDir(int x, int y, int xDir, int yDir);
void SearchForBlockGravity();
bool IsMapGoodToPlay();

int main() 
{
	// Set Random Numbers
	srand(time(NULL));
	// Initialize Window
	InitWindow(SCR_WIDTH, SCR_HEIGHT, "Dig Out");

	// Next Level
	NextLevel:

	// Generate a random map.
	do{
		GenerateRandomMap();
	}while(!IsMapGoodToPlay());

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
			#if defined(CONSOLE_ON)
				system("cls");
			#endif
			DrawtileMap();
			DrawText(TextFormat("Level : %d", level), SCR_WIDTH-100, 0, 16, GREEN);
			DrawText(TextFormat("SCORE : %d", score), SCR_WIDTH-100, 20, 16, GREEN);
			DrawRectangleLines((SCR_WIDTH/2)-180, (SCR_HEIGHT/2)-180, 364, 364, WHITE);
		EndDrawing();

		/* <---- UPDATE ---->*/
		if(isWinTheGame)
		{
			isWinTheGame = false;
			blockLevel++;
			level++;
			score+=5;
			player_pos = {0, 0};
			tileMap[0][0] = '!';
			goto NextLevel;
		}
	}
}

void GenerateRandomMap()
{
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
                int getRandom = rand()%5;
                tileMap[i][j] = mapList[rand()%5];

				//if(j % ((MAPSIZEY*MAPSIZEX)/2) != 0){
				//	tileMap[i][j] = '#';
				//	continue;
				//}

                // We should set $ at 5 - 8 position at least.
                if(tileMap[i][j] == '$' && j < (MAPSIZEY - (rand()%(MAPSIZEY/2))))
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
                for(int row = 0; row < MAPSIZEX; row++)
                {
                    if(tileMap[row][j] == '@')
                        entireBlockInRow++;
                    if(entireBlockInRow > (MAPSIZEX - 1))
                    {
                        entireBlockInRow--;
                        counterOfBlock--;
                        goto Retry;
                    }
                }
                for(int col = 0; col < MAPSIZEY; col++)
                {
                    if(tileMap[i][col] == '@')
                        entireBlockInRow++;
                    if(entireBlockInCol > (MAPSIZEY-1))
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
	if(counterOfDollar != 1)
		GenerateRandomMap();
}

void DrawtileMap()
{
	for(int i = 0; i < MAPSIZEX; i++){
		for(int j = 0; j < MAPSIZEY; j++)
		{
			if(tileMap[i][j] == ' ') continue;
			DrawRectangle((block_pos[i][j].x) + 130, (block_pos[i][j].y) + 130, BLOCKSIZE, BLOCKSIZE, colState[i][j]);
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
				colState[i][j] = BLUE;
			else if(tileMap[i][j] == ' ') // PATH
				continue;
			else if(tileMap[i][j] == '@') // BLOCK
				colState[i][j] = RED;
			else if(tileMap[i][j] == '$') // JEWLLERY
				colState[i][j] = YELLOW;
			
			block_pos[i][j].x = (BLOCKSIZE + OFFSET)*j;
			block_pos[i][j].y = (BLOCKSIZE + OFFSET)*i;
		}
	}

	SearchForBlockGravity();
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

	if(IsKeyPressed(KEY_R)){
		GenerateRandomMap();
		tileMap[0][0] = '!';
	}
}

void Movements(int x, int y, int xDir, int yDir)
{
	if(tileMap[x+yDir][y+xDir] == ' ' ||  tileMap[x+yDir][y+xDir] == '$')
	{
		if(tileMap[x+yDir][y+xDir] == '$'){
			isWinTheGame = true;
		}
		tileMap[x][y] = ' ';
		tileMap[x+yDir][y + xDir] = '!';
		colState[x+yDir][y+xDir] = GREEN;
		
	}
}

void BreakDir(int x, int y, int xDir, int yDir){
	if(tileMap[x][y] == '!')
	{
		if(tileMap[x+yDir][y+xDir] == '#')
		{
			 if(tileMap[x-1][y] == '@' && tileMap[x][y] != '!')
			 {
                tileMap[x-1][y] = ' '; 
                tileMap[x][y] = '@';
            }
			tileMap[x+yDir][y+xDir] = ' ';
		}
	}
}

void SearchForBlockGravity(){
    for(int i = 0; i < MAPSIZEX; i++)
	{
        for(int j = 0; j < MAPSIZEY; j++)
		{
            if(tileMap[i][j] == '@')
			{
                if(tileMap[i+1][j] == ' '){
                    tileMap[i][j] = ' ';
                    tileMap[i+1][j] = '@';
                }
            }
        }
    }
}

bool IsMapGoodToPlay(){
    for(int i = 0; i < MAPSIZEX; i++){
        for(int j = 0; j < MAPSIZEY; j++){
            if(tileMap[i][j] == tileMap[j][i]){
                if(tileMap[i][j] == '@' && tileMap[j][i] == '@')
                {
                    return false;
                }
            } 
                    
        }
    }
    return true;
}
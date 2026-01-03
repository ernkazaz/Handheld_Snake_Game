#ifndef GAME_H
#define GAME_H

#define GRID_WIDTH  27
#define GRID_HEIGHT 15
#define BLOCK_SIZE  3

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[100]; 
    int length;     
    int dirX;       
    int dirY;        
} Snake;

typedef struct {
    Point pos;
    int active;
} Apple;

typedef enum {
    MENU,
    GAME,
    GAME_OVER
} GameState_t;

extern Snake mySnake;
extern Apple myApple;
extern GameState_t CurrentState;

void Game_Init(void);
void Game_Update(void);
void Game_SetDirection(int dx, int dy);
void Game_Draw(void);
void Menu_Draw(void);
void GameOver_Draw(void);

#endif
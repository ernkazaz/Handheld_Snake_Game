#include "Game.h"
#include "Nokia5110.h" // Çizim fonksiyonlari için
#include <stdlib.h>    // rand() için

// Global degiskenler
Snake mySnake;
Apple myApple;
GameState_t CurrentState = MENU; // Baslangiç durumu MENÜ
int LastScore = 0; // Son skoru tutmak için

// Rastgele Sayi
int RandomNum(int min, int max){
    return min + (rand() % (max - min + 1));
}

// Elma Olusturma
void GenerateApple(void){
    int valid = 0;
    int i;
    while(!valid){
        myApple.pos.x = RandomNum(0, GRID_WIDTH - 1); 
        myApple.pos.y = RandomNum(0, GRID_HEIGHT - 1);
        valid = 1;
        // Elma yilanin üstünde mi?
        for(i=0; i < mySnake.length; i++){
            if(mySnake.body[i].x == myApple.pos.x && mySnake.body[i].y == myApple.pos.y){
                valid = 0; 
                break;
            }
        }
    }
    myApple.active = 1;
}

// --- OYUN BASLATMA ---
void Game_Init(void){
    mySnake.length = 8; 
    mySnake.dirX = 1;   // Saga git
    mySnake.dirY = 0;
    
    // Yilani ortala
    for(int i=0; i<mySnake.length; i++){
        mySnake.body[i].x = 15 - i; 
        mySnake.body[i].y = 7;      
    }
    GenerateApple(); 
}

// --- YÖN DEGISTIRME ---
void Game_SetDirection(int dx, int dy){
    // Ters yöne dönemez (Saga giderken sola dönemez)
    if(mySnake.dirX == 1 && dx == -1) return;
    if(mySnake.dirX == -1 && dx == 1) return;
    if(mySnake.dirY == 1 && dy == -1) return;
    if(mySnake.dirY == -1 && dy == 1) return;

    mySnake.dirX = dx;
    mySnake.dirY = dy;
}

// --- OYUN DÖNGÜSÜ (UPDATE) ---
void Game_Update(void){
    int i;
    
    // 1. Kuyrugu Tasi
    for(i = mySnake.length - 1; i > 0; i--){
        mySnake.body[i] = mySnake.body[i-1]; 
    }
    
    // 2. Kafayi Ilerlet
    mySnake.body[0].x += mySnake.dirX;
    mySnake.body[0].y += mySnake.dirY;
    
    // --- BURASI DEGISTI ---
    
    // 3. Duvar Çarpisma Kontrolü
    if(mySnake.body[0].x >= GRID_WIDTH || mySnake.body[0].x < 0 || 
       mySnake.body[0].y >= GRID_HEIGHT || mySnake.body[0].y < 0){
        
        LastScore = mySnake.length; // <-- EKLENDI: Ölmeden skoru kaydet
        
        Game_Draw(); 
        // for(long d=0; d<2000000; d++); 
        CurrentState = GAME_OVER; 
        return;
    }

    // 4. Elma Yeme (Burasi ayni)
    if(mySnake.body[0].x == myApple.pos.x && mySnake.body[0].y == myApple.pos.y){
        if(mySnake.length < 100){
            mySnake.length++;
            mySnake.body[mySnake.length-1] = mySnake.body[mySnake.length-2];
        }
        GenerateApple();
    }

    // 5. Kendine Çarpma (GAME OVER)
    for(i = 1; i < mySnake.length; i++){
        if(mySnake.body[0].x == mySnake.body[i].x && 
           mySnake.body[0].y == mySnake.body[i].y){
             
             // ÖLMEDEN ÖNCE SON KEZ ÇIZ!
						 LastScore = mySnake.length;
             Game_Draw();
             
             // Biraz bekle
             // for(long d=0; d<2000000; d++);
             
             CurrentState = GAME_OVER; 
             return; 
        }
    }
}

void Menu_Draw(void){
    Nokia5110_Clear(); 
    
    // Title
    Nokia5110_SetCursor(25, 0);
    Nokia5110_PrintString("Snake");
    
    // Check if we have a score to show (Game has been played at least once)
    if(LastScore > 0) {
        Nokia5110_SetCursor(15, 2);
        Nokia5110_PrintString("SCORE: ");
        Nokia5110_PrintNumber(LastScore);
				Nokia5110_SetCursor(5, 4);
				Nokia5110_PrintString("Press button");
				Nokia5110_SetCursor(16, 5);
				Nokia5110_PrintString("to play!");
    } else {
        Nokia5110_SetCursor(5, 4);
				Nokia5110_PrintString("Press button");
				Nokia5110_SetCursor(16, 5);
				Nokia5110_PrintString("to play!");
    }
    
    // Navigation instructions

}


// --- OYUN EKRANI ÇIZIMI ---
void Game_Draw(void){
    Nokia5110_ClearBuffer(); 
    
    Nokia5110_DrawBorder(); // Çerçeve
    
    // Yilani Çiz
    for(int i=0; i<mySnake.length; i++){
        Nokia5110_PrintBlock(mySnake.body[i].x, mySnake.body[i].y);
    }
    
    // Elmayi Çiz
    if(myApple.active){
        Nokia5110_DrawApple(myApple.pos.x, myApple.pos.y);
    }
    
    Nokia5110_DisplayBuffer(); 
}
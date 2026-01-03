#ifndef NOKIA5110_H
#define NOKIA5110_H

#include <stdint.h>


#define BLOCK_SIZE 3 


#define GRID_WIDTH  27 
#define GRID_HEIGHT 15


void Nokia5110_Init(void);
void Nokia5110_Clear(void);         
void Nokia5110_SetCursor(uint8_t newX, uint8_t newY);


void Nokia5110_ClearBuffer(void);   
void Nokia5110_DisplayBuffer(void); 


void Nokia5110_PrintBlock(int gridX, int gridY);
void Nokia5110_DrawApple(int gridX, int gridY);
void Nokia5110_DrawBorder(void);             


void Nokia5110_PrintChar(char c);       
void Nokia5110_PrintString(char *ptr); 

void Nokia5110_PrintNumber(int num);

#endif
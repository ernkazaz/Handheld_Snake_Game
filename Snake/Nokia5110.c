#include "TM4C123GH6PM.h"
#include "Nokia5110.h"

const uint8_t ASCII[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 32 - Bosluk (Space)
    {0x00, 0x00, 0x5f, 0x00, 0x00}, // 33 - !
    
    // RAKAMLAR (0-9)
    {0x3e, 0x51, 0x49, 0x45, 0x3e}, // 48 - 0
    {0x00, 0x42, 0x7f, 0x40, 0x00}, // 49 - 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 50 - 2
    {0x21, 0x41, 0x45, 0x4b, 0x31}, // 51 - 3
    {0x18, 0x14, 0x12, 0x7f, 0x10}, // 52 - 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 53 - 5
    {0x3c, 0x4a, 0x49, 0x49, 0x30}, // 54 - 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 55 - 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 56 - 8
    {0x06, 0x49, 0x49, 0x29, 0x1e}, // 57 - 9
    
    {0x00, 0x36, 0x36, 0x00, 0x00}, // 58 - :
    
    // BÜYÜK HARFLER (A-Z)
    {0x7c, 0x12, 0x11, 0x12, 0x7c}, // 65 - A
    {0x7f, 0x49, 0x49, 0x49, 0x36}, // 66 - B
    {0x3e, 0x41, 0x41, 0x41, 0x22}, // 67 - C
    {0x7f, 0x41, 0x41, 0x22, 0x1c}, // 68 - D
    {0x7f, 0x49, 0x49, 0x49, 0x41}, // 69 - E
    {0x7f, 0x09, 0x09, 0x09, 0x01}, // 70 - F
    {0x3e, 0x41, 0x49, 0x49, 0x7a}, // 71 - G
    {0x7f, 0x08, 0x08, 0x08, 0x7f}, // 72 - H
    {0x00, 0x41, 0x7f, 0x41, 0x00}, // 73 - I
    {0x20, 0x40, 0x41, 0x3f, 0x01}, // 74 - J
    {0x7f, 0x08, 0x14, 0x22, 0x41}, // 75 - K
    {0x7f, 0x40, 0x40, 0x40, 0x40}, // 76 - L
    {0x7f, 0x02, 0x0c, 0x02, 0x7f}, // 77 - M
    {0x7f, 0x04, 0x08, 0x10, 0x7f}, // 78 - N
    {0x3e, 0x41, 0x41, 0x41, 0x3e}, // 79 - O
    {0x7f, 0x09, 0x09, 0x09, 0x06}, // 80 - P
    {0x3e, 0x41, 0x51, 0x21, 0x5e}, // 81 - Q
    {0x7f, 0x09, 0x19, 0x29, 0x46}, // 82 - R
    {0x46, 0x49, 0x49, 0x49, 0x31}, // 83 - S
    {0x01, 0x01, 0x7f, 0x01, 0x01}, // 84 - T
    {0x3f, 0x40, 0x40, 0x40, 0x3f}, // 85 - U
    {0x1f, 0x20, 0x40, 0x20, 0x1f}, // 86 - V
    {0x3f, 0x40, 0x38, 0x40, 0x3f}, // 87 - W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 88 - X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // 89 - Y
    {0x61, 0x51, 0x49, 0x45, 0x43},  // 90 - Z
		
		{0x20, 0x54, 0x54, 0x78, 0x40}, // 97 - a
    {0x7f, 0x28, 0x44, 0x44, 0x38}, // 98 - b
    {0x38, 0x44, 0x44, 0x44, 0x28}, // 99 - c
    {0x38, 0x44, 0x44, 0x28, 0x7f}, // 100 - d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // 101 - e
    {0x00, 0x08, 0x7e, 0x09, 0x02}, // 102 - f
    {0x18, 0xa4, 0xa4, 0x9c, 0x78}, // 103 - g
    {0x7f, 0x08, 0x04, 0x04, 0x78}, // 104 - h
    {0x00, 0x44, 0x7d, 0x40, 0x00}, // 105 - i
    {0x20, 0x40, 0x40, 0x3d, 0x00}, // 106 - j
    {0x7f, 0x10, 0x28, 0x44, 0x00}, // 107 - k
    {0x00, 0x41, 0x7f, 0x40, 0x00}, // 108 - l
    {0x7c, 0x04, 0x78, 0x04, 0x78}, // 109 - m
    {0x7c, 0x08, 0x04, 0x04, 0x78}, // 110 - n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // 111 - o
    {0xfc, 0x18, 0x24, 0x24, 0x18}, // 112 - p
    {0x18, 0x24, 0x24, 0x18, 0xfc}, // 113 - q
    {0x7c, 0x08, 0x04, 0x04, 0x08}, // 114 - r
    {0x48, 0x54, 0x54, 0x54, 0x24}, // 115 - s
    {0x04, 0x04, 0x3f, 0x44, 0x24}, // 116 - t
    {0x3c, 0x40, 0x40, 0x20, 0x7c}, // 117 - u
    {0x1c, 0x20, 0x40, 0x20, 0x1c}, // 118 - v
    {0x3c, 0x40, 0x30, 0x40, 0x3c}, // 119 - w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // 120 - x
    {0x4c, 0x90, 0x90, 0x90, 0x7c}, // 121 - y
    {0x44, 0x64, 0x54, 0x4c, 0x44}  // 122 - z
};

uint8_t ScreenBuffer[504];

const uint8_t AppleShape[3][3] = {
    {0, 1, 0}, 
    {1, 0, 1}, 
    {0, 1, 0}  
};


void Nokia5110_WriteCommand(uint8_t command){
    while((SSI0->SR & 0x02) == 0){}; 
    GPIOA->DATA &= ~0x40; 
    SSI0->DR = command; 
    while((SSI0->SR & 0x10) == 0x10){};
}

void Nokia5110_WriteData(uint8_t data){
    while((SSI0->SR & 0x02) == 0){}; 
    GPIOA->DATA |= 0x40;  
    SSI0->DR = data; 
    while((SSI0->SR & 0x10) == 0x10){}; 
}

void Nokia5110_SetCursor(uint8_t newX, uint8_t newY){
    if((newX > 83) || (newY > 5)) return;
    Nokia5110_WriteCommand(0x80 | newX);
    Nokia5110_WriteCommand(0x40 | newY);
}

void Nokia5110_Init(void){
    volatile uint32_t delay;
    
    // 1. Clock Enable
    SYSCTL->RCGCSSI |= 0x01;   
    SYSCTL->RCGCGPIO |= 0x01;  
    delay = SYSCTL->RCGCGPIO;  

    // 2. GPIO Ayarlari
    GPIOA->AFSEL |= 0x2C; 
    GPIOA->PCTL = (GPIOA->PCTL & 0xFF0F00FF) + 0x00202200; 
    GPIOA->DEN |= 0x2C;   
    GPIOA->DIR |= 0xC0;   
    GPIOA->AFSEL &= ~0xC0;
    GPIOA->DEN |= 0xC0;   

    // 3. SSI Ayarlari
    SSI0->CR1 = 0;        
    SSI0->CPSR = 10;      
    SSI0->CR0 = 0x0007;   
    SSI0->CR1 |= 0x02;    

    // 4. Reset
    GPIOA->DATA &= ~0x80; 
    for(delay=0; delay<100000; delay++); 
    GPIOA->DATA |= 0x80;  

    Nokia5110_WriteCommand(0x21); 
    Nokia5110_WriteCommand(0xC0); 
    Nokia5110_WriteCommand(0x06); 
    Nokia5110_WriteCommand(0x13); 
    Nokia5110_WriteCommand(0x20); 
    Nokia5110_WriteCommand(0x0C); 
}

void Nokia5110_Clear(void){
    int i;
    Nokia5110_SetCursor(0, 0);
    for(i=0; i<504; i++) Nokia5110_WriteData(0x00);
}


void Nokia5110_ClearBuffer(void){
    int i;
    for(i=0; i<504; i++) ScreenBuffer[i] = 0x00;
}

void Nokia5110_DisplayBuffer(void){
    int i;
    Nokia5110_SetCursor(0, 0);
    for(i=0; i<504; i++){
        Nokia5110_WriteData(ScreenBuffer[i]);
    }
}

void Nokia5110_SetPixel(int x, int y){
    if(x < 0 || x >= 84 || y < 0 || y >= 48) return;
    ScreenBuffer[x + (y / 8) * 84] |= (1 << (y % 8));
}

void Nokia5110_PrintBlock(int gridX, int gridY){
    int px, py;
 
    int startX = (gridX * BLOCK_SIZE) + 1;
    int startY = (gridY * BLOCK_SIZE) + 1;

    for(px = 0; px < BLOCK_SIZE; px++){
        for(py = 0; py < BLOCK_SIZE; py++){
            if((startX + px) < 82 && (startY + py) < 46) {
                Nokia5110_SetPixel(startX + px, startY + py);
						}
					}
        }
}

void Nokia5110_DrawApple(int gridX, int gridY){
    int px, py;
    
    int startX = (gridX * BLOCK_SIZE) + 1; 
    int startY = (gridY * BLOCK_SIZE) + 1;

    for(px = 0; px < 3; px++){
        for(py = 0; py < 3; py++){
            if(AppleShape[py][px] == 1){ 
                Nokia5110_SetPixel(startX + px, startY + py);
            }
        }
    }
}

void Nokia5110_DrawBorder(void){
    int i;
    for(i=0; i<83; i++){
        Nokia5110_SetPixel(i, 0);
        Nokia5110_SetPixel(i, 46);		
    }
    
    for(i=0; i<47; i++){
        Nokia5110_SetPixel(0, i);
        Nokia5110_SetPixel(82, i);
    }
}

void Nokia5110_PrintChar(char c){
    int i;
    int index;

    if (c == 32) { 
        index = 0; 
    } 
    else if (c == 33) { 
        index = 1; // !
    } 
    else if (c >= 48 && c <= 58) { 
  
        index = c - 46; 
    } 
    else if (c >= 65 && c <= 90) { 
        index = c - 52; 
    } 
    else if (c >= 97 && c <= 122) { 
        index = c - 58; 
    } 
    else {
        index = 0; 
    }

    for(i=0; i<5; i++){
        Nokia5110_WriteData(ASCII[index][i]);
    }
    Nokia5110_WriteData(0x00);
}

void Nokia5110_PrintString(char *ptr){
    while(*ptr){
        Nokia5110_PrintChar(*ptr); 
        ptr++; 
    }
}

void Nokia5110_PrintNumber(int num){
    char buffer[10];
    int i = 0;

    if(num == 0){
        Nokia5110_PrintChar('0');
        return;
    }

    while(num > 0){
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i > 0){
        Nokia5110_PrintChar(buffer[--i]);
    }
}
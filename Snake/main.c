#include "TM4C123GH6PM.h"
#include "Nokia5110.h"
#include "Game.h"
#include "I2C.h"
#include "Accelerometer.h"
#include "ADC.h"
#include "PWM.h"
#include "Buzzer.h"
#include <stdint.h>
#include <stdbool.h>


extern uint32_t ADC_Read(void);

void PortF_Init(void){
    SYSCTL->RCGCGPIO |= 0x20; 
    while((SYSCTL->PRGPIO & 0x20) == 0){}; 
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR = 0x1F;
    GPIOF->DIR |= 0x0E;       
    GPIOF->DIR &= ~0x10;    
    GPIOF->PUR |= 0x10;    
    GPIOF->DEN |= 0x1F;       
}

bool Button_Pressed(void){
    return (GPIOF->DATA & 0x10) == 0; 
}

void Delay_ms(uint32_t ms) {
    uint32_t i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<3180; j++); 
}

void Accelerometer_SafeRead(void) {
    uint32_t timeout = 0;
    const uint32_t MAX_TIMEOUT = 50000; 

    ADXL345_RequestRead(); 

    while(data_ready == 0 && timeout < MAX_TIMEOUT){
        timeout++;
    }

    if(timeout >= MAX_TIMEOUT) {
        GPIOF->DATA |= 0x02; 
        I2C0_Init();
        ADXL345_Init();
        GPIOF->DATA &= ~0x02;
    } else {
        Process_Accelerometer_Data();
    }
}

int main(void){
    __disable_irq(); 
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
    Nokia5110_Init();
    Nokia5110_Clear();
    PortF_Init();      
    ADC_Init();        
    PWM_Init();   
    I2C0_Init();   
    ADXL345_Init(); 
		Buzzer_Init();
	
    __enable_irq();    
    
    CurrentState = MENU;
    bool ScreenUpdated = false; 
    
    while(1){
        switch(CurrentState){
            case MENU:
                PWM_Disable(); 
                GPIOF->DATA = (GPIOF->DATA & ~0x0E) | 0x04;
                
                if(!ScreenUpdated){ 
                    Menu_Draw();
                    ScreenUpdated = true; 
                }
                
                if(Button_Pressed()){
                    while(Button_Pressed());
                    Game_Init(); 
                    CurrentState = GAME; 
                    ScreenUpdated = false; 
                }
                break;
                
            case GAME:
                GPIOF->DATA &= ~0x06; 
                PWM_SetBrightness(mySnake.length); 

                uint32_t potValue = ADC_Read(); 
                float T_delay = 0.2f + (1.8f * ((float)potValue / 4095.0f));
                Accelerometer_SafeRead();

                
                if(intended_direction != DIR_NONE) {
                    int oldDX = mySnake.dirX;
                    int oldDY = mySnake.dirY;

                    if(intended_direction == DIR_UP)    Game_SetDirection(0, -1);
                    if(intended_direction == DIR_DOWN)  Game_SetDirection(0, 1);
                    if(intended_direction == DIR_LEFT)  Game_SetDirection(-1, 0);
                    if(intended_direction == DIR_RIGHT) Game_SetDirection(1, 0);

                    if(oldDX != mySnake.dirX || oldDY != mySnake.dirY) {
                        Buzzer_Play(1000, 150);
                    } else if(intended_direction != DIR_NONE) {
                        Buzzer_Play(2500, 150);
                    }
                }
                
                Game_Update();
                Game_Draw(); 

                Delay_ms((uint32_t)(T_delay * 1000));
                
                if(CurrentState == GAME_OVER) ScreenUpdated = false; 
                break;
                
            case GAME_OVER:
                PWM_Disable(); 
                GPIOF->DATA = (GPIOF->DATA & ~0x0E) | 0x02;
                Buzzer_PlayGameOver();
								CurrentState = MENU; 
								ScreenUpdated = false; 		
                break;
        }
    }
}
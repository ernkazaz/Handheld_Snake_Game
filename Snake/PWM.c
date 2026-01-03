#include "TM4C123GH6PM.h"


void PWM_Init(void){
    SYSCTL->RCGCPWM |= 0x02;   
    SYSCTL->RCGCGPIO |= 0x20; 

    while((SYSCTL->PRPWM & 0x02) == 0) {}; 
		while((SYSCTL->PRGPIO & 0x20) == 0) {};
    
    GPIOF->AFSEL |= 0x08;       
    GPIOF->PCTL &= ~0x0000F000;
    GPIOF->PCTL |= 0x00005000; 
    GPIOF->DEN |= 0x08; 
    
    SYSCTL->RCC |= 0x00100000;  
    SYSCTL->RCC &= ~0x000E0000;
    SYSCTL->RCC |= 0x00000000; 

    PWM1->_3_CTL = 0;        
    
    PWM1->_3_GENB = 0x0000080C; 
    
    PWM1->_3_LOAD = 40000 - 1;  
    
    PWM1->_3_CMPB = 0;          
    

    PWM1->_3_CTL |= 1;     
    PWM1->ENABLE |= 0x80;   
}


void PWM_SetBrightness(int length){
    PWM1->ENABLE |= 0x80; 

    unsigned long duty = length * 98; 
    if(duty > 39999) duty = 39999;
    if(length == 0) duty = 0;
    
    PWM1->_3_CMPB = 40000 - duty;
}

void PWM_Disable(void){
    PWM1->ENABLE &= ~0x80;
    PWM1->_3_CMPB = 0;
}
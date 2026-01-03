#include "TM4C123GH6PM.h"

extern unsigned long ADC_Read(void);

void ADC_Init(void){
    SYSCTL->RCGCADC |= 0x01;   
    SYSCTL->RCGCGPIO |= 0x10;  
    
    while((SYSCTL->PRGPIO & 0x10) == 0); 
    while((SYSCTL->PRADC & 0x01) == 0); 

    GPIOE->DIR &= ~0x08;       
    GPIOE->AFSEL |= 0x08;      
    GPIOE->DEN &= ~0x08;       
    GPIOE->AMSEL |= 0x08;      

    ADC0->ACTSS &= ~0x0008;    
    ADC0->EMUX &= ~0xF000;     
    ADC0->SSMUX3 = 0;          
    ADC0->SSCTL3 = 0x0006;     
    ADC0->ACTSS |= 0x0008;     
}
#include "TM4C123GH6PM.h"
#include "Buzzer.h"

#define BUZZER_PIN (1 << 6)


static volatile uint32_t tone_steps = 0;

void Buzzer_Init(void) {
    SYSCTL->RCGCGPIO |= 0x02; 
    SYSCTL->RCGCTIMER |= 0x01;
    while((SYSCTL->PRGPIO & 0x02) == 0);

    GPIOB->DIR |= BUZZER_PIN;
    GPIOB->DEN |= BUZZER_PIN;


    TIMER0->CTL &= ~0x01;     
    TIMER0->CFG = 0x00000000;
    TIMER0->TAMR = 0x00000002;
    TIMER0->IMR |= 0x01;

    NVIC->ISER[0] |= (1 << 19); // Kesmeyi aktif et

    NVIC->IPR[4] = (NVIC->IPR[4] & 0x1FFFFFFF) | (3 << 29);
}

void Buzzer_Play(uint32_t freq, uint32_t duration_ms) {
    if (freq == 0) return;

    uint32_t reload = (50000000 / (2 * freq)) - 1;
    TIMER0->TAILR = reload;

    tone_steps = (duration_ms * 2 * freq) / 1000;
    TIMER0->CTL |= 0x01; 
}


void Buzzer_PlayGameOver(void) {

    uint32_t notes[] = {494, 698, 698, 698, 659, 587, 523, 330, 196, 262};
    
    uint32_t durations[] = {120, 120, 120, 120, 120, 120, 140, 140, 140, 230};

    const uint32_t ms_wait = 2500; 

    for(int i = 0; i < 10; i++) {
        Buzzer_Play(notes[i], durations[i]);
        
        for(volatile uint32_t j = 0; j < ((durations[i] + 20) * ms_wait); j++);
    }
}

void TIMER0A_Handler(void) {
    TIMER0->ICR = 0x01;

    if (tone_steps > 0) {
        GPIOB->DATA ^= BUZZER_PIN; 
        tone_steps--;
    } else {
        TIMER0->CTL &= ~0x01;      
        GPIOB->DATA &= ~BUZZER_PIN;
    }
}
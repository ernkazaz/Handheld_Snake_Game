#include "TM4C123GH6PM.h"
#include "I2C.h"

volatile I2C_State_t I2C_State = IDLE;
uint8_t i2c_data[6];
volatile uint8_t i2c_index = 0;
volatile uint8_t data_ready = 0;

void I2C0_Init(void) {
    SYSCTL->RCGCI2C |= 0x01;
    SYSCTL->RCGCGPIO |= 0x02;
    while((SYSCTL->PRGPIO & 0x02) == 0) {};

    GPIOB->AFSEL |= 0x0C;
    GPIOB->ODR |= 0x08; 
    GPIOB->DEN |= 0x0C;
    GPIOB->PCTL = (GPIOB->PCTL & 0xFFFF00FF) | 0x00003300;
		
    I2C0->MCR = 0x10;
    I2C0->MTPR = 0x15;
    I2C0->MIMR = 0x01;

    NVIC->ISER[0] |= (1 << 8);
    __enable_irq();
}

void I2C0_Write(uint8_t slaveAddr, uint8_t reg, uint8_t data) {
    I2C0->MSA = (slaveAddr << 1);
    I2C0->MDR = reg;
    I2C0->MCS = 0x03;
    while(I2C0->MCS & 0x01);
    
    I2C0->MDR = data;
    I2C0->MCS = 0x05;
    while(I2C0->MCS & 0x01);
}

void I2C0_Handler(void) {
    I2C0->MICR = 0x01;
    if (I2C0->MCS & 0x02) {
        I2C0->MCS = 0x04;
        I2C_State = IDLE;
        return;
    }

    switch (I2C_State) {
        case POINTER:
            I2C0->MSA = (ADXL345_ADDR << 1) | 0x01;
            I2C0->MCS = 0x0B;
            i2c_index = 0;
            I2C_State = READ;
            break;
        case READ:
            i2c_data[i2c_index++] = I2C0->MDR;
            I2C0->MCS = (i2c_index < 5) ? 0x09 : 0x05;
            if (i2c_index == 5) I2C_State = LAST_BYTE;
            break;
        case LAST_BYTE:
            i2c_data[i2c_index] = I2C0->MDR;
            I2C_State = IDLE;
            data_ready = 1; // Signal main loop
            break;
        default: I2C_State = IDLE; break;
    }
}
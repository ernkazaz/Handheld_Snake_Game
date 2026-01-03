#ifndef I2C_H
#define I2C_H

#include <stdint.h>

// ADXL345 I2C Address (ALT ADDRESS pin grounded = 0x53)
#define ADXL345_ADDR 0x53

typedef enum {
    IDLE,
    POINTER,
    READ,
    LAST_BYTE
} I2C_State_t;

// Shared variables (accessible by other modules)
extern volatile I2C_State_t I2C_State;
extern uint8_t i2c_data[6];
extern volatile uint8_t data_ready;

// Function Prototypes
void I2C0_Init(void);
void I2C0_Write(uint8_t slaveAddr, uint8_t reg, uint8_t data);
void I2C0_Handler(void);

#endif
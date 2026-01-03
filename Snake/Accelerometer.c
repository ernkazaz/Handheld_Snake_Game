#include "TM4C123GH6PM.h"
#include "Accelerometer.h"
#include "I2C.h"

int16_t x_raw = 0, y_raw = 0;
uint8_t intended_direction = DIR_NONE;

void ADXL345_Init(void) {
    I2C0_Write(ADXL345_ADDR, 0x31, 0x01); // +-4g
    I2C0_Write(ADXL345_ADDR, 0x2D, 0x08); // Measure mode
}

void ADXL345_RequestRead(void) {
    I2C0->MSA = (ADXL345_ADDR << 1);
    I2C0->MDR = 0x32; // DATAX0 register
    I2C_State = POINTER;
    I2C0->MCS = 0x03;
}

void Process_Accelerometer_Data(void) {
    if (!data_ready) return;
    data_ready = 0;

    // Convert raw bytes from I2C driver to signed integers
    x_raw = (int16_t)((i2c_data[1] << 8) | i2c_data[0]);
    y_raw = (int16_t)((i2c_data[3] << 8) | i2c_data[2]);

    int16_t absX = (x_raw < 0) ? -x_raw : x_raw;
    int16_t absY = (y_raw < 0) ? -y_raw : y_raw;

    if (absX < TILT_THRESHOLD && absY < TILT_THRESHOLD) {
        intended_direction = DIR_NONE;
    } else if (absY > TILT_THRESHOLD && absY > absX) {
        intended_direction = (y_raw < 0) ? DIR_UP : DIR_DOWN;
    } else if (absX > TILT_THRESHOLD && absX >= absY) {
        intended_direction = (x_raw > 0) ? DIR_LEFT : DIR_RIGHT;
    }
}
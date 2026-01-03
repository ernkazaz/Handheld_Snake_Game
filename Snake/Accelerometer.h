#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>

// Threshold for tilt detection (Adjust based on sensitivity)
#define TILT_THRESHOLD 50 

// Direction Constants
#define DIR_NONE  0
#define DIR_UP    1
#define DIR_DOWN  2
#define DIR_LEFT  3
#define DIR_RIGHT 4

// Shared variables
extern int16_t x_raw, y_raw;
extern uint8_t intended_direction;

// Function Prototypes
void ADXL345_Init(void);
void ADXL345_RequestRead(void);
void Process_Accelerometer_Data(void);

#endif
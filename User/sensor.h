#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

void Sensor_Init(void);
void Sensor_LedOn(void);
void Sensor_LedOff(void);
int  Sensor_ReadValue(void);
uint16_t Sensor_ReadAnalog(void);
extern uint8_t last_proximity_state_detected;

#endif // SENSOR_H

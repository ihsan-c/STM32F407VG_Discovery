/*
 * bmp180.h
 *
 *  Created on: Aug 9, 2024
 *      Author: ihsan
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include "stm32f4xx_hal.h"

void bmp180_init(void);
void bmp180_calibrate(void);
void bmp180_get_calibration_value(void);
void bmp180_get_uncompensated_temperature(void);
void bmp180_get_temperature(void);
void bmp180_get_uncompensated_pressure(void);
void bmp180_get_pressure(void);



#endif /* INC_BMP180_H_ */

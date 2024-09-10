/*
 * Nokia5110.h
 *
 *  Created on: Aug 24, 2024
 *      Author: ihsan
 */

#ifndef INC_NOKIA5110_H_
#define INC_NOKIA5110_H_

#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_8
#define RST_GPIO_Port GPIOD
#define CE_Pin GPIO_PIN_9
#define CE_GPIO_Port GPIOD
#define DC_Pin GPIO_PIN_10
#define DC_GPIO_Port GPIOD

#include "stm32f4xx_hal.h"

#include <stdbool.h>

extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;


bool nokia5110_Init(void);
void nokia5110_Reset(void);
bool nokia5110_Update(void);
void nokia5110_BufferWrite(uint8_t* data,uint16_t lenght);
void nokia5110_Clear(void);
bool nokia5110_Write(uint8_t data,uint8_t mode);
void nokia5110_SetPixel(uint8_t x,uint8_t y,bool set);

#endif /* INC_NOKIA5110_H_ */

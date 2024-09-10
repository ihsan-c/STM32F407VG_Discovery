/*
 * Nokia5110.c
 *
 *  Created on: Aug 24, 2024
 *      Author: ihsan
 */

#include "Nokia5110.h"

uint8_t frameBuff[504]; // Screen has 504 index

bool nokia5110_Init(void)
{
	nokia5110_Reset();

	if(!nokia5110_Write(0x21, 0))
		return false;
	if(!nokia5110_Write(0xC0, 0))
		return false;
	if(!nokia5110_Write(0x07, 0))
		return false;
	if(!nokia5110_Write(0x13, 0))
		return false;
	if(!nokia5110_Write(0x20, 0))
		return false;
	if(!nokia5110_Write(0x0C, 0))
		return false;

	return true;
}

void nokia5110_Reset(void)
{
	HAL_GPIO_WritePin(GPIOD, RST_Pin, GPIO_PIN_RESET);	// RESET pin is LOW
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, RST_Pin, GPIO_PIN_SET);	// RESET pin is HIGH
}

bool nokia5110_Update(void)
{
	if(!nokia5110_Write(0x80, 0))	// Set the X axis cursor to 0
		return false;
	if(!nokia5110_Write(0x40, 0))	// Set the Y axis cursor to 0
		return false;

	nokia5110_BufferWrite(frameBuff, 504);
	return true;
}

void nokia5110_BufferWrite(uint8_t* data,uint16_t length)
{
	HAL_GPIO_WritePin(GPIOD,CE_Pin, GPIO_PIN_RESET);	//CE pin is low
	HAL_GPIO_WritePin(GPIOD,DC_Pin, GPIO_PIN_SET);		//DC pin is HIGH to send command
	HAL_SPI_Transmit_DMA(&hspi2, data, length);
}

void nokia5110_Clear(void)
{
	for(uint16_t i =0;i<504;i++)
	frameBuff[i]=0X00;
}
bool nokia5110_Write(uint8_t data,uint8_t mode)
{
	HAL_GPIO_WritePin(GPIOD,CE_Pin, GPIO_PIN_RESET);	//CE pin is low

	if(mode==0)
		HAL_GPIO_WritePin(GPIOD, DC_Pin, GPIO_PIN_RESET);	//DC pin is LOW to send data
	else if(mode==1)
		HAL_GPIO_WritePin(GPIOD,DC_Pin, GPIO_PIN_SET);		//DC pin is HIGH to send command
	else
	{
		HAL_GPIO_WritePin(GPIOD, CE_Pin, GPIO_PIN_SET);		//CE pin is HIGH
		return true;
	}

	HAL_SPI_Transmit_DMA(&hspi2, &data, 1);

	return true;
}

void nokia5110_SetPixel(uint8_t x,uint8_t y,bool set)
{
	uint8_t Bi;
	uint16_t By;

	if(x<0 || x>83 || y<0 || y>83 )
		return;

	By = (y/8) * 84 +x;
	Bi = y % 8;

	if(set)
	{
		frameBuff[By] |= (1 << Bi);
	}
	else
	{
		frameBuff[By] &= (1 << Bi);
	}

}

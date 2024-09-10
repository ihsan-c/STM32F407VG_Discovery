/*
 * bmp180.c
 *
 *  Created on: Aug 17, 2024
 *      Author: ihsan
 */

#include "bmp180.h"


#define BMP180_READ_REGISTER_ADDRESS 0XEF
#define BMP180_WRITE_REGISTER_ADRESS 0XEE
#define BMP180_CALIBRATION_COEFFICENT_LENGHT 22
#define BMP180_CALIBRATION_START_ADDRESS 0XAA


extern I2C_HandleTypeDef hi2c1;

/*MBP180 EEPROM calibration values*/
int16_t AC1,AC2,AC3,B1,B2,MB,MC,MD;
uint16_t AC4,AC5,AC6;

/*Temperature values*/
int16_t uncompTemp;
int32_t temp;
int32_t tX1,tX2,tB5;

/*Pressure Values*/
int16_t uncompPressure;
int32_t pressure,pressureATM;
int32_t pX1,pX2,pX3,pB2,pB3,pB5,pB6;
uint32_t pB4,pB7;

void bmp180_init(void)
{
	if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_WRITE_REGISTER_ADRESS, 1, 100000)!=HAL_OK)
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);

	bmp180_get_calibration_value();
}


void bmp180_calibrate(void)
{

}
void bmp180_get_calibration_value(void)
{
	uint8_t buffer[BMP180_CALIBRATION_COEFFICENT_LENGHT]={0};

	HAL_I2C_Mem_Read(&hi2c1, (uint16_t)BMP180_READ_REGISTER_ADDRESS, (uint16_t)BMP180_CALIBRATION_START_ADDRESS, 1, buffer, (uint16_t)BMP180_CALIBRATION_COEFFICENT_LENGHT, 100000);
	int i=0;
	AC1= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	AC2= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	AC3= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	AC4= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	AC5= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	AC6= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	B1= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	B2= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	MB= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	MC= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
	MD= (int16_t)((buffer[i]<<8) | buffer[i+1]);i=+2;
}

void bmp180_get_uncompensated_temperature(void)
{
	uint8_t wData[1]={0};
	uint8_t rData[2]={0};
	wData[0]=0X2E;
	HAL_I2C_Mem_Write(&hi2c1, BMP180_WRITE_REGISTER_ADRESS, 0XF4, 1, wData, 1, 100000);
	HAL_Delay(5);
	HAL_I2C_Mem_Read(&hi2c1, BMP180_READ_REGISTER_ADDRESS, 0XF6, 1, rData, 2, 100000);
	uncompTemp=(int16_t)((rData[0]<<8) | rData[1]);
}
void bmp180_get_temperature(void)
{
	bmp180_get_uncompensated_temperature();
	tX1=((int32_t)uncompTemp -(int32_t)AC6)*(int32_t)AC5/(int32_t)32768;
	tX2=((int32_t)MC*2048)/(tX1+(int32_t)MD);
	tB5=tX1+tX2;
	temp=(tB5+8)/16;
}

void bmp180_get_uncompensated_pressure(void)
{
	uint8_t wData[1]={0};
	uint8_t rData[3]={0};
	wData[0]=0x34 | (0x03<<6);
	HAL_I2C_Mem_Write(&hi2c1, BMP180_WRITE_REGISTER_ADRESS, 0XF4, 1, wData, 1, 100000);
	HAL_Delay(5);
	HAL_I2C_Mem_Read(&hi2c1, BMP180_READ_REGISTER_ADDRESS, 0XF6, 1, rData, 3, 100000);
	uncompPressure=(rData[0]<<16 | rData[1]<<8 | rData[2])>>(8-(uint8_t)0x03);
}
void bmp180_get_pressure(void)
{
	bmp180_get_uncompensated_pressure();

	pB6 = tB5 - 4000;
	pX1 = (B2*(pB6*pB6/4096))/2048;
	pX2 = AC2 * pB6/ 2048;
	pX3 = pX1 +pX2;
	pB3 = (((AC1*4+pX3) << (uint8_t)0x03) +2)/4;
	pX1 = AC3 *pB6 /8192;
	pX2 = (B1 * (pB6 *pB6 / 4096)) /65536;
	pX3 = ((pX1+pX2)+2)/4;
	pB4 = AC3 * (unsigned long)(pX3 + 32768) / 32768;
	pB7 = ((unsigned long)uncompPressure- pB3) * (50000 >> (uint8_t)0x03);

	if(pB7 < 0x80000000)
		pressure = (pB7 * 2) / pB4;
	else
		pressure = (pB7 / pB4) * 2;

	pX1 = (pressure / 256) * (pressure / 256);
	pX1 = (pX1 * 3038) / 65536;
	pX2 = (-7357 * pressure) / 65536;
	pressure = pressure + (pX1 + pX2 + 3791) /16; //hPa

}


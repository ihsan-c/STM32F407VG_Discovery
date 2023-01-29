
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t value_adc;
void RCC_Config()
{
	    RCC->CR = 0x00030000;  //HSE ON HSEONRDY ENABLE
		while(!(RCC->CR & (1<<17))); //wait hse active
		RCC->CR = 0x00080000;//css enable
		RCC->PLLCFGR = 0x00000000; //PLL CONFÝG reset
		RCC->PLLCFGR |= (1<<22);//PLLscr=1 PLL source HSE
		RCC->PLLCFGR |= (4<<0);//PLLM=4
		RCC->PLLCFGR |= (168<<6);//PLLN=168
		RCC->PLLCFGR |= (0<<16);//PLLP0=0
		RCC->PLLCFGR |= (0<<17);//PLLP1=0
		RCC->CFGR |= 0X00000000;//AHB prescaler=1 ahb 1'e bölünür
		RCC->CFGR |= 0x00001400;//APB1 prescaler=4
		RCC->CFGR |= 0x00080000;//APB2 prescaler=2
		RCC->CIR |= 0x00800800;//HSE FLAG CLEAR CSS ENABLE FLAG CLEAR

		RCC->AHB1ENR |= 0x00000009;// GPIOA VE GPIOD ENABLE
}

void GPIO_Config()
{

	RCC->AHB1ENR |= 0x00000001;//GPIOA Clock enable
	GPIOA->MODER |= 0x00000003;//Analog mod on
	GPIOA->OSPEEDR |=0x00000003;//high speed 100mhz

}
void ADC_Config()
{
	RCC->APB2ENR |= 0x00000100;//ADC1 enable
	ADC1->CR1 |= 0x02000000;//resolution 8 bit
	ADC1->CR2 |= 0x00000001;	// ADC enable
	ADC1->SMPR2 |=0x00000003;//56 cycle da bir örnekleme
	ADC->CCR |= 0x00100000;//div4
}

uint8_t Read_ADC()
{
	uint8_t value ;

	ADC1->CR2 |=0x40000000;
	while(!(ADC1->SR & 0x00000002));

	value = ADC1->DR;
	 return value;
}

int main(void)
{
  RCC_Config();
  GPIO_Config();
  ADC_Config();
  while (1)
  {
	value_adc =Read_ADC();
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}

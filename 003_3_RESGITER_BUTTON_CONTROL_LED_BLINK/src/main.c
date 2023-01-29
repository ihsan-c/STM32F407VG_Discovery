#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_Config(void)
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

	GPIOD->MODER=0x55000000;// 12,13,14,15.pinler digital output
	GPIOD->OTYPER=0x00000000;//PINS PUSH PULL
	GPIOD->OSPEEDR=0xFF000000;//100 MHz colck hýzý
	GPIOD->PUPDR=0x00000000;//12,13,14,15 no pull

}

void delay(uint32_t time){
	while(time--);
}
int count =0;

int main(void)
{
	GPIO_Config();
  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)
	  {
		  while(GPIOA->IDR & 0x00000001)
			  delay(1680000);

		  count++ ;
	  }
	  if(count%2 ==0){
		  GPIOD->ODR = 0x0000000;
	  }
	  else{
		  GPIOD->ODR = 0x000F000;
	  }

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

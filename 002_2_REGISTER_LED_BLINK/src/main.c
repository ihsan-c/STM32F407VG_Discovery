#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;

uint32_t systemClock;

void RCC_Config(void)
{
	RCC->CR &= ~(1<<0);  //Tek bit sýfýrlama HSI off
	RCC->CR |=(1<<16);  //Tek bit birleme HSE on
	while(!(RCC->CR & (1<<17))); //wait hse active
	RCC->CR |= (1<<19);
	RCC->PLLCFGR = 0x00000000; //PLL CONFÝG reset
	RCC->PLLCFGR |= (1<<22);//PLLscr=1 PLL source HSE
	RCC->PLLCFGR |= (4<<0);//PLLM=4
	RCC->PLLCFGR |= (168<<6);//PLLN=168
	RCC->PLLCFGR |= (0<<16);//PLLP0=0
	RCC->PLLCFGR |= (0<<17);//PLLP1=0

	RCC->CR |= (1<<24);//pll on
	while(!(RCC->CR & (1<<25))); //wait pll active

	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);
	while(!(RCC->CFGR & (1<<1)));//select system clock as PLL clock
}

void GPIO_Config()
{
	RCC->AHB1ENR |= (1<<3);

	GPIOD->MODER |= 0x55000000;
	GPIOD->OTYPER |= 0x00000000;
	GPIOD->OSPEEDR |= 0xFF000000;
	GPIOD->PUPDR |= 0x00000000; //NO PULL-UP PULL DOWN,default position
}

int main(void)
{
 RCC_Config();

 SystemCoreClockUpdate();

 GPIO_Config();
 while (1)
  {
	 GPIOD->ODR |= 1<<12; // 12.Led set
	 GPIOD->ODR |= 1<<13; // 13.Led set
	 GPIOD->ODR |= 1<<14; // 14.Led set
	 GPIOD->ODR |= 1<<15; // 15.Led set
	 for(int i=0;i<1680000;i++);
	     GPIOD->ODR &= ~(1<<12); // 12.Led reset
		 GPIOD->ODR &= ~(1<<13); // 13.Led reset
		 GPIOD->ODR &= ~(1<<14); // 14.Led reset
		 GPIOD->ODR &= ~(1<<15); // 15.Led reset
		 for(int i=0;i<1680000;i++);

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

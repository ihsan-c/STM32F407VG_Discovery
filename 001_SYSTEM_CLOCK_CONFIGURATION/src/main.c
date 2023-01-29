#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;

uint32_t systemClock;

void RCC_Config(void)
{
	RCC->CR &= ~(1<<0);  //Tek bit sýfýrlama HSI off
	RCC->CR |=(1<<16);  //Tek bit birleme HSE on
	while(!(RCC->CR & (1<<17))); //wait hse active
	RCC->CR |= (1<<19);//css enable
	RCC->PLLCFGR = 0x00000000; //PLL CONFÝG reset
	RCC->PLLCFGR |= (1<<22);//PLLscr=1 PLL source HSE
	RCC->PLLCFGR |= (4<<0);//PLLM=4
	RCC->PLLCFGR |= (168<<6);//PLLN=168
	RCC->PLLCFGR |= (0<<16);//PLLP0=0
	RCC->PLLCFGR |= (0<<17);//PLLP1=0

	RCC->CFGR |= 0X00000000;//AHB prescaler=1 ahb 1'e bölünür


	RCC->CR |= (1<<24);//pll on
	while(!(RCC->CR & (1<<25))); //wait pll active

	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);
	while(!(RCC->CFGR & (1<<1)));//select system clock as PLL clock
}


int main(void)
{
 RCC_Config();

 SystemCoreClockUpdate();

 systemClock = SystemCoreClock;
 while (1)
  {

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

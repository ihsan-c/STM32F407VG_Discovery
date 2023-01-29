#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i =0;

void CLK_Config()
{
	        RCC->CR = 0x00010000;  //HSE ON
			while(!(RCC->CR & (1<<17))); //wait hse active
			RCC->CR = 0x00080000;//css enable
			RCC->PLLCFGR = 0x00000000; //PLL CONFIG reset
			RCC->PLLCFGR |= (1<<22);//PLLscr=1 PLL source HSE
			RCC->PLLCFGR |= (4<<0);//PLLM=4
			RCC->PLLCFGR |= (168<<6);//PLLN=168
			RCC->PLLCFGR |= (0<<16);//PLLP0=0
			RCC->PLLCFGR |= (0<<17);//PLLP1=0
			RCC->CFGR |= 0X00000000;//AHB prescaler=1 ahb divided by 1
			RCC->CFGR |= 0x00001400;//APB1 prescaler=4
			RCC->CFGR |= 0x00080000;//APB2 prescaler=2
			RCC->CIR |= 0x00800800;//HSE FLAG CLEAR CSS ENABLE FLAG CLEAR
}

void delay(uint32_t time)
{
	while(time--);
}
void DAC1_Config()
{
	RCC->AHB1ENR |= 0x00000001;//AHB1 Enabled
	RCC->APB1ENR |= 0x20000000;//APB1 line Enabled

	DAC->CR |= 0x00000001;// DAC cahnnel 1 Enabled
	DAC->SWTRIGR |= 0x00000000;//Sowftware trigger register disabled
	DAC->DHR12R1 |= 0x00000000;//DAC channel1 12-bit right-aligned data holding register


}

int main(void)
{
  CLK_Config();
  DAC1_Config();
  while (1)
  {
	for(;i<4096;i++)
	{
		DAC->DHR12R1 = i;
		delay(16800);
	}
	i=0;
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}

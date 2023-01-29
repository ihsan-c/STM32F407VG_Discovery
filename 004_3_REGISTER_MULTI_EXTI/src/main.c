#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void CLK_Config()
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
}

void GPIO_Config()
{
	RCC->AHB1ENR=0x00000009;//gpioa and gpiod active
	GPIOD->MODER=0x55000000;//12-15 pins general purpose out put
	GPIOD->OTYPER=0x00000000;//out put push-pull
	GPIOD->PUPDR=0x00000000;//no pull down or pull up
	GPIOD->OSPEEDR=0xFF000000;


}

void EXTI_Config()
{
	RCC->APB2ENR=0x00004000;//SYSCFG biti enable

	SYSCFG->EXTICR[0]=0x00000000;//EXTI0 line'ý 0,1,2 ve 3.pinleri PA PORTU icin aktiflerstirildi
	//4,5,6,7.pinler kullanýlmak istense idi EXTICR[1] kullanilirdi 8-12 icin 2 ve 13-15 icin 3
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	NVIC_SetPriority(EXTI0_IRQn,0);
	NVIC_SetPriority(EXTI1_IRQn,1);
	NVIC_SetPriority(EXTI2_IRQn,2);

	EXTI->IMR=0x00000007;//0 1 2 bitleri intterupt icin kullanilicak
	EXTI->RTSR=0x00000007;//yukselen kenarda aktiflesicek


}

void delay(uint32_t time)
{
	while(time--);
}
void EXTI0_IRQHandler()
{
	if(EXTI->PR & 1<<0)//0.bit 1'lendi mi ?
	{
		for(int i=0;i<5;i++)
		{
			GPIOD->ODR=0x00001000;
			delay(1680000);
			GPIOD->ODR=0x00000000;
			delay(1680000);
		}

	}
	EXTI->PR =0x00000001;
}
void EXTI1_IRQHandler()
{
	if(EXTI->PR & 1<<1)
	{
		for(int i=0;i<5;i++)
	   {
		GPIOD->ODR=0x00002000;
		delay(1680000);
		GPIOD->ODR=0x00000000;
		delay(1680000);
		}

	}
	EXTI->PR =0x00000002;
}
void EXTI2_IRQHandler()
{
	if(EXTI->PR & 1<<2)
	{
		for(int i=0;i<5;i++)
	  {
		GPIOD->ODR=0x00004000;
		delay(1680000);
		GPIOD->ODR=0x00000000;
		delay(1680000);
	  }
	}
	EXTI->PR =0x00000004;
}

int main(void)
{
CLK_Config();
GPIO_Config();
EXTI_Config();
  while (1)
  {
	  	  GPIOD->ODR=0x0000F000;
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

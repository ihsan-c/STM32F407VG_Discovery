#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct ;
EXTI_InitTypeDef EXTI_InitStruct ;
NVIC_InitTypeDef NVIC_InitStruct;

void delay (uint32_t time)
{
	while(time--);
}

void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		delay(3680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		delay(3680000);
	    GPIO_SetBits(GPIOD,GPIO_Pin_14);
		delay(3680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
		delay(3680000);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
void EXTI2_IRQHandler()
{
		if(EXTI_GetITStatus(EXTI_Line2) != RESET)
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
		    delay(3680000);
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			delay(3680000);
			GPIO_SetBits(GPIOD,GPIO_Pin_13);
	     	delay(3680000);
			GPIO_SetBits(GPIOD,GPIO_Pin_12);
	    	delay(3680000);
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
}

void GPIO_Config()
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);
SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);

GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

GPIO_Init(GPIOD,&GPIO_InitStruct);

GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

GPIO_Init(GPIOA,&GPIO_InitStruct);

}

void EXTI_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	EXTI_InitStruct.EXTI_Line =EXTI_Line1|EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt ;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;//A Portunun 1.pininin EXTI oldugunu belirttim
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//Oncelige sahip olan pinin priorty degeri kucuk girilir
	//su an 1.pinin ayarlarýný yaptýgým icin 0 vererek 1.pini öncelikli yaptim
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;

	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//0'DAN BÜYÜK 15'E KADAR DEGER VERILEBILINIR
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;//ON hazirlikta önem sirasi belirlendigi icin önemli bir fonk degil

	NVIC_Init(&NVIC_InitStruct);
}


int main(void)
{

	GPIO_Config();
	EXTI_Config();
  while (1)
  {
	GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
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

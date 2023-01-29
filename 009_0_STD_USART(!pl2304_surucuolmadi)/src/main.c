#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;

char str[50];

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

    GPIO_PinAFConfig(GAPIOA,PinSource2,GPIO_AF_USART2);

    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

    GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void USART_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	USART_InitStruct.USART_BaudRate=9600;//veri gonderme hizi,kac saniyede bir veri gondersin
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//RTS VE CTS alicinin ve vericinin birbirini uyarmasini saglar
	USART_InitStruct.USART_Mode=USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;//sonlandirma biti oncesi paritiy biti yollayarak aliciya on haber verir.
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//1 gittiginde durmus olucak
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART2,&USART_InitStruct);

	USART_Cmd(USART2,ENABLE);

}

void delay(uint32_t time)
{
	while(time--);
}

void USART_Put(USART_TypeDef* USARTx,volatile char *s)
{
	while(*s)
	{
		while(!USART->SR = 0x00000040)
		{
			USART_SendData(USARTx,*s)
			*s++;
		}
	}
}

int main(void)
{
  USART_Config();
  GPIO_Config();
  while (1)
  {
	sprintf(str,"Hi World\n");
	USART_Put(USART2,str);
	delay(1680000);
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

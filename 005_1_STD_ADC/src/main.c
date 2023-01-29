#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value=0;
float adc_voltage=0;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd= GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void ADC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;//Tek bir adc'yi baska adclere baglamadan yapicagimiz icin bunu sectik
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;//adc'nin hýzýnýn 36MHZ'den kucuk olmasý gerekmektedir(datasheet sayfa 133)
	//APB2 hattýnýn hýzý ise 84MHz.ADC'ye uygun olmasý icin 84MHz'yi 4'e boluyoruz.

	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;//Ornekleme arttikca daha hassas olcum yapar
	// ancak ayný zamanda cevresel gurultulerden daha fazla etkilenir
	ADC_Init(ADC1,&ADC_InitStruct);

	ADC_Cmd(ADC1,ENABLE);//ADC cevre birimlerini akrif-pasiflestirir.
}

uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);//adc kanalý,GPIOA 0.porttan
	//okuuma yaptigimiz icin channel_0, 1 sabit , 56 altý cevrimde bir okuma yapicak

	ADC_SoftwareStartConv(ADC1);//ADC1 kanalinin yazilimsal olarak baslatir

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC1);
}
int main(void)
{
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = Read_ADC();
	  adc_voltage=0.000805*adc_value;
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

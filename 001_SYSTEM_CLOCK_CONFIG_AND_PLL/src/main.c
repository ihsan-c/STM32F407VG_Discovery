#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int main(void)
{
  int i = 0;


  while (1)
  {
	i++;
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
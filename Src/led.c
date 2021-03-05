/*led驱动*/
#include "led.h"

void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state)
{
  /*判断参量合法性*/
  assert_param(IS_LED_TYPEDEF(LEDx));
  assert_param(IS_LED_STATE(state));
  
	/*执行操作*/
  if(state==LED_OFF)
  {
    if(LEDx & LED0)            
      LED0_OFF;
     
    if(LEDx & LED1)
      LED1_OFF;
  }
  else if(state==LED_ON)
  {
    if(LEDx & LED0)
      LED0_ON;
     
    if(LEDx & LED1)
      LED1_ON;
  }
  else
  {
    if(LEDx & LED0)
      LED0_TOGGLE;
     
    if(LEDx & LED1)
      LED1_TOGGLE;
  }
}

void LED0_Hit()
{
  LED0_ON;
	HAL_Delay(200);
  LED0_OFF;
	HAL_Delay(200);
}

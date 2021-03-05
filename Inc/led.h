#ifndef __LED_H
#define __LED_H
#include "stm32f1xx_hal.h"

/*类型定义*/
typedef enum
	{
		LED_OFF = 0,
		LED_ON  = 1,
		LED_TOGGLE = 2,
	}LEDState_TypeDef;

/*宏定义*/	
#define IS_LED_STATE(STATE)           (((STATE) == LED_OFF) || ((STATE) == LED_ON) || ((STATE) == LED_TOGGLE))
	
#define LED0                          (uint8_t)0x01
#define LED1                          (uint8_t)0x02
#define IS_LED_TYPEDEF(LED)           (((LED) == LED1) || ((LED) == LED2))

#define LED0_GPIO                     GPIOA
#define LED0_GPIO_PIN                 GPIO_PIN_8

#define LED1_GPIO                     GPIOD
#define LED1_GPIO_PIN                 GPIO_PIN_2

#define LED0_ON                       HAL_GPIO_WritePin(LED0_GPIO,LED0_GPIO_PIN,GPIO_PIN_RESET)    //输出低电平
#define LED0_OFF                      HAL_GPIO_WritePin(LED0_GPIO,LED0_GPIO_PIN,GPIO_PIN_SET)  		 //输出高电平
#define LED0_TOGGLE                   HAL_GPIO_TogglePin(LED0_GPIO,LED0_GPIO_PIN)                  //输出反转
 
#define LED1_ON                       HAL_GPIO_WritePin(LED1_GPIO,LED1_GPIO_PIN,GPIO_PIN_RESET)    //输出低电平
#define LED1_OFF                      HAL_GPIO_WritePin(LED1_GPIO,LED1_GPIO_PIN,GPIO_PIN_SET)      //输出高电平
#define LED1_TOGGLE                   HAL_GPIO_TogglePin(LED1_GPIO,LED1_GPIO_PIN)                  //输出反转

/*函数声明*/		
void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state);
void LED0_Hit(void);

#endif

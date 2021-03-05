#ifndef __KEY_H_
#define __KEY_H_
#include "stm32f1xx_hal.h"

/*类型定义*/
typedef enum
{
	KEY_UP = 0,
	KEY_DOWN = 1,
}KEYState_TypeDef;

/*宏定义*/

//开发板上的按键
#define KEY0_GPIO                     GPIOC
#define KEY0_GPIO_PIN                 GPIO_PIN_1
#define KEY0_DOWN_LEVEL               0

#define KEY1_GPIO                     GPIOC
#define KEY1_GPIO_PIN                 GPIO_PIN_13
#define KEY1_DOWN_LEVEL               0

//用户按键
#define KEY_UP_GPIO                   GPIOA
#define KEY_UP_GPIO_PIN               GPIO_PIN_10
#define KEY_UP_DOWN_LEVEL             0

#define KEY_DOWN_GPIO                 GPIOC
#define KEY_DOWN_GPIO_PIN             GPIO_PIN_8
#define KEY_DOWN_DOWN_LEVEL           0

#define KEY_RIGHT_GPIO                GPIOA
#define KEY_RIGHT_GPIO_PIN            GPIO_PIN_9
#define KEY_RIGHT_DOWN_LEVEL          0

#define KEY_LEFT_GPIO                 GPIOC
#define KEY_LEFT_GPIO_PIN             GPIO_PIN_7
#define KEY_LEFT_DOWN_LEVEL           0

#define KEY_OK_GPIO                   GPIOC
#define KEY_OK_GPIO_PIN               GPIO_PIN_9
#define KEY_OK_DOWN_LEVEL             0

/*函数定义*/

//开发板上的按键
KEYState_TypeDef KEY0_StateRead(void);
KEYState_TypeDef KEY1_StateRead(void);

//用户按键
KEYState_TypeDef KEY_UP_StateRead(void);
KEYState_TypeDef KEY_DOWN_StateRead(void);
KEYState_TypeDef KEY_RIGHT_StateRead(void);
KEYState_TypeDef KEY_LEFT_StateRead(void);
KEYState_TypeDef KEY_OK_StateRead(void);

#endif

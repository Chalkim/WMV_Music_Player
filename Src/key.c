/*按键驱动程序*/

#include "key.h"

//扫描式按键输入

//开发板上的按键
KEYState_TypeDef KEY0_StateRead(void)
{
  if (HAL_GPIO_ReadPin(KEY0_GPIO,KEY0_GPIO_PIN) == KEY0_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY0_GPIO,KEY0_GPIO_PIN) == KEY0_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY0_GPIO,KEY0_GPIO_PIN) == KEY0_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

KEYState_TypeDef KEY1_StateRead(void)
{
  if (HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_GPIO_PIN) == KEY1_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_GPIO_PIN) == KEY1_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_GPIO_PIN) == KEY1_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

//用户按键
KEYState_TypeDef KEY_UP_StateRead(void)
{
  if (HAL_GPIO_ReadPin(KEY_UP_GPIO,KEY_UP_GPIO_PIN) == KEY_UP_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY_UP_GPIO,KEY_UP_GPIO_PIN) == KEY_UP_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY_UP_GPIO,KEY_UP_GPIO_PIN) == KEY_UP_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

KEYState_TypeDef KEY_DOWN_StateRead(void)
{
  if (HAL_GPIO_ReadPin(KEY_DOWN_GPIO,KEY_DOWN_GPIO_PIN) == KEY_DOWN_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY_DOWN_GPIO,KEY_DOWN_GPIO_PIN) == KEY_DOWN_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY_DOWN_GPIO,KEY_DOWN_GPIO_PIN) == KEY_DOWN_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

KEYState_TypeDef KEY_RIGHT_StateRead(void)
{
  if (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO,KEY_RIGHT_GPIO_PIN) == KEY_RIGHT_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO,KEY_RIGHT_GPIO_PIN) == KEY_RIGHT_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO,KEY_RIGHT_GPIO_PIN) == KEY_RIGHT_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

KEYState_TypeDef KEY_LEFT_StateRead(void)
{
	if (HAL_GPIO_ReadPin(KEY_LEFT_GPIO,KEY_LEFT_GPIO_PIN) == KEY_LEFT_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY_LEFT_GPIO,KEY_LEFT_GPIO_PIN) == KEY_LEFT_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY_LEFT_GPIO,KEY_LEFT_GPIO_PIN) == KEY_LEFT_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

KEYState_TypeDef KEY_OK_StateRead(void)
{
  if (HAL_GPIO_ReadPin(KEY_OK_GPIO,KEY_OK_GPIO_PIN) == KEY_OK_DOWN_LEVEL) {
		HAL_Delay(10);
		if (HAL_GPIO_ReadPin(KEY_OK_GPIO,KEY_OK_GPIO_PIN) == KEY_OK_DOWN_LEVEL) {
			while (HAL_GPIO_ReadPin(KEY_OK_GPIO,KEY_OK_GPIO_PIN) == KEY_OK_DOWN_LEVEL);
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

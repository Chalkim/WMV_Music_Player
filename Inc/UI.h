#ifndef __UI_H_
#define __UI_H_

#include "sign.h"


extern u8 TOP;
void UI_Init(void);
void UI_Info(u8 * str,u16 COLOR);
void UI_Select(u8 index);

#endif

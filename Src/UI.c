#include "UI.h"
#include "GUI.h"
#include "lcd.h"
#include "file.h"
extern char names[6][13];               /* 文件名 */
extern u8 old_index;
//画笔颜色,背景颜色
u16 POINT_COLOR = WHITE,BACK_COLOR = BLACK;

void UI_Init(void)
{
	LCD_Init();              //LCD初始化
	LCD_Clear(BACK_COLOR);         //LCD清屏
	u8 i;
  LCD_DrawRectangle(0,0,127,127);
	LCD_DrawRectangle(1,1,126,126); //外面粗框
	LCD_DrawRectangle(3,3,124,124); //外面细框
	TOP = 1;
	for(i=0;i<=5;i++)
	{
		LCD_DrawRectangle(5,5 + i*18,122,21 + i*18);
	  Show_Str(7,5 + i*18,POINT_COLOR,BACK_COLOR,names[i],16,1);
	}
  POINT_COLOR = WHITE;
	LCD_DrawFillRectangle(5,5,122,21);
	POINT_COLOR = BLACK;
	Show_Str(7,5,POINT_COLOR,BACK_COLOR,names[0],16,1);
	POINT_COLOR = WHITE;
	LCD_DrawRectangle(5,113,123,122);
	LCD_DrawLine(5,115,123,115);
	LCD_DrawLine(5,118,123,118);
}

void UI_DrawSelect (u8 i)
{
	POINT_COLOR = WHITE;
	LCD_DrawFillRectangle(5,5 + i*18,122,21 + i*18);
	POINT_COLOR = BLACK;
	Show_Str(7,5 + i*18,POINT_COLOR,BACK_COLOR,names[TOP - 1 + i],16,1);
	old_index = i;
}

void UI_Select(u8 index)
{
  u8 i;
  if(index - TOP < 0)  //上翻
	{
	  TOP = index - 5;
		LCD_Fill(4,4,123,112,BLACK);
		POINT_COLOR = WHITE;
		for(i=0;i<=5;i++)
	  {
		  LCD_DrawRectangle(5,5 + i*18,122,21 + i*18);
	    Show_Str(7,5 + i*18,POINT_COLOR,BACK_COLOR,names[TOP - 1 + i],16,1);
	  }
    UI_DrawSelect(5);

	}else 
	if(index - TOP > 5)  //下翻
	{
	  TOP = index;
		LCD_Fill(4,4,123,112,BLACK);
		POINT_COLOR = WHITE;
		for(i=0;i<=5&&i!=5;i++)
	  {
		  LCD_DrawRectangle(5,5 + i*18,122,21 + i*18);
	    Show_Str(7,5 + i*18,POINT_COLOR,BACK_COLOR,names[TOP - 1 + i],16,1);
	  }
    UI_DrawSelect(0);
	}else   //不翻页
	{
		LCD_Fill(5,5 + old_index*18,122,21 + old_index*18,BLACK);
		POINT_COLOR = WHITE;
		LCD_DrawRectangle(5,5 + old_index*18,122,21 + old_index*18);
	  Show_Str(7,5 + old_index*18,POINT_COLOR,BACK_COLOR,names[TOP - 1 + old_index],16,1);
		i = index - TOP;
    UI_DrawSelect(i);
	}
}

void UI_Info(u8 * str,u16 COLOR)
{
	POINT_COLOR = COLOR;
  LCD_Fill(13,43,113,83,BACK_COLOR);
	LCD_DrawRectangle(13,43,113,83);
	LCD_DrawRectangle(14,44,112,82);
	LCD_DrawRectangle(16,46,110,80);
	Gui_StrCenter(0,55,POINT_COLOR,BACK_COLOR,str,16,1);
}

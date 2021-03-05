#include "file.h"

char SDPath[4];

FATFS fs;													/* FatFs文件系统对象 */
FIL file;													/* 文件对象 */
DIR dir;                          /* 目录对象 */
FILINFO f_info;                   /* 文件信息对象 */
FRESULT res;                      /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
extern char names[20][13];               /* 文件名 */
u8 i = 0,j = 0;
u8 file_num,TOP;

FRESULT SD_mount(void)
{
  if(FATFS_LinkDriver(&USER_Driver, SDPath) == 0)
  res = f_mount(&fs,"0:",1); 					//挂载SD卡

	if(res == FR_OK)
	{
		HAL_Delay(1);
		return res;
	}
	return res;
}
	
FRESULT scan_files (char* path)
{
	FILINFO fno;
	file_num = 0;
 if ( f_opendir(&dir, path) == FR_OK) 
	{
		for(;;)
		{
			res = f_readdir(&dir, &fno); 
			 if (res != FR_OK || fno.fname[0] == 0) break; 
			{			
				{
					if(!fno.fname[0])         break; 
					  if(strrchr(fno.fname,'.WAV') != NULL)
						{
						
							file_num++;
							for(j=0;j<=13&&i<=20;j++)
							{
								names[i][j]=fno.fname[j];
							}
							i++;
						
						}
//					if (file_num >= TOP)
//					{
//						for(j=0;j<=13&&i<=5;j++)
//						{
//							f_name[i][j]=fno.fname[j];
//						}
//						j = 0;
//						i++;
//					}
					
				}
			}
		}
	}
 return res;
} 

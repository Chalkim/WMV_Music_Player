#include "file.h"

char SDPath[4];

FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL file;													/* �ļ����� */
DIR dir;                          /* Ŀ¼���� */
FILINFO f_info;                   /* �ļ���Ϣ���� */
FRESULT res;                      /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
extern char names[20][13];               /* �ļ��� */
u8 i = 0,j = 0;
u8 file_num,TOP;

FRESULT SD_mount(void)
{
  if(FATFS_LinkDriver(&USER_Driver, SDPath) == 0)
  res = f_mount(&fs,"0:",1); 					//����SD��

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

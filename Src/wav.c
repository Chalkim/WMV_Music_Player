#include "wav.h"
int a = 0;
char myflag;
extern DAC_HandleTypeDef hdac;
extern u8 state;
extern TIM_HandleTypeDef htim6;
extern FIL WAV_file;

/*大小端转换*/
u32 BYTE4_MSB(BYTE *DATA)
{
  return ((u32)DATA[3]<<24)+((u32)DATA[2]<<16)+((u32)DATA[1]<<8)+((u32)DATA[0]);
}

/*
功能：获取WAV文件头信息
参数：path:文件路径
      WAVInfo：结构体，用于储存WAV文件信息
*/
int WAV_GET_Info(const TCHAR* path,WAVInfoTypedef* WAVInfo)
{
	FRESULT res;
	FIL file;													/* 文件对象 */
	UINT fnum;            					  /* 文件成功读写数量 */
	res = f_open(&file, path, FA_OPEN_EXISTING | FA_READ); 	 
	if(res == FR_OK)
	{
		res &= f_read(&file, WAVInfo->RIFF, sizeof(WAVInfo->RIFF), &fnum);
		res &= f_read(&file, WAVInfo->FILESize, sizeof(WAVInfo->FILESize), &fnum);
		res &= f_read(&file, WAVInfo->WAVE, sizeof(WAVInfo->WAVE), &fnum);
		res &= f_read(&file, WAVInfo->fmt, sizeof(WAVInfo->fmt), &fnum);
		res &= f_read(&file, WAVInfo->TRASH, sizeof(WAVInfo->TRASH), &fnum);
		res &= f_read(&file, WAVInfo->TYPE, sizeof(WAVInfo->TYPE), &fnum);
		res &= f_read(&file, WAVInfo->WAY, sizeof(WAVInfo->WAY), &fnum);
		res &= f_read(&file, WAVInfo->SAMRate, sizeof(WAVInfo->SAMRate), &fnum);
		res &= f_read(&file, WAVInfo->BYTERate, sizeof(WAVInfo->BYTERate), &fnum);
		res &= f_read(&file, WAVInfo->DATASize, sizeof(WAVInfo->DATASize), &fnum);
		res &= f_read(&file, WAVInfo->PCMBit, sizeof(WAVInfo->PCMBit), &fnum); 
	}
	/* 不再读写，关闭文件 */
	f_close(&file);	
	return res;
}

void WAV_GET_SAMRate(WAVInfoTypedef* WAVInfo,u32 *SAMRate)
{
  *SAMRate = BYTE4_MSB(WAVInfo->SAMRate);
}

void WAV_GET_PCMBit(WAVInfoTypedef* WAVInfo,u16 *PCMBit)
{
  *PCMBit = BYTE4_MSB(WAVInfo->PCMBit);
}

void WAV_GET_WAY(WAVInfoTypedef* WAVInfo,u16 *WAY)
{
  *WAY = BYTE4_MSB(WAVInfo->WAY);
}

/*
功能：文件预加载，找到数据区的起始位置
参数：path：文件路径
			file：文件对象
*/
int WAV_PreLoad(const TCHAR* path,FIL * file)
{

	FRESULT res;
	UINT fnum;            					  /* 文件成功读写数量 */
	BYTE DATA[1];
	BYTE DATASize[4];
	int i;
	if(a == 0)
	{
		res = f_open(file, path, FA_OPEN_EXISTING | FA_READ);
		do
		{
			res &= f_read(file, DATA,1,&fnum);
			if(DATA[0] == 0x64) 
			{
				res &= f_read(file, DATA,1,&fnum);
				if(DATA[0] == 0x61)
				{
					res &= f_read(file, DATA,1,&fnum);
					if(DATA[0] == 0x74)
					{
						res &= f_read(file, DATA,1,&fnum);
						if(DATA[0] == 0x61)
						{
							a = 1;
							break;
						}
					}
				}
			}
		}while(res == 0);
		res &= f_read(file, DATASize,4,&fnum);
	}
	return res;
}

/*
功能：读取数据区，并转换为数字信号 
BUF:原始数据缓冲区（文件）
DMA_BUF:DMA播放用的缓冲区
mode:0：选择DMA_BUF前部分
		 1：选择DMA_BUF后部分
PCMBit：位深度
WAY：声道
*/
int WAV_READ(FIL * file,BYTE * BUF,u16 * DMA_BUF,int mode,u16 PCMBit,u16 WAY)
{
	UINT fnum;            					  /* 文件成功读写数量 */
	FRESULT res;
	int i;

	if (mode == 0)
	{
		res &= f_read(file,BUF,sdBUF_Size,&fnum);
		for(i=0;i < sdBUF_Size;i = i + 4)
		{

			DMA_BUF[i/4] = (short int)(((u16)BUF[i + 1] << 8) + ((u16)BUF[i])) + 0x8000;
		}
	}
	if (mode == 1)
	{
		res &= f_read(file,BUF,sdBUF_Size,&fnum);
		for(i=0;i < sdBUF_Size;i = i + 4)
		{
			DMA_BUF[DMA_BUF_Size/2+i/4] = (short int)(((u16)BUF[i + 1] << 8) + ((u16)BUF[i])) + 0x8000;
		}
	}
	
	if(fnum == 0)
	{
			HAL_TIM_Base_Stop(&htim6);
			HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_1);
			WAV_STOP(&WAV_file);
			state = 2;
	}
}

int WAV_CHBUF(FIL * WAV_file,BYTE * sdBUF,u16 * DMA_BUF,u16 PCMBit,u16 WAY)
{
		if (myflag ==1)
		{
      WAV_READ(WAV_file,sdBUF,DMA_BUF,0, PCMBit, WAY);
			myflag =0;
		}
		if (myflag ==2)
		{
      WAV_READ(WAV_file,sdBUF,DMA_BUF,1, PCMBit, WAY);
			myflag =0;
		}
}

int WAV_STOP(FIL * WAV_file)
{
	FRESULT res;
  res = f_close(WAV_file);
	a = 0;
	return res;
}

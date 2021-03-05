#include "wav.h"
int a = 0;
char myflag;
extern DAC_HandleTypeDef hdac;
extern u8 state;
extern TIM_HandleTypeDef htim6;
extern FIL WAV_file;

/*��С��ת��*/
u32 BYTE4_MSB(BYTE *DATA)
{
  return ((u32)DATA[3]<<24)+((u32)DATA[2]<<16)+((u32)DATA[1]<<8)+((u32)DATA[0]);
}

/*
���ܣ���ȡWAV�ļ�ͷ��Ϣ
������path:�ļ�·��
      WAVInfo���ṹ�壬���ڴ���WAV�ļ���Ϣ
*/
int WAV_GET_Info(const TCHAR* path,WAVInfoTypedef* WAVInfo)
{
	FRESULT res;
	FIL file;													/* �ļ����� */
	UINT fnum;            					  /* �ļ��ɹ���д���� */
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
	/* ���ٶ�д���ر��ļ� */
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
���ܣ��ļ�Ԥ���أ��ҵ�����������ʼλ��
������path���ļ�·��
			file���ļ�����
*/
int WAV_PreLoad(const TCHAR* path,FIL * file)
{

	FRESULT res;
	UINT fnum;            					  /* �ļ��ɹ���д���� */
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
���ܣ���ȡ����������ת��Ϊ�����ź� 
BUF:ԭʼ���ݻ��������ļ���
DMA_BUF:DMA�����õĻ�����
mode:0��ѡ��DMA_BUFǰ����
		 1��ѡ��DMA_BUF�󲿷�
PCMBit��λ���
WAY������
*/
int WAV_READ(FIL * file,BYTE * BUF,u16 * DMA_BUF,int mode,u16 PCMBit,u16 WAY)
{
	UINT fnum;            					  /* �ļ��ɹ���д���� */
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

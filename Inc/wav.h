#ifndef __WAV_H_
#define __WAV_H_

#include "file.h"
#define sdBUF_Size 4096               //sd��������С
#define DMA_BUF_Size sdBUF_Size/2     //���Ż�������С

extern char myflag;        //�жϱ�־

typedef struct {
	BYTE RIFF[4];        //RIFF
	BYTE FILESize[4];    //�ļ���С
	BYTE WAVE[4];        //WAVE
	BYTE fmt[4];         //fmt 
	BYTE TRASH[4];       //��֪��ʲô��
	BYTE TYPE[2];        //��������
	BYTE WAY[2];         //ͨ����
	BYTE SAMRate[4];     //������
	BYTE BYTERate[4];    //����
	BYTE DATASize[2];    //һ�β���������
	BYTE PCMBit[2];      //λ���
}WAVInfoTypedef;

int WAV_GET_Info(const TCHAR*  path,WAVInfoTypedef* WAVInfo);
void WAV_GET_SAMRate(WAVInfoTypedef* WAVInfo,u32 *SAMRate);
void WAV_GET_PCMBit(WAVInfoTypedef* WAVInfo,u16 *PCMBit);
void WAV_GET_WAY(WAVInfoTypedef* WAVInfo,u16 *WAY);
int WAV_PreLoad(const TCHAR* path,FIL * file);
int WAV_READ(FIL * file,BYTE * BUF,u16 * DMA_BUF,int mode,u16 PCMBit,u16 WAY);
int WAV_CHBUF(FIL * WAV_file,BYTE * sdBUF,u16 * DMA_BUF,u16 PCMBit,u16 WAY);
int WAV_STOP(FIL * WAV_file);

#endif

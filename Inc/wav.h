#ifndef __WAV_H_
#define __WAV_H_

#include "file.h"
#define sdBUF_Size 4096               //sd缓冲区大小
#define DMA_BUF_Size sdBUF_Size/2     //播放缓冲区大小

extern char myflag;        //中断标志

typedef struct {
	BYTE RIFF[4];        //RIFF
	BYTE FILESize[4];    //文件大小
	BYTE WAVE[4];        //WAVE
	BYTE fmt[4];         //fmt 
	BYTE TRASH[4];       //不知道什么用
	BYTE TYPE[2];        //编码类型
	BYTE WAY[2];         //通道数
	BYTE SAMRate[4];     //采样率
	BYTE BYTERate[4];    //码率
	BYTE DATASize[2];    //一次采样数据量
	BYTE PCMBit[2];      //位深度
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

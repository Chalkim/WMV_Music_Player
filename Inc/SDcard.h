#ifndef __SDCARD_H_
#define __SDCARD_H_

#include "stm32f1xx_hal.h"
#include "sign.h"

// SD�����Ͷ���  
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	 

/*�ܽŶ���*/
#define CS_GPIO                       GPIOA
#define CS_GPIO_PIN                   GPIO_PIN_15

#define SCLK_GPIO                     GPIOB
#define SCLK_GPIO_PIN                 GPIO_PIN_3

#define MISO_GPIO                     GPIOB
#define MISO_GPIO_PIN                 GPIO_PIN_4

#define MOSI_GPIO                     GPIOB
#define MOSI_GPIO_PIN                 GPIO_PIN_5

#define SD_CS_SET()                   HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,GPIO_PIN_SET)
#define SD_CS_RESET()                 HAL_GPIO_WritePin(CS_GPIO,CS_GPIO_PIN,GPIO_PIN_RESET)

#define SD_MOSI_SET()                 HAL_GPIO_WritePin(MOSI_GPIO,MOSI_GPIO_PIN,GPIO_PIN_SET)
#define SD_MOSI_RESET()               HAL_GPIO_WritePin(MOSI_GPIO,MOSI_GPIO_PIN,GPIO_PIN_RESET)

// SD��ָ���  	   
#define CMD0    0       //����λ
#define CMD1    1
#define CMD8    8       //����8 ��SEND_IF_COND
#define CMD9    9       //����9 ����CSD����
#define CMD10   10      //����10����CID����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00
#define CMD17   17      //����17����sector
#define CMD18   18      //����18����Multi sector
#define CMD23   23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector
#define CMD25   25      //����25��дMulti sector
#define CMD41   41      //����41��Ӧ����0x00
#define CMD55   55      //����55��Ӧ����0x01
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00
//����д���Ӧ������
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD����Ӧ�����
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF

extern SPI_HandleTypeDef hspi3;

//��������
u8 SD_SPI_ReadWriteByte(u8 data);
void SD_SPI_SpeedLow(void);
void SD_SPI_SpeedHigh(void);
u8 SD_WaitReady(void);							//�ȴ�SD��׼��
u8 SD_GetResponse(u8 Response);					//�����Ӧ
u8 SD_Init(void);								//��ʼ��
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt);		//����
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);		//д��
u32 SD_GetSectorCount(void);   					//��������
u8 SD_GetCID(u8 *cid_data);                     //��SD��CID
u8 SD_GetCSD(u8 *csd_data);                     //��SD��CSD
	
#endif

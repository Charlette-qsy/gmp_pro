#ifndef __SPI_H__
#define __SPI_H__

#include "driver/inc/SLMCU.h"          
#include "driver/inc/public.h"

#define SPI_SEND_BUF_SIZE	100
#define SPI_REV_BUF_SIZE	100

typedef struct
{
	uint8_t SendBuf[SPI_SEND_BUF_SIZE];
	uint8_t RevBuf[SPI_REV_BUF_SIZE];  

	uint16_t SBWriteIdx;        // ���ͻ���д�����
	uint16_t SBReadIdx;			// ���ͻ����ȡ���
	uint16_t UnSendCnt;			// δ�����ֽ���

	uint8_t IntSendFlag;        // ����æµ��־

	uint16_t RBWriteIdx;        // ���ջ���д�����
	uint16_t RBReadIdx;			// ���ջ����ȡ���
	uint16_t UnRevCnt;			// δ��ȡ�ֽ���

}SPI_PARAM_s;


extern SPI_PARAM_s Spi0_S;
void SPI_Config(void);

#endif



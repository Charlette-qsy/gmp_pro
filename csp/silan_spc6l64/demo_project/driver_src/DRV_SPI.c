#include "driver/inc/SPI.h"
#include "driver/inc/DMA.h"
#include "driver/inc/GPIO.h"

SPI_PARAM_s Spi0_S;

void SPI_Config(void)
{	
	Gpio_Af_Sel(DIGITAL,PA,4,5);//SPI0 NSS
	Gpio_Af_Sel(DIGITAL,PA,5,5);//SPI0 SCK
	Gpio_Af_Sel(DIGITAL,PA,6,5);//SPI0 MISO
	Gpio_Af_Sel(DIGITAL,PA,7,5);//SPI0 MOSI	
	
	SPI0->SPICTL0_b.SPC = 0;//0,ѡ��ȫ˫����ʽ  1,ѡ���˫����ʽ
//	SPI0->SPICTL0_b.BIDIROE = 0;//0,MOMI��SISO���ó�����  1,MOMI��SISO���ó����
//	SPI0->SPICTL0_b.MODFEN = 0;//0,��������ʽ��ͻ��������ֹ��NSS����ͨIO  1,��������ʽ��ͻ�������ʹ��
	
	SPI0->SPICTL0_b.DFF = 1;//0,8 λ����֡��ʽ  1,16λ
	SPI0->SPICTL0_b.LSBF = 0;//0,��λ���ȷ���  1,��λ���ȷ���
	SPI0->SPICTL0_b.MSTEN = 1;//0,�����ڴӻ���ʽ  1,������������ʽ

	SPI0->SPICTL1_b.CPOL = 1;//Clock Polarity High
	SPI0->SPICTL1_b.CPHA = 0;//First edge to lock the data
	SPI0->SPICTL1_b.SPCR = 0x07;//4��Ƶ	

//	SPI0->SPICTL0_b.SPTIE = 1;//0,��ֹSPTEF�ж�  1,����SPTEF�����ж�
	SPI0->SPICTL0_b.SPRIE = 1;//SPRF�ж�ʹ��	
	SPI0->SPICTL0_b.SPIE = 1;//ʹ��SPIģ��
	
//	NVIC_ClearPendingIRQ(SPI0_IRQn);
//	NVIC_SetPriority(SPI0_IRQn,1);	
//	NVIC_EnableIRQ(SPI0_IRQn);	
}


void SPI0_IRQHandler(void)
{
	uint32_t temp8;

	temp8 = SPI0->SPIFLAG;
	
	if(SPI0->SPICTL0_b.SPRIE == 1)
	{
		if (temp8 & SPI0_SPIFLAG_SPRF_Msk)
		{
			Spi0_S.RevBuf[Spi0_S.RBReadIdx ++] = SPI0->SPIDAT;
		}
		
		if (temp8 & SPI0_SPIFLAG_RXOV_Msk)
		{
			SPI0->SPIFLAG_b.RXOV = 0x00;
		}
		
		if (temp8 & SPI0_SPIFLAG_WCOL_Msk)
		{
			SPI0->SPIFLAG_b.WCOL = 0x00;
		}
		
		if (temp8 & SPI0_SPIFLAG_MODF_Msk)
		{
			SPI0->SPIFLAG_b.MODF = 0x00;
		}
	}
	
//	if(SPI0->SPICTL0_b.SPTIE == 1)
//	{
//		if(Spi0_S.SBWriteIdx <= 15)
//			SPI0->SPIDAT = D_data0[Spi0_S.SBWriteIdx ++];
//		else
//			SPI0->SPICTL0_b.SPTIE = 0;
//	}
	
}





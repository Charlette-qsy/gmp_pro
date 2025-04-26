/**
* @file          : Uart1.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for Uart1 configuration.
* @version       : Ver. 1.00

* H/W Platform   : SL_FOC FOR MOTOR CONTROL

*------------------------------------------------------------------------------
 
* Compiler info  : Keil v5.20
 
*------------------------------------------------------------------------------
 
* Note: In this software, the function is used in motor control.

*------------------------------------------------------------------------------

*  History:  

*              mm/dd/yyyy ver. x.y.z author

*              mm1/dd1/yyyy1 ver. x.y.z author1

*------------------------------------------------------------------------------
* @attention
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, SLMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.

* <h2><center>&copy; COPYRIGHT 2017 SLMicroelectronics</center></h2>
*******************************************************************************
*/

/***************************************************************************
	���ļ�չʾ��UART��ͨѶЭ���Լ���ʼ����������
******************************************************************************/


#include "driver/inc/uart1.h"
//#include "driver/inc/config.h"
#include "driver/inc/GPIO.h"

/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Uart1_Init();
  * @endcode
  * @warning:
*/

UART_PARAM_s Uart0_S,Uart1_S,Uart2_S;

void UART_ISR_EN(UART0_Type *UARTx)
{
	if(UARTx == UART0)
	{
		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_SetPriority(UART0_IRQn,0);
		NVIC_EnableIRQ(UART0_IRQn);		
	}
	else if(UARTx == UART1)
	{
		NVIC_ClearPendingIRQ(UART1_IRQn);
		NVIC_SetPriority(UART1_IRQn,0);
		NVIC_EnableIRQ(UART1_IRQn);			
	}
	/*
	else if(UARTx == UART2)
	{
		NVIC_ClearPendingIRQ(UART2_IRQn);
		NVIC_SetPriority(UART2_IRQn,0);
		NVIC_EnableIRQ(UART2_IRQn);			
	}	*/
}

void UART_Model0_Config(UART0_Type *UARTx)
{	
	UARTx->UARTCTL_b.TXEN = 1;//����ʹ��	
	UARTx->UARTCTL_b.RXEN = 0;//���н�������ʹ��
	
	UARTx->UARTCTL_b.SM0 = 0;//
	UARTx->UARTCTL_b.SM1 = 0;//����ģʽѡ��
	UARTx->UARTCTL_b.SM2 = 0;//���ͨ�ſ���λ
	
	UARTx->UARTCTL_b.HDEN = 0;//���߰�˫��ʹ��λ
	UARTx->UARTCTL_b.HDOE = 0;//��˫��OE�ſ���λ
	UARTx->UARTCTL_b.RXDMAE = 0;//����DMAʹ��λ
	UARTx->UARTCTL_b.TXDMAE = 0;//����DMAʹ��λ
	
	UARTx->UARTBRCFG_b.BRTEN = 1;//�����ʷ���������
	UARTx->UARTIBRD_b.BRDDI = UART0_IBRD;//������������Ƶ�Ĵ���
	UARTx->UARTBRCFG_b.BRDDF = UART0_FBRD;//UARTС����Ƶ
	
	UARTx->UARTINTEN_b.RIE = 1;//�����ж�ʹ��
	UARTx->UARTINTEN_b.TIE = 1;//��������ж�ʹ��
	
	UARTx->UARTCTL_b.UARTEN = 1;//UARTʹ��	
}

void UART_Model123_Config(UART0_Type *UARTx, uint8_t model, uint8_t dir)
{	
	if(dir == UART_FUNC_RX)
	{
		UARTx->UARTCTL_b.TXEN = 0;//����ʹ��	
		UARTx->UARTCTL_b.RXEN = 1;//���н�������ʹ��
	}
	if(dir == UART_FUNC_TX)
	{
		UARTx->UARTCTL_b.TXEN = 1;//����ʹ��	
		UARTx->UARTCTL_b.RXEN = 0;//���н�������ʹ��		
	}
	if(dir == UART_FUNC_DOUBLE) 
	{
		UARTx->UARTCTL_b.TXEN = 1;//����ʹ��	
		UARTx->UARTCTL_b.RXEN = 1;//���н�������ʹ��		
	}
	
	if(model == 0X01)
	{
		UARTx->UARTCTL_b.SM0 = 1;//
		UARTx->UARTCTL_b.SM1 = 0;//����ģʽѡ��	
		
		UARTx->UARTCTL_b.PEN = 0;//У��ʹ��λ
		UARTx->UARTCTL_b.EPS = 0;//��żУ��			
	}
	else if(model == 0X02)
	{
		UARTx->UARTCTL_b.SM0 = 0;//
		UARTx->UARTCTL_b.SM1 = 1;//����ģʽѡ��	
		UARTx->UARTCTL_b.SM2 = 1;//���ͨ�ſ���λ		
	}
	else if(model == 0X03)
	{
		UARTx->UARTDATA_b.STB8 = 0;//
		UARTx->UARTCTL_b.SM0 = 1;//
		UARTx->UARTCTL_b.SM1 = 1;//����ģʽѡ��	
		UARTx->UARTCTL_b.SM2 = 0;//���ͨ�ſ���λ
	}
	
	UARTx->UARTCTL_b.HDEN = 0;//���߰�˫��ʹ��λ
	UARTx->UARTCTL_b.HDOE = 0;//��˫��OE�ſ���λ
	
	UARTx->UARTBRCFG_b.BRTEN = 1;//�����ʷ���������
	UARTx->UARTIBRD_b.BRDDI = UART0_IBRD;//������������Ƶ�Ĵ���
	UARTx->UARTBRCFG_b.BRDDF = UART0_FBRD;//UARTС����Ƶ
	
	UARTx->UARTINTEN_b.RIE = 1;//�����ж�ʹ��
	UARTx->UARTINTEN_b.TIE = 1;//��������ж�ʹ��
	
	UARTx->UARTCTL_b.UARTEN = 1;//UARTʹ��
}

void UART_Half_Duplex_Config(UART0_Type *UARTx, uint8_t dir)
{
	UARTx->UARTCTL_b.PEN = 0;//У��ʹ��λ
	UARTx->UARTCTL_b.EPS = 0;//��żУ��	
	
	UARTx->UARTCTL_b.TXEN = 1;//����ʹ��	
	UARTx->UARTCTL_b.RXEN = 1;//���н�������ʹ��
	
	UARTx->UARTCTL_b.SM0 = 1;//
	UARTx->UARTCTL_b.SM1 = 0;//����ģʽѡ��
	UARTx->UARTCTL_b.SM2 = 0;//���ͨ�ſ���λ
	
	UARTx->UARTCTL_b.HDEN = 1;//���߰�˫��ʹ��λ
	if(dir == UART_FUNC_RX)
		UARTx->UARTCTL_b.HDOE = 0;//��˫��OE�ſ���λ
	else if(dir == UART_FUNC_TX)
		UARTx->UARTCTL_b.HDOE = 1;
	UARTx->UARTCTL_b.RXDMAE = 0;//����DMAʹ��λ
	UARTx->UARTCTL_b.TXDMAE = 0;//����DMAʹ��λ
	
	UARTx->UARTBRCFG_b.BRTEN = 1;//�����ʷ���������
	UARTx->UARTIBRD_b.BRDDI = UART0_IBRD;//������������Ƶ�Ĵ���
	UARTx->UARTBRCFG_b.BRDDF = UART0_FBRD;//UARTС����Ƶ
	
	UARTx->UARTINTEN_b.RIE = 1;//�����ж�ʹ��
	UARTx->UARTINTEN_b.TIE = 1;//��������ж�ʹ��
	
	UARTx->UARTCTL_b.UARTEN = 1;//UARTʹ��	
}

void UART0_IRQHandler(void)
{
	uint32_t temp16;

	temp16 = (UART0->UARTINTSTA) & (UART0->UARTINTEN);

	if (temp16 & UART0_UARTINTSTA_RIF_Msk)
	{
		Uart0_S.RevBuf[Uart0_S.RBWriteIdx] = UART0->UARTDATA_b.UARTDATA;

		Uart0_S.UnRevCnt++;
		Uart0_S.RBWriteIdx++;
		if(Uart0_S.RBWriteIdx >= UART_REV_BUF_SIZE)
		{
			Uart0_S.RBWriteIdx = 0;
		}
		
		UART0->UARTINTCLR = UART0_UARTINTCLR_RIC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_TIF_Msk)
	{
		if(Uart0_S.UnSendCnt > 0)
		{
			Uart0_S.UnSendCnt--;	
      		Uart0_S.SBReadIdx++;
			UART0->UARTDATA = Uart0_S.SendBuf[Uart0_S.SBReadIdx];			
			
			if(Uart0_S.SBReadIdx >= UART_SEND_BUF_SIZE)
			{
				Uart0_S.SBReadIdx = 0;
			}
		}
		else
		{
			Uart0_S.SBWriteIdx = 0;
			Uart0_S.SBReadIdx = 0;
			Uart0_S.IntSendFlag = 0;
		}		
		UART0->UARTINTCLR = UART0_UARTINTCLR_TIC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_TXE_Msk)
	{
		UART0->UARTINTEN_b.TXEIE = 0x00;
	}

	if (temp16 & UART0_UARTINTSTA_OEF_Msk)
	{
		UART0->UARTINTCLR = UART0_UARTINTCLR_OEC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_PEF_Msk)
	{
		UART0->UARTINTCLR = UART0_UARTINTCLR_PEC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_FEF_Msk)
	{
		UART0->UARTINTCLR = UART0_UARTINTCLR_FEC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_BEF_Msk)
	{
		UART0->UARTINTCLR = UART0_UARTINTCLR_BEC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_BRDEF_Msk)
	{
		UART0->UARTIBRD = 1;
		//Ӳ������
	}

}


void UART1_IRQHandler(void)
{
	uint32_t temp16;

	temp16 = (UART1->UARTINTSTA) & (UART1->UARTINTEN);

	if (temp16 & UART0_UARTINTSTA_RIF_Msk)
	{
		Uart1_S.RevBuf[Uart1_S.RBWriteIdx] = UART1->UARTDATA_b.UARTDATA;

		Uart1_S.UnRevCnt++;
		Uart1_S.RBWriteIdx++;
		if(Uart1_S.RBWriteIdx >= UART_REV_BUF_SIZE)
		{
			Uart1_S.RBWriteIdx = 0;
		}
		
		UART1->UARTINTCLR = UART0_UARTINTCLR_RIC_Msk;
	}

	if (temp16 & UART0_UARTINTSTA_TIF_Msk)
	{
		if(Uart1_S.UnSendCnt > 0)
		{
			Uart1_S.UnSendCnt--;	
      		Uart1_S.SBReadIdx++;
			UART1->UARTDATA = Uart1_S.SendBuf[Uart1_S.SBReadIdx];			
			
			if(Uart1_S.SBReadIdx >= UART_SEND_BUF_SIZE)
			{
				Uart1_S.SBReadIdx = 0;
			}
		}
		else
		{
			Uart1_S.SBWriteIdx = 0;
			Uart1_S.SBReadIdx = 0;
			Uart1_S.IntSendFlag = 0;
		}		
		UART1->UARTINTCLR = UART0_UARTINTCLR_TIC_Msk;
	}	
}

/*************************************************************************
 		ͨ���״ζ�UARTDR��ֵ�����������ж�
**************************************************************************/

void UartSendStart(UART_PARAM_s *v, UART0_Type *UARTx)
{
	if(v->IntSendFlag) return;
	
	if(v->UnSendCnt > 0)
	{
		if(v->IntSendFlag==0) v->UnSendCnt--;// �粻��һ�������෢һ���ֽ�

		v->IntSendFlag = 1;
		UARTx->UARTDATA = v->SendBuf[v->SBReadIdx];
		
	}
	else
	{
		v->SBWriteIdx = 0;
		v->SBReadIdx = 0;
	}
}


/***************************************************************************
		�����͵�һ���ֽ����ݷ��뷢�ͻ���
****************************************************************************/
void UartSendByte(UART_PARAM_s *v,uint8_t byte)
{
	v->SendBuf[v->SBWriteIdx] = byte;
	v->UnSendCnt++;
	v->SBWriteIdx++;
	if(v->SBWriteIdx >= UART_SEND_BUF_SIZE)
	{
		v->SBWriteIdx = 0;
	}
}
/*************************************************************************
 			�����ַ��������뷢�ͻ�����
**************************************************************************/

void UartSendString(UART_PARAM_s *v,uint8_t *str)
{
	while((*str) != '\0')
	{
		v->SendBuf[v->SBWriteIdx] = *str;
		str++;
		v->UnSendCnt++;
		v->SBWriteIdx++;
		if(v->SBWriteIdx >= UART_SEND_BUF_SIZE)
		{
			v->SBWriteIdx = 0;
		}
	}
}
/***************************************************************************
		��ֵת��
****************************************************************************/
void UartSentUint32ToASCII(UART_PARAM_s *v,uint32_t output)
{
	uint8_t digit = 0;
	while (output >= 1000000000) { output -= 1000000000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=  100000000) { output -= 100000000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=   10000000) { output -= 10000000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=    1000000) { output -= 1000000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=     100000) { output -= 100000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=      10000) { output -= 10000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=       1000) { output -=  1000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=        100) { output -=   100; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=         10) { output -=    10; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=          1) { output -=     1; digit++; } UartSendByte(v,digit + 0x30);
}

void UartSentInt16ToASCII(UART_PARAM_s *v,uint16_t output)
{
	uint8_t digit = 0;	
	while (output >= 10000) { output -= 10000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=  1000) { output -=  1000; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=   100) { output -=   100; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=    10) { output -=    10; digit++; } UartSendByte(v,digit + 0x30); digit = 0;
	while (output >=     1) { output -=     1; digit++; } UartSendByte(v,digit + 0x30);
}





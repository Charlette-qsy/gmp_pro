/**
* @file          : FLASH.c
* @author        : MCU Lab 
* @date          : 07/10/2017
* @brief         : This file is for FLASH control function.
* @version       : Ver. 0.00

* H/W Platform       : SILAN THREE SHUNT MOTOR CONCTROL

 *------------------------------------------------------------------------------
 
 * Compiler info     :keil v5
 
 *------------------------------------------------------------------------------
 
Note: In this software, the function is used in motor control.

*-------------------------------------------------------------------------------

*  History:  

*              07/10/2017   ver0.0  MCU Lab 

*           

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

* <h2><center>&copy; COPYRIGHT 2015 SLMicroelectronics</center></h2>
*******************************************************************************/

#include "driver/inc/IAP.h"

/********************************************************************************************
  * @brief      WriteFlashWord.
  * @param[in]  u32 addr,u32 data 
  * @param[out] uint8_t : err  0���޹���   1���й���
  * @retval     none
  * @pre  
  * @see  
  * @par        
  * -This example shows how to call the function:
  * @code
  * uint8_t WriteFlashWord(u32 addr,u32 data);
  * @endcode
  * @warning:   none
********************************************************************************************/
uint8_t WriteFlashWord(uint32_t addr,uint32_t data)
{
	uint8_t err = 0;
	__disable_irq(); 														
	FLASH->CCLR = 0x3E;						// FLASH����ʹ�����
	FLASH->ICR = 0x7F;						// ������й��ϱ�־λ
	FLASH->IEN = 0x7F;						// ʹ�������ж�
	FLASH->ADDR = addr;						// ��ַ��ֵ
	FLASH->DATA = data;						// ���ݸ�ֵ
	FLASH->CSET_b.PROGEN = 1;			// �ֱ��ʹ��
	FLASH->FEED = 0x12345678;			// д���������KEY
	FLASH->FEED = 0x87654321;
	FLASH->CSET_b.OPSTART = 1;		// ��������
	while((FLASH->ISR & 0x01ul) == 0)	// �ȴ��������
	{
		if((FLASH->ISR & 0x7E) != 0) //�����ж�
		{
			err = 1;
			break;
		}
	}
	FLASH->ICR = 0x7F;						// ������й��ϱ�־λ
	FLASH->CCLR_b.PROGEN = 1;			// ����ֱ��ʹ��λ
	__enable_irq();	
	return err;
}										

/********************************************************************************************
  * @brief      EraseFlashSector.
  * @param[in]  u32 address 
  * @param[out] uint8_t : err  0���޹���   1���й���
  * @retval     none
  * @pre  
  * @see  
  * @par        
  * -This example shows how to call the function:
  * @code
  * uint8_t EraseFlashSector(u32 addr);
  * @endcode
  * @warning:   none
********************************************************************************************/
uint8_t EraseFlashSector(uint32_t addr)
{
	uint8_t err = 0;														
	FLASH->CCLR = 0x3E;						// FLASH����ʹ�����
	FLASH->ICR = 0x7F;						// ������й��ϱ�־λ
	FLASH->IEN = 0x7F;						// ʹ�������ж�
	FLASH->ADDR = addr;						// ��ַ��ֵ
	FLASH->CSET_b.PAGEEN = 1;			// �����ʹ��
	FLASH->FEED = 0x12345678;			// д���������KEY
	FLASH->FEED = 0x87654321;
	FLASH->CSET_b.OPSTART = 1;		// ��������
	while((FLASH->ISR & 0x01ul) == 0)	// �ȴ��������
	{
		if((FLASH->ISR & 0x7E) != 0) //�����ж�
		{
			err = 1;
			break;
		}
	}
	FLASH->ICR = 0x7F;						// ������й��ϱ�־λ
	FLASH->CCLR_b.PAGEEN = 1;			// ����ֱ��ʹ��λ
	return err;
}										



/********************************************************************************************
  * @brief      ReadFlashWord.
  * @param[in]  u32 address
  * @param[out] u32 data
  * @retval     none
  * @pre  
  * @see  
  * @par        
  * -This example shows how to call the function:
  * @code
  * u32 ReadFlashWord(u32 addr);
  * @endcode
  * @warning:   none   �����ڿ����֮�����϶�ȡ���ݣ����и���������ϵԭ��
********************************************************************************************/
uint32_t ReadFlashWord(uint32_t addr)
{
	uint32_t dat = 0;					
	uint32_t *ptr;
	ptr = (uint32_t *)addr;				// ָ��ָ���ַ
	dat = *ptr;							// ��ȡ����
	return dat;      					// ������ʱ240ns
}


uint32_t	FlashRead(unsigned long adr, unsigned long size, unsigned char *buff)
{
	__disable_irq();
	FLASH->CCLR = 0xFF;//��������
	FLASH->IEN  = 0xFF;//�ж�ʹ��
	FLASH->ICR  = 0xFF;//�ж�״̬���
	
	while(size)
	{
		FLASH->CSET_b.RDEN = 1;   //��ȡʹ��
		FLASH->ADDR = adr;
		FLASH->FEED = 0x12345678ul;
		FLASH->FEED = 0x87654321ul;//����FLASH��̻���������
		FLASH->CSET_b.OPSTART = 1;// ������ʼ
	   while (FLASH->ISR_b.COMPLETE == 0x00)
	  {
		if(FLASH->ISR_b.PROTECT == 1)
		{
			return(1);
		}
		if(FLASH->ISR_b.ERROR == 1)
		{
			return(1);
		}				
		if(FLASH->ISR_b.RCHOFF == 1)
		{
			return(1);
		}
		if(FLASH->ISR_b.DRDERR == 1)
		{
			return(1);
		}
	  }
	FLASH->ICR_b.COMPCLR = 1;//���������жϱ�־���
	FLASH->CCLR_b.RDEN = 1;//��ȡʹ�����
	*buff = FLASH->DATA;
	*(buff + 1) = (FLASH->DATA >> 8);
	*(buff + 2) = (FLASH->DATA >> 16);
	*(buff + 3) = (FLASH->DATA >> 24);
	buff += 0x04;
	adr += 0x04;
	size -= 0x04;
	}
	FLASH->IEN = 0x00; 
	__enable_irq();
	return (0); 	
}




	

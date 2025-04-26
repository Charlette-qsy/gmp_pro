/**
* @file          : adc.c
* @author        : SiLan Motor Lab 
* @date          : 02/12/2022
* @brief         : This file is for motor FOC function.
* @version       : Ver. 1.00

* H/W Platform   : SL_FOC FOR MOTOR CONCTROL

*------------------------------------------------------------------------------
 
* Compiler info  : Keil v5.20
 
*------------------------------------------------------------------------------
 
* Note: In this software, the function is used in motor control.

*-------------------------------------------------------------------------------

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

/******************************************************************************
* include file
******************************************************************************/
#include "driver/inc/adc.h"
/******************************************************************************
* global data for the project
******************************************************************************/
/******************************************************************************
* loacal define for the current file
******************************************************************************/

#define ADC_PA1         4  		// 	PA1,ADC4	 
#define ADC_PC1         6  		// 	PC1,ADC6
#define ADC_PB11        8  		// 	PB11,ADC8	
#define ADC_PB6       	11  	// 	PB6,ADC11	
#define ADC_OPA0       	0x13  	// 	OPA0,0x13

/******************************************************************************
* loacal data for the current file
******************************************************************************/
// ͬʱ����ģʽ(SIMULENx = 1)
uint8_t ChSel[16]   = {ADC_PA1,ADC_PC1,ADC_PB11,ADC_PB6,ADC_OPA0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t ACQPS[16]   = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
uint8_t TrigSel[16] = {5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
/******************************************************************************
* loacal prototypes function 
******************************************************************************/
/*����Դѡ���
		00���������
		01h������
		02h��BT41_EVENT
		03h��BT40_EVENT
		04h������
		05h��PWM0_SOCA
		06h��PWM0_SOCB
		07h��PWM1_SOCA
		08h��PWM1_SOCB
		09h��PWM2_SOCA
		0Ah��PWM2_SOCB
*/


/******************************************************************************
* loacal function for the current file
******************************************************************************/
/**
  * @brief      ADC init.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * ADC_Init();
  * @endcode
  * @warning:
*/
void ADC_Init(void)	
{
	uint8_t i = 0;
/*************************��������*****************************/	
	ADC_RESET;										 	// ADCģ�鸴λ
	ADC_ENABLE;										 	// ADCģ��ʹ��

	ACCESS_EN();	ADC->ADCCTL1_b.PD = 0;      		// ADC�ϵ磬�ߵ�ƽ��Ч	
	ACCESS_EN();	ADC->ADCCTL2_b.CLKDIV = ADC_CLKDIV_3;// ʱ�� 3��Ƶ����ΪADCģ��ʱ��
	ACCESS_EN();	ADC->ADCCTL2_b.SCDLY  = 2;  		// �����Ϳ�ʼת��֮�����ʱ
	ACCESS_EN();	ADC->ADCCTL2_b.STRW   = 4;     	// ��ʼת����������
	ADC_NONOVERLAP;										// ������ת�����ص�
	ADC_REF_INTERNAL;									// �ڲ��ⲿ�ο�Դѡ��ѡ���ڲ���϶�ο�Դ

/*************************CHANNEL SELECT*****************************/
	for(i=0; i<=15; i++)
	{
		ACCESS_EN();ADC->ADCCUCTL_b[i].ACQPS = ACQPS[i];//CCUx��������ѡ��(ACQPS+1)
		ACCESS_EN();ADC->ADCCUCTL_b[i].CHSEL = ChSel[i];//SOCͨ��ѡ��
		ACCESS_EN();ADC->ADCCUCTL_b[i].TRIGSEL = TrigSel[i];//CCUx����Դѡ��		
	}
	
/*************************AD�ж�����*****************************/
	ADC_INT_AT_EOC;										// ��ADC����������Ĵ�����ǰһ�����ڲ���INT����		   

	ACCESS_EN();	ADC->INTSEL1N2_b.INT1E = 1;     				// Enable ADCINT0
	ACCESS_EN();	ADC->INTSEL1N2_b.INT1CONT = 1;  				// Cont	
	ACCESS_EN();	ADC->INTSEL1N2_b.INT1SEL = 0; 					// EOC0 is selected as trigger source

/*************************ADʹ��*****************************/	
	ACCESS_EN();ADC->ADCCTL1_b.EN = 1;   /*Enable ADC*/  
}


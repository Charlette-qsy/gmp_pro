/**
* @file          : ACMP.c
* @author        : SiLan Motor Lab 
* @date          : 02/14/2022
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
#include "driver/inc/ACMP.h"
/******************************************************************************
* global data for the project
******************************************************************************/


/******************************************************************************
* loacal define for the current file
******************************************************************************/
//#define ADC_SEL 17

/******************************************************************************
* loacal data for the current file
******************************************************************************/


/******************************************************************************
* loacal prototypes function 
******************************************************************************/


/******************************************************************************
* loacal function for the current file
******************************************************************************/
/**
  * @brief      CMP init.
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * CMP_Init();
  * @endcode
  * @warning:
*/

/*------6.OCP����������------------------------------------------*/

#define CMP_NEG_VREF		10						// �Ƚ���CMP�Ĵ�����ֵ


 void CMP0_Init()
{	
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0PS  = C0PS_INPUT_SEL_OPA_OUTPUT;	// �Ƚ���P���ź�ѡ���˷����
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0OPS = C0OPS_SEL_OP1O;				// �˷�����ź�ѡ��OPA1O
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0EN  = CMP_ENABLE;					// �Ƚ���ʹ��
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0VRRL = 1;							// �����ѹ��λ��λ
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0VRRH = 1;							// �����ѹ��λ��λ
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0RDS = CMP_NEG_VREF;				// �����ѹֵ
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0VRHS = VRHS_SOURCE_SEL_VDD; 		// �ڲ������ѹ���ݵ�Դѡ��VDD
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0REFEN = REFEN_INTERN_REF_ENABLE; 	// �ڲ��ο���ѹʹ��
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0HYSEN = HYSEN_WITHOUT_HYSTERESIS; // �رճ���
	 ACCESS_EN();	 ACMP->CP0CTL_b.C0NS = C0NS_NEG_INPUT_SEL_CVREF0;   // ��������ѡ��CVREF0
//	 ACCESS_EN();	 ACMP->CP0CFG_b.C0FLG = 1;							// �Ƚ�����־λ��� 
//	 ACCESS_EN();	 ACMP->CP0CFG_b.C0GCEN = 1;							// �Ƚ����ſعر�
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0INTS = INTS_RE;					// �����ش���
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0INTM = 0;             		
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0DFILT = ((uint16_t)(72*1.5));   	// �����˲���������2�����ڣ���Ӧ3us
	 ACCESS_EN();	 ACMP->CP0CFG |=(1<<19);				 			// �ر�32Ԥ��Ƶ
	 ACCESS_EN();	 ACMP->CP0CFG_b.C0CLKD = 0;   						// ����Ƶ

 }
 void CMP1_Init()
{	
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1PS  = C1PS_INPUT_SEL_CP12P_PIN;		// �Ƚ���P���ź�ѡ��CP12P��������
//	 ACCESS_EN();	 ACMP->CP1CTL_b.C1OPS = C0OPS_SEL_OP0O;						// �˷�����ź�ѡ��OPA3O
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1EN  = CMP_ENABLE;									// �Ƚ���ʹ��
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1VRRL = 1;													// �����ѹ��λ��λ
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1VRRH = 0;													// �����ѹ��λ��λ
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1RDS = 10;//CMP_NEG_VREF;													// �����ѹֵ ��0.42V ��������0.1�� ��Ӧ4A������
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1VRHS = VRHS_SOURCE_SEL_VDD; 			// �ڲ������ѹ���ݵ�Դѡ��VDD
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	// �ڲ��ο���ѹʹ��
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS; // �رճ���
	 ACCESS_EN();	 ACMP->CP1CTL_b.C1NS = C0NS_NEG_INPUT_SEL_CVREF0;   // ��������ѡ��CVREF0
//	 ACCESS_EN();	 ACMP->CP1CTL_b.C1FLG = 1;												// �Ƚ�����־λ��� 
//	 ACCESS_EN();	 ACMP->CP1CTL_b.C1GCEN = 1;												// �Ƚ����ſعر�
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1INTS = INTS_RE;										// �����ش���
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1INTM = 0;             						// ���ж�
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1DFILT = 3;   											// �����˲���������3�����ڣ���Ӧ1.33us
	 ACCESS_EN();	 ACMP->CP1CFG |= (1<<19);				 										// �ر�32Ԥ��Ƶ
	 ACCESS_EN();	 ACMP->CP1CFG_b.C1CLKD = 31;   											// 32��Ƶ

 }
 void CMP2_Init()
{	
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2PS  = C2PS_INPUT_SEL_OPA_OUTPUT;	// �Ƚ���P���ź�ѡ���˷����
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2OPS = C2OPS_SEL_OP0O;							// �˷�����ź�ѡ��OPA3O
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2EN  = CMP_ENABLE;									// �Ƚ���ʹ��
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2VRRL = 0;													// �����ѹ��λ��λ
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2VRRH = 1;													// �����ѹ��λ��λ
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2RDS = 0;							// �����ѹֵ
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2VRHS = VRHS_SOURCE_SEL_VDD; 			// �ڲ������ѹ���ݵ�Դѡ��VDD
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2REFEN = REFEN_INTERN_REF_ENABLE; 	// �ڲ��ο���ѹʹ��
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2HYSEN = HYSEN_WITHOUT_HYSTERESIS; // �رճ���
	 ACCESS_EN();	 ACMP->CP2CTL_b.C2NS = C0NS_NEG_INPUT_SEL_CVREF0;   // ��������ѡ��CVREF0
//	 ACCESS_EN();	 ACMP->CP2CTL_b.C2FLG = 1;												// �Ƚ�����־λ��� 
//	 ACCESS_EN();	 ACMP->CP2CTL_b.C2GCEN = 1;												// �Ƚ����ſعر�
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2INTS = INTS_RE;										// �����ش���
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2INTM = 0;             		
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2DFILT = 3;   										// �����˲���������2�����ڣ���Ӧ3us
	 ACCESS_EN();	 ACMP->CP2CFG|=(1<<19);				 											// �ر�32Ԥ��Ƶ
	 ACCESS_EN();	 ACMP->CP2CFG_b.C2CLKD = 31;   											// 32��Ƶ

 }

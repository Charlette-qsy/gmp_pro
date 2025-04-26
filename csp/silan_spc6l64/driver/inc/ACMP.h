#ifndef __ACMP_H__
#define __ACMP_H__

#include "driver/inc/SLMCU.h"

/************************************************************
                         �Ƚ�������
************************************************************/

#define C0PS_INPUT_SEL_OPA_OUTPUT 0 // �Ƚ���0����ѡ��OPA������
#define C0PS_INPUT_SEL_CP00P_PIN  1 // �Ƚ���0����ѡ��CP00P�ܽ�����
#define C0PS_INPUT_SEL_CP01P_PIN  2 // �Ƚ���0����ѡ��CP01P�ܽ�����
#define C0PS_INPUT_SEL_CP02P_PIN  3 // �Ƚ���0����ѡ��CP02P�ܽ�����

#define C1PS_INPUT_SEL_OPA_OUTPUT 0 // �Ƚ���1����ѡ��OPA������
#define C1PS_INPUT_SEL_CP10P_PIN  1 // �Ƚ���1����ѡ��CP10P�ܽ�����
#define C1PS_INPUT_SEL_CP11P_PIN  2 // �Ƚ���1����ѡ��CP11P�ܽ�����
#define C1PS_INPUT_SEL_CP12P_PIN  3 // �Ƚ���1����ѡ��CP12P�ܽ�����

#define C2PS_INPUT_SEL_OPA_OUTPUT 0 // �Ƚ���2����ѡ��OPA������
#define C2PS_INPUT_SEL_CP20P_PIN  1 // �Ƚ���2����ѡ��CP20P�ܽ�����
#define C2PS_INPUT_SEL_CP21P_PIN  2 // �Ƚ���2����ѡ��CP21P�ܽ�����
#define C2PS_INPUT_SEL_CP22P_PIN  3 // �Ƚ���2����ѡ��CP22P�ܽ�����

#define C0OPS_SEL_OP0O            0 // �Ƚ���0����ѡ��OPA0������
#define C0OPS_SEL_OP1O            1 // �Ƚ���0����ѡ��OPA1������
#define C0OPS_SEL_OP2O            2 // �Ƚ���0����ѡ��OPA1������
#define C0OPS_SEL_OP3O            3 // �Ƚ���0����ѡ��OPA3������
#define C1OPS_SEL_OP0O            0 // �Ƚ���1����ѡ��OPA0������
#define C1OPS_SEL_OP1O            1 // �Ƚ���1����ѡ��OPA1������
#define C1OPS_SEL_OP2O            2 // �Ƚ���1����ѡ��OPA1������
#define C1OPS_SEL_OP3O            3 // �Ƚ���1����ѡ��OPA3������
#define C2OPS_SEL_OP0O            0 // �Ƚ���2����ѡ��OPA0������
#define C2OPS_SEL_OP1O            1 // �Ƚ���2����ѡ��OPA1������
#define C2OPS_SEL_OP2O            2 // �Ƚ���2����ѡ��OPA1������
#define C2OPS_SEL_OP3O            3 // �Ƚ���2����ѡ��OPA3������

#define CMP_ENABLE                1 // �Ƚ���ʹ��
#define CMP_DISABLE               0 // �Ƚ�����ֹ

#define VRHS_SOURCE_SEL_VDD       0 // �ڲ������ѹ���ݵ�Դѡ��VDD
#define VRHS_SOURCE_SEL_VTEST     1 // �ڲ������ѹ���ݵ�Դѡ��VTEST  1.5V

#define REFEN_INTERN_REF_ENABLE   1 // �ڲ��ο���ѹʹ��
#define REFEN_INTERN_REF_DISABLE  0 // �ڲ��ο���ѹ��ֹ

#define HYSEN_WITH_HYSTERESIS     1 // �г���
#define HYSEN_WITHOUT_HYSTERESIS  0 // �޳���

#define HYSEN_8MV                 0 // ����-8mV
#define HYSEN_16MV                1 // ����-16mV
#define HYSEN_32MV                2 // ����-32mV
#define HYSEN_110MV               3 // ����-110mV

#define C0NS_NEG_INPUT_SEL_CVREF0 0 // ��������ѡ��CVREF0
#define C0NS_NEG_INPUT_SEL_PIN    1 // ��������ѡ���ⲿ�ܽ�����
#define C0NS_NEG_INPUT_SEL_VSS    3 // ��������ѡ��VSS

#define INTS_DISABLE              0 // �ж�����ѡ�񣺽�ֹ
#define INTS_FE                   1 // �ж�����ѡ���½���
#define INTS_RE                   2 // �ж�����ѡ��������
#define INTS_FE_RE                3 // �ж�����ѡ�������غ��½���

#define INTM_INT_ENABLE           0 // �������ж�
#define INTM_INT_DISABLE          1 // �����ж�

extern void CMP0_Init(void);
extern void CMP1_Init(void);
extern void CMP2_Init(void);

#endif

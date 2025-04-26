#ifndef __OPA_H__
#define __OPA_H__

#include "driver/inc/SLMCU.h"

extern void OPA0_Init(void);
extern void OPA1_Init(void);

#define OPA_ENABLE                1; // �˷�ʹ��
#define OPA_DISABLE               0; // �˷Ž�ֹ
#define OPA_PS_ENABLE             1; // �ڲ�ƫ�ô�
#define OPA_PS_DISABLE            0; // �ڲ�ƫ�ùر�
#define OPA_FEEDBACK_LOOP_ENABLE  1; // �˷ŷ�����·ʹ��
#define OPA_FEEDBACK_LOOP_DISABLE 0; // �˷ŷ�����·��ֹ
#define OPA_OUTPUT_To_PIN_ENABLE  1; // �˷Ž��������ܽ�ʹ��
#define OPA_OUTPUT_To_PIN_DISABLE 0; // �˷Ž��������ܽŽ�ֹ

#define OPxGS_1x                  0; // OPA1/2/3�Ŵ�����Ϊ1
#define OPxGS_2x                  1; // OPA1/2/3�Ŵ�����Ϊ2
#define OPxGS_4x                  2; // OPA1/2/3�Ŵ�����Ϊ3
#define OPxGS_6x                  3; // OPA1/2/3�Ŵ�����Ϊ4
#define OPxGS_8x                  4; // OPA1/2/3�Ŵ�����Ϊ5
#define OPxGS_12x                 5; // OPA1/2/3�Ŵ�����Ϊ6
#define OPxGS_16x                 6; // OPA1/2/3�Ŵ�����Ϊ8
#define OPxGS_20x                 7; // OPA1/2/3�Ŵ�����Ϊ12
#define OPxPRS_RES_ENABLE         0; // OPA1/2/3����˵���ʹ��
#define OPxPRS_RES_SHORT          1; // OPA1/2/3����˵���̽�
#define OPxNRS_RES_ENABLE         0; // OPA1/2/3����˵���ʹ��
#define OPxNRS_RES_SHORT          1; // OPA1/2/3����˵���̽�

#endif

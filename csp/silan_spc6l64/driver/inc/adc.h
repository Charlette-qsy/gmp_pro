#ifndef __ADC_H__
#define __ADC_H__
#include "driver/inc/SLMCU.h"

#define ADC_CLKDIV_2  0  // 2��Ƶ
#define ADC_CLKDIV_3  1  // 3��Ƶ
#define ADC_CLKDIV_4  2  // 4��Ƶ
#define ADC_CLKDIV_5  3  // 5��Ƶ
#define ADC_CLKDIV_6  4  // 6��Ƶ
#define ADC_CLKDIV_8  5  // 8��Ƶ
#define ADC_CLKDIV_10 6  // 10��Ƶ
#define ADC_CLKDIV_12 7  // 12��Ƶ
#define ADC_CLKDIV_14 8  // 14��Ƶ
#define ADC_CLKDIV_16 9  // 16��Ƶ
#define ADC_CLKDIV_18 10 // 18��Ƶ
#define ADC_CLKDIV_20 11 // 20��Ƶ
#define ADC_CLKDIV_26 12 // 26��Ƶ
#define ADC_CLKDIV_32 13 // 32��Ƶ
#define ADC_CLKDIV_64 14 // 64��Ƶ

// #define ACCESS_EN() SYSCFG->ACCESSEN = 0x05fa659a										// �ر�д����
#define ADC_RESET                                                                                                      \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.RESET = 1; // ADCģ������
#define ADC_ENABLE                                                                                                     \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.EN = 1; // ADCģ��ʹ��
#define ADC_DISABLE                                                                                                    \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.EN = 0; // ADCģ���ֹ
#define ADC_NONOVERLAP                                                                                                 \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL2 |= (1 << 1); // ������ת�����ص�
#define ADC_OVERLAP                                                                                                    \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL2 &= ~(1 << 1);                      // ������ת���ص�
#define ADC_MODE2       ADC->ADCTRIM_b.mode2 = 1;   // ADCģʽ2
#define ADC_VOL_SEL_50V ADC->ADCTRIM_b.vol_sel = 1; // �ڲ���ѹ�ο�ѡ��5.0V
#define ADC_VOL_SEL_33V ADC->ADCTRIM_b.vol_sel = 0; // �ڲ���ѹ�ο�ѡ��3.3V
#define ADC_INT_AT_EOC                                                                                                 \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.INTPLSC = 1; // EOC��������ڷ������Ĵ���ǰ��һ������
#define ADC_INT_AT_SOC                                                                                                 \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.INTPLSC = 0; // EOC���������ת����ʼʱ
#define ADC_REF_INTERNAL                                                                                               \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.REFSEL = 0; // ADCʹ���ڲ��ο���ѹ
#define ADC_REF_EXT_VREF                                                                                               \
    ACCESS_EN();                                                                                                       \
    ADC->ADCCTL1_b.REFSEL = 1; // ADCʹ���ⲿ�ο���ѹ

extern void ADC_Init(void);

#endif

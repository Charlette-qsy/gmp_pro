
#ifndef _FILE_SILAN_CONFIG_H_
#define _FILE_SILAN_CONFIG_H_

// System config
#define SYS_CLK        72     // MHz,ϵͳʱ��  (�������޸�)
#define PWM_FREQUENCY  18     // PWM����Ƶ��(kHZ)	(���޸ģ��������鳬��30KHZ)
#define T0_FREQUENCY   1      // �⻷ִ��Ƶ��(kHZ)(�������޸�)
#define UART0_BAUDRATE 115200 // ���ڲ�����UART0
#define UART1_BAUDRATE 115200 // ���ڲ�����UART1

/*---------------------ʱ������м�ֵ���㣬����Ҫ�޸�--------------------------------*/
#define PWM_PERIOD  (SYS_CLK * 500 / PWM_FREQUENCY) //
#define TIM6_PERIOD (SYS_CLK * 1000 / T0_FREQUENCY) //
#define TPWM        (0.001 / PWM_FREQUENCY)         // PWM����ֵ (s)
#define TSP         (TPWM)                          // PWM����ֵ (s)
#define TS0         (0.001 / T0_FREQUENCY)          // T0����ֵ  (s)

/*-----------------------����ֵ,��λ��Ϊpu ������Ҫ�޸�------------------------------*/

#define UART0_IBRD (unsigned long)(SYS_CLK * 1000000 / (16 * UART0_BAUDRATE))
#define UART0_FBRD                                                                                                     \
    (unsigned long)((SYS_CLK * 1000000 % UART0_BAUDRATE >= (UART0_BAUDRATE >> 1))                                      \
                        ? (SYS_CLK * 1000000 / UART0_BAUDRATE - UART0_IBRD * 16 + 1)                                   \
                        : (SYS_CLK * 1000000 / UART0_BAUDRATE - UART0_IBRD * 16))

#define UART1_IBRD (unsigned long)(SYS_CLK * 1000000 / (16 * UART1_BAUDRATE))
#define UART1_FBRD                                                                                                     \
    (unsigned long)((SYS_CLK * 1000000 % UART1_BAUDRATE >= (UART1_BAUDRATE >> 1))                                      \
                        ? (SYS_CLK * 1000000 / UART1_BAUDRATE - UART1_IBRD * 16 + 1)                                   \
                        : (SYS_CLK * 1000000 / UART1_BAUDRATE - UART1_IBRD * 16))

//	ADC ת�����
#define ADC_CHANNEL_PEAK_CURRENT ADC->ADCRESULT[0] // ��ֵ����
#define ADC_CHANNEL_BEMF_U       ADC->ADCRESULT[1] // ������
#define ADC_CHANNEL_BEMF_V       ADC->ADCRESULT[2]
#define ADC_CHANNEL_BEMF_W       ADC->ADCRESULT[3]
#define ADC_CHANNEL_VDC          ADC->ADCRESULT[4] // ĸ�ߵ�ѹ
#define ADC_CHANNEL_IDC          ADC->ADCRESULT[5] // ĸ��ƽ������
#define ADC_CHANNEL_SPEED        ADC->ADCRESULT[6] // �ⲿ���Կ���
#define ADC_CHANNEL_NTC          ADC->ADCRESULT[7] // �¶ȼ��
#define ADC_CHANNEL_BATNTC       ADC->ADCRESULT[8] // 2.5Vƫ�ò���

#endif //_FILE_SILAN_CONFIG_H_

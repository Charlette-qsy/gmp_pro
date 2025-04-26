/*******************************************************************
    ���ļ�������UART����ͨѶ�����ݽṹ���Լ����ա�������
******************************************************************/

#ifndef __UART1_H__
#define __UART1_H__

#include "driver/inc/SLMCU.h"
#include "stdint.h"

#define UART_DEBUG         1
#define UART_SEND_BUF_SIZE 250
#define UART_REV_BUF_SIZE  100
#define UART_DATA_SIZE     50

#define UART_FUNC_RX       0
#define UART_FUNC_TX       1
#define UART_FUNC_DOUBLE   2

typedef struct
{
    uint8_t SendBuf[UART_SEND_BUF_SIZE]; // ���ڷ��ͻ���
    uint8_t RevBuf[UART_REV_BUF_SIZE];   // ���ڽ��ջ���

    uint8_t RevData[UART_DATA_SIZE]; // �������ݴ����

    uint16_t SBWriteIdx; // ���ͻ���д�����
    uint16_t SBReadIdx;  // ���ͻ����ȡ���
    uint16_t UnSendCnt;  // δ�����ֽ���

    uint8_t IntSendFlag; // ����æµ��־

    uint16_t RBWriteIdx; // ���ջ���д�����
    uint16_t RBReadIdx;  // ���ջ����ȡ���
    uint16_t UnRevCnt;   // δ��ȡ�ֽ���

    uint16_t RevStart; // ֡��ʼ��־
    uint16_t RevLen;   // ���յ�ַ������
    uint8_t RevOK;     // һָ֡�������ϱ�־
    uint8_t DataLen;   // ���ݳ���

} UART_PARAM_s;

extern UART_PARAM_s Uart0_S, Uart1_S, Uart2_S;
;

extern void UART_ISR_EN(UART0_Type *UARTx);
extern void UART_Model0_Config(UART0_Type *UARTx);
extern void UART_Model123_Config(UART0_Type *UARTx, uint8_t model, uint8_t dir);
extern void UART_Half_Duplex_Config(UART0_Type *UARTx, uint8_t dir);
extern void UartSendStart(UART_PARAM_s *v, UART0_Type *UARTx);
extern void UartSendByte(UART_PARAM_s *v, uint8_t byte);
extern void UartSendString(UART_PARAM_s *v, uint8_t *str);
extern void UartSentUint32ToASCII(UART_PARAM_s *v, uint32_t output);
extern void UartSentInt16ToASCII(UART_PARAM_s *v, uint16_t output);

#endif

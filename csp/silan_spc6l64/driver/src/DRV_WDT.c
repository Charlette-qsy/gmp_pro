#include "driver/inc/WDT.h"

void WWDT_Config(void)
{
    WWDT->CTRL_b.DIV = 0x06;      // 2^n��Ƶ 64��Ƶ
    WWDT->CTRL_b.WARNIEN = 0x00;  // Ԥ�����ܲ�ʹ��
    WWDT->CTRL_b.LOWLIMIT = 0x00; // ѡ��0Ϊ��������ֵ
    WWDT->CTRL_b.WARNSEL = 0x00;  // Ԥ��ֵΪ����ֵһ��
    WWDT->CTRL_b.DEBUG = 0x01;    // ����ģʽ��WDT��ͣ
    WWDT->RELOAD = 146250;        // 130ms	 ʱ��72/64=1.125M

    WWDT->CTRL_b.EN = 1; // ���Ź�ʹ��

    WWDT->FEED = 0x1ACCE551;
}

void WWDT_Clear(void)
{
    WWDT->FEED = 0x1ACCE551;
}

void IWDT_Config(void)
{
    CHIP_KEY_EN();
    CHIPCTRL->IWDTCFG_b.WINEN = 0; // ���ڹ�����Ч
    CHIP_KEY_EN();
    CHIPCTRL->IWDTCFG_b.WINSEL = 0; // 0,����ֵΪRLD  1,����ֵΪRLD/2ֵ

    CHIP_KEY_EN();
    CHIPCTRL->IWDTCLKDIV_b.CLKDIV = 0; // ʱ��Ԥ��Ƶ
    CHIP_KEY_EN();
    CHIPCTRL->IWDTRLD_b.RLD = 3200; // ������װ��ֵ 100ms��λ ʱ��32K

    CHIP_KEY_EN();
    CHIPCTRL->IWDTCTRL = 0X05FACCCC;
}

void IWDT_Clear(void)
{
    while (CHIPCTRL->IWDTSTATUS_b.UPDATING == 1)
        ;
    __disable_irq();
    CHIP_KEY_EN();
    CHIPCTRL->IWDTCTRL = 0X05FACCCC;
    __enable_irq();
}

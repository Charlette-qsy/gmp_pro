
#include "driver/inc/BT01.h"

uint8_t HallSection_R, HallSection_L;
uint32_t Hall_SectionTime[8] = {0};

void BT0_TimingMode_test()
{
    /***************BT00  1ms***********************/
    BT0->BT0MOD_b.T0M = 0;         // ��ʱ����ģʽ
    BT0->BT0MOD_b.CT0 = 0;         // ��ʱģʽ
    BT0->BT0MOD_b.CKS0 = 0;        // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC0 = 5;     // 64��Ƶ
    BT0->BT0DAT0_b.DATR0 = 0XFFFF; // 0XFFFF
    BT0->BT0CTL_b.INTE0 = 1;       // T0�ж�ʹ��

    /***************BT01 330us***********************/
    BT0->BT0MOD_b.T1M = 0;         // ��ʱ����ģʽ
    BT0->BT0MOD_b.CT1 = 0;         // ��ʱģʽ
    BT0->BT0MOD_b.CKS1 = 0;        // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC1 = 5;     // 64��Ƶ
    BT0->BT0DAT1_b.DATR1 = 0XFFFF; // 0XFFFF
    BT0->BT0CTL_b.INTE1 = 1;       // T1�ж�ʹ��

    BT0->BT0CFG_b.SHADOWEN = 0;

    /***************�ж�***********************/
    //	BT0->BT0CTL_b.TR0 = 1;//��ʱ��0����
}

void BT1_TimingMode_test()
{
    /***************BT10***********************/
    BT1->BT1MOD_b.T0M = 0;     // ��ʱ����ģʽ
    BT1->BT1MOD_b.CT0 = 0;     // ��ʱģʽ
    BT1->BT1MOD_b.CKS0 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC0 = 1; // 4��Ƶ
    BT1->BT1DAT0_b.DATR0 = 18000;
    BT1->BT1CTL_b.INTE0 = 1; // T0�ж�ʹ��

    /***************BT11***********************/
    BT1->BT1MOD_b.T1M = 0;     // ��ʱ����ģʽ
    BT1->BT1MOD_b.CT1 = 0;     // ��ʱģʽ
    BT1->BT1MOD_b.CKS1 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC1 = 1; // 4��Ƶ
    BT1->BT1DAT1_b.DATR1 = 18000;
    BT1->BT1CTL_b.INTE1 = 1; // T1�ж�ʹ��

/***************��ϳ�32λ��ʱ��(��Ӧ�ж�BT00)***********************/
#if (1)
    BT1->BT1CFG_b.BT32EN = 1;
    BT1->BT1DAT0 = 180000; // 10ms
    //	BT1->BT1DAT0_b.DATR0 = (0XFFFF & 120000);//10ms
    //	BT1->BT1DAT1_b.DATR1 = (120000>>16);

#endif
/***************�ֳ�����8λ��ʱ��***********************/
#if (0)
    BT1->BT1PSC_b.BT1PSC0 = 7; // 256��Ƶ(48M��Ƶ��187.5KHZ)
    BT1->BT1PSC_b.BT1PSC1 = 7; // 256��Ƶ
    BT1->BT1DAT0_b.DATR0 = 144;
    BT1->BT1DAT0_b.DATR0 |= (200 << 8);
    BT1->BT1DAT1_b.DATR1 = 72;
    BT1->BT1DAT1_b.DATR1 |= (36 << 8);

    BT1->BT1MOD_b.T0M = 3;    // �ֳ�����8λ������
    BT1->BT1MOD_b.T1M = 3;    // �ֳ�����8λ������
    BT1->BT1CTL_b.HINTE0 = 1; // T0�߰�λ�ж�ʹ��
    BT1->BT1CTL_b.HINTE1 = 1; // T1�߰�λ�ж�ʹ��

    BT1->BT1CTL_b.TRH0 = 1; // ��ʱ��0�߰�λ����
    BT1->BT1CTL_b.TRH1 = 1; // ��ʱ��1�߰�λ����
#endif

    /***************�ж�***********************/
    BT1->BT1CTL_b.TR0 = 1;
    BT1->BT1CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // ʹ��BT00_IRQn�ж�

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // ʹ��BT01_IRQn�ж�
}

void BT0_CountMode_test()
{
    /*******����ֵΪ�����ж�֮����������************/
    /***************BT00***********************/
    //	EXINT_Config(0,EXINT_PINSEL_PA05,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[0].PINSEL = 5;//ѡ��PA5
    //	EXINT->CFG_b[0].FILTA = 0;//�ر�ģ���˲�
    //	EXINT->CFG_b[0].DIV = 0;//�����˲�ʱ�ӷ�Ƶ
    //	EXINT->CFG_b[0].PSC = 0;//�����˲�����

    BT0->BT0MOD_b.T0M = 0;      // ��ʱ����ģʽ
    BT0->BT0MOD_b.CT0 = 1;      // ����ģʽ
    BT0->BT0CFG_b.EDGESEL0 = 1; // 0:�½��ش�����Ч 1:�����ش�����Ч

    BT0->BT0DAT0_b.DATR0 = 10;
    BT0->BT0CTL_b.INTE0 = 1; // T0�ж�ʹ��

    /***************BT01***********************/
    //	EXINT_Config(1,EXINT_PINSEL_PA06,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[1].PINSEL = 6;//ѡ��PA6
    //	EXINT->CFG_b[1].FILTA = 0;//�ر�ģ���˲�
    //	EXINT->CFG_b[1].DIV = 0;//�����˲�ʱ�ӷ�Ƶ
    //	EXINT->CFG_b[1].PSC = 0;//�����˲�����

    BT0->BT0MOD_b.T1M = 0;      // ��ʱ����ģʽ
    BT0->BT0MOD_b.CT1 = 1;      // ����ģʽ
    BT0->BT0CFG_b.EDGESEL1 = 0; // 0:�½��ش�����Ч 1:�����ش�����Ч

    BT0->BT0DAT1_b.DATR1 = 7;
    BT0->BT0CTL_b.INTE1 = 1; // T1�ж�ʹ��

    /***************�ж�***********************/
    BT0->BT0CTL_b.TR0 = 1;
    BT0->BT0CTL_b.TR1 = 1;
    NVIC_ClearPendingIRQ(BT00_IRQn);
    NVIC_SetPriority(BT00_IRQn, 0);
    NVIC_EnableIRQ(BT00_IRQn); // ʹ��BT00_IRQn�ж�

    NVIC_ClearPendingIRQ(BT01_IRQn);
    NVIC_SetPriority(BT01_IRQn, 0);
    NVIC_EnableIRQ(BT01_IRQn); // ʹ��BT01_IRQn�ж�
}

void BT1_CountMode_test()
{
    /***************BT10***********************/
    //	EXINT_Config(2,EXINT_PINSEL_PA05,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[2].PINSEL = 5;//ѡ��PA5
    //	EXINT->CFG_b[2].FILTA = 0;//�ر�ģ���˲�
    //	EXINT->CFG_b[2].DIV = 0;//�����˲�ʱ�ӷ�Ƶ
    //	EXINT->CFG_b[2].PSC = 0;//�����˲�����

    BT1->BT1MOD_b.T0M = 0;      // ��ʱ����ģʽ
    BT1->BT1MOD_b.CT0 = 1;      // ����ģʽ
    BT1->BT1CFG_b.EDGESEL0 = 1; // 0:�½��ش�����Ч 1:�����ش�����Ч

    BT1->BT1DAT0_b.DATR0 = 8;
    BT1->BT1CTL_b.INTE0 = 1; // T1�ж�ʹ��

    /***************BT11***********************/
    //	EXINT_Config(3,EXINT_PINSEL_PA06,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[3].PINSEL = 6;//ѡ��PA6
    //	EXINT->CFG_b[3].FILTA = 0;//�ر�ģ���˲�
    //	EXINT->CFG_b[3].DIV = 0;//�����˲�ʱ�ӷ�Ƶ
    //	EXINT->CFG_b[3].PSC = 0;//�����˲�����

    BT1->BT1MOD_b.T1M = 0;      // ��ʱ����ģʽ
    BT1->BT1MOD_b.CT1 = 1;      // ����ģʽ
    BT1->BT1CFG_b.EDGESEL1 = 0; // 0:�½��ش�����Ч 1:�����ش�����Ч

    BT1->BT1DAT1_b.DATR1 = 10;
    BT1->BT1CTL_b.INTE1 = 1; // T1�ж�ʹ��

    /***************�ж�***********************/
    BT1->BT1CTL_b.TR0 = 1;
    BT1->BT1CTL_b.TR1 = 1;
    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // ʹ��BT00_IRQn�ж�

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // ʹ��BT01_IRQn�ж�
}

void BT0_capture1_test(void)
{
/***************BT00***********************/
#if (1)
    EXINT_Config(0, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS0 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC0 = 0; // 2��Ƶ
    BT0->BT0MOD_b.T0M = 1;     // 1,����  2,�ߵ͵�ƽ
    BT0->BT0MOD_b.CT0 = 0;     // ��ʱ�򲶻�ģʽ

    BT0->BT0MOD_b.CAPEN0 = 1; // ʹ�ܲ���0

    BT0->BT0CTL_b.INTE0 = 1;    // T0�ж�ʹ��
    BT0->BT0CTL_b.OVFINTE0 = 1; // ��������ж�ʹ��

    BT0->BT0CFG_b.DOUEDGE0 = 0;  // 0,�����ƽ  1,����ռ�ձȺ�����
    BT0->BT0CFG_b.LEVELSEL0 = 1; // 0,����͵�ƽ  1,����ߵ�ƽ
#endif
/***************BT01***********************/
#if (0)
    EXINT_Config(1, EXINT_PINSEL_PA06, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS1 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC1 = 0; // 2��Ƶ
    BT0->BT0MOD_b.T1M = 1;     // 1,����  2,�ߵ͵�ƽ
    BT0->BT0MOD_b.CT1 = 0;     // ��ʱ�򲶻�ģʽ
    BT0->BT0PSC_b.BT0PSC2 = 0; // ��ʱ��T1 FLCLKԤ��Ƶ
    BT0->BT0MOD_b.CAPS1 = 0;   // 0:ѡ��Ϊ�ⲿ����TI1 1:FLCLK

    BT0->BT0MOD_b.CAPEN1 = 1; // ʹ�ܲ���1

    BT0->BT0CTL_b.INTE1 = 1; // T0�ж�ʹ��
    BT0->BT0CTL_b.OVFE1 = 1; // ��������ж�ʹ��

    BT0->BT0CFG_b.DOUEDGE1 = 0;  // 0,�����ƽ  1,����ռ�ձȺ�����
    BT0->BT0CFG_b.LEVELSEL1 = 1; // 0,����͵�ƽ  1,����ߵ�ƽ
#endif

/***************��ϳ�32λ��ʱ��(��Ӧ�ж�BT00)***********************/
#if (0)
    BT0->BT0CFG_b.BT32EN = 1;
#endif
    /***************�ж�***********************/
    BT0->BT0CTL_b.TR0 = 1;
    BT0->BT0CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT00_IRQn);
    NVIC_SetPriority(BT00_IRQn, 0);
    NVIC_EnableIRQ(BT00_IRQn); // ʹ��BT00_IRQn�ж�

    NVIC_ClearPendingIRQ(BT01_IRQn);
    NVIC_SetPriority(BT01_IRQn, 0);
    NVIC_EnableIRQ(BT01_IRQn); // ʹ��BT01_IRQn�ж�
}

void BT1_capture1_test(void)
{
/***************BT10***********************/
#if (0)
    EXINT_Config(2, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS0 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC0 = 0; // 2��Ƶ
    BT1->BT1MOD_b.T0M = 1;     // 1,����  2,�ߵ͵�ƽ
    BT1->BT1MOD_b.CT0 = 0;     // ��ʱ�򲶻�ģʽ

    BT1->BT1MOD_b.CAPEN0 = 1; // ʹ�ܲ���0

    BT1->BT1CTL_b.INTE0 = 1; // T0�ж�ʹ��
    BT1->BT1CTL_b.OVFE0 = 1; // ��������ж�ʹ��

    BT1->BT1CFG_b.DOUEDGE0 = 1;  // 0,�����ƽ  1,����ռ�ձȺ�����
    BT1->BT1CFG_b.LEVELSEL0 = 1; // 0,����͵�ƽ  1,����ߵ�ƽ
#endif
/***************BT11***********************/
#if (0)
    EXINT_Config(3, EXINT_PINSEL_PA06, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS1 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC1 = 0; // 2��Ƶ
    BT1->BT1MOD_b.T1M = 1;     // 1,����  2,�ߵ͵�ƽ
    BT1->BT1MOD_b.CT1 = 0;     // ��ʱ�򲶻�ģʽ
    BT1->BT1PSC_b.BT1PSC2 = 0; // ��ʱ��T1 FLCLKԤ��Ƶ
    BT1->BT1MOD_b.CAPS1 = 0;   // 0:ѡ��Ϊ�ⲿ����TI1 1:FLCLK

    BT1->BT1MOD_b.CAPEN1 = 1; // ʹ�ܲ���1

    BT1->BT1CTL_b.INTE1 = 1; // T0�ж�ʹ��
    BT1->BT1CTL_b.OVFE1 = 1; // ��������ж�ʹ��

    BT1->BT1CFG_b.DOUEDGE1 = 1;  // 0,�����ƽ  1,����ռ�ձȺ�����
    BT1->BT1CFG_b.LEVELSEL1 = 1; // 0,����͵�ƽ  1,����ߵ�ƽ
#endif

/***************��ϳ�32λ��ʱ��(��Ӧ�ж�BT10)***********************/
#if (0)
    BT1->BT1CFG_b.BT32EN = 1;
#endif
    /***************�ж�***********************/
    BT1->BT1CTL_b.TR0 = 1;
    BT1->BT1CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // ʹ��BT10_IRQn�ж�

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // ʹ��BT11_IRQn�ж�
}

void BT0_capture_test()
{
/***************BT00***********************/
#if (1)
    EXINT_Config(0, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS0 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC0 = 0; // 2��Ƶ
    BT0->BT0MOD_b.T0M = 2;     // ����ģʽ2
    BT0->BT0MOD_b.CT0 = 0;     // ��ʱ�򲶻�ģʽ

    BT0->BT0MOD_b.CAPEN0 = 1; // ʹ�ܲ���0

    BT0->BT0CTL_b.RINTE0 = 1;   // �������ж�ʹ��
    BT0->BT0CTL_b.FINTE0 = 1;   // �½����ж�ʹ��
    BT0->BT0CTL_b.OVFINTE0 = 1; // ��������ж�ʹ��

    BT0->BT0CFG_b.DOUEDGE0 = 1; // 0,�����ƽ  1,����ռ�ձȺ�����

#endif
/***************BT01***********************/
#if (0)
    EXINT_Config(1, EXINT_PINSEL_PA06, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS1 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC1 = 0; // 2��Ƶ
    BT0->BT0MOD_b.T1M = 2;     // ����ģʽ2
    BT0->BT0MOD_b.CT1 = 0;     // ��ʱ�򲶻�ģʽ
    BT0->BT0PSC_b.BT0PSC2 = 0; // ��ʱ��T1 FLCLKԤ��Ƶ
    BT0->BT0MOD_b.CAPS1 = 0;   // 0:ѡ��Ϊ�ⲿ����TI1 1:FLCLK

    BT0->BT0MOD_b.CAPEN1 = 1; // ʹ�ܲ���1

    BT0->BT0CTL_b.INTER1 = 1; // �������ж�ʹ��
    BT0->BT0CTL_b.INTEF1 = 1; // �½����ж�ʹ��
    BT0->BT0CTL_b.OVFE1 = 1;  // ��������ж�ʹ��

    BT0->BT0CFG_b.DOUEDGE1 = 1; // 0,�����ƽ  1,����ռ�ձȺ�����
#endif
/***************HALL����(��Ӧ�ж�BT00)*******************************/
#if (0)
    EXINT_Config(3, EXINT_PINSEL_PA08, EXINT_DIR0_TYPE0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    ACCESS_EN;
    BT0->BT0CFG_b.INSEL = 1; // T0��ʱ������ѡ��Ĵ��� 0��ѡ��BTI0, 1��ѡ��BTI0��BTI1��BTI2�����

    BT0->BT0CFG_b.BT32EN = 1;
#endif
/***************��ϳ�32λ��ʱ��(��Ӧ�ж�BT00)***********************/
#if (0)
    BT0->BT0CFG_b.BT32EN = 1;
#endif
    /***************�ж�***********************/
    BT0->BT0CTL_b.TR0 = 1;
    //	BT0->BT0CTL_b.TR1 = 1;
}
void BT1_capture_test()
{
/***************BT10***********************/
#if (0)
    EXINT_Config(2, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS0 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC0 = 0; // 2��Ƶ
    BT1->BT1MOD_b.T0M = 2;     // ����ģʽ2
    BT1->BT1MOD_b.CT0 = 0;     // ��ʱ�򲶻�ģʽ

    BT1->BT1MOD_b.CAPEN0 = 1; // ʹ�ܲ���0

    BT1->BT1CTL_b.INTER0 = 1; // �������ж�ʹ��
    BT1->BT1CTL_b.INTEF0 = 1; // �½����ж�ʹ��
    BT1->BT1CTL_b.OVFE0 = 1;  // ��������ж�ʹ��

    BT1->BT1CFG_b.DOUEDGE0 = 1; // 0,�����ƽ  1,����ռ�ձȺ�����

#endif
/***************BT11***********************/
#if (0)
    EXINT_Config(3, EXINT_PINSEL_PA06, EXINT_DIR0_TYPE0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS1 = 0;    // 0:ʱ��ԴΪϵͳʱ��fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC1 = 0; // 2��Ƶ
    BT1->BT1MOD_b.T1M = 2;     // ����ģʽ2
    BT1->BT1MOD_b.CT1 = 0;     // ��ʱ�򲶻�ģʽ
    BT1->BT1PSC_b.BT1PSC2 = 0; // ��ʱ��T1 FLCLKԤ��Ƶ
    BT1->BT1MOD_b.CAPS1 = 0;   // 0:ѡ��Ϊ�ⲿ����TI1 1:FLCLK

    BT1->BT1MOD_b.CAPEN1 = 1; // ʹ�ܲ���1

    BT1->BT1CTL_b.INTER1 = 1; // �������ж�ʹ��
    BT1->BT1CTL_b.INTEF1 = 1; // �½����ж�ʹ��
    BT1->BT1CTL_b.OVFE1 = 1;  // ��������ж�ʹ��

    BT1->BT1CFG_b.DOUEDGE1 = 1; // 0,�����ƽ  1,����ռ�ձȺ�����

#endif
/***************HALL����(��Ӧ�ж�BT00)*******************************/
#if (0)
    EXINT_Config(1, EXINT_PINSEL_PA08, EXINT_DIR0_TYPE0_INTNON, EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[1].PINSEL = 8;//ѡ��PA8
    //	EXINT->CFG_b[1].FILTA = 0;//�ر�ģ���˲�
    //	EXINT->CFG_b[1].DIV = 63;//�����˲�ʱ�ӷ�Ƶ
    //	EXINT->CFG_b[1].PSC = 0;//�����˲�����
    ACCESS_EN;
    BT1->BT1CFG_b.INSEL = 1; // T0��ʱ������ѡ��Ĵ��� 0��ѡ��BTI0, 1��ѡ��BTI0��BTI1��BTI2�����

    BT1->BT1CFG_b.BT32EN = 1;
#endif
/***************��ϳ�32λ��ʱ��(��Ӧ�ж�BT10)***********************/
#if (0)
    BT1->BT1CFG_b.BT32EN = 1;
#endif
    /***************�ж�***********************/
    BT1->BT1CTL_b.TR0 = 1;
    //	BT1->BT1CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // ʹ��BT10_IRQn�ж�

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // ʹ��BT11_IRQn�ж�
}

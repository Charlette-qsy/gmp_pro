#ifndef __SLMCU_H__
#define __SLMCU_H__


#include "SPC6Lxx.h" 

#define ACCESS_EN()			SYSCFG->ACCESSEN = 0x05fa659a 			// �ر�д����
#define CHIP_KEY_EN()		CHIPCTRL->CHIPKEY = 0x05fa659a

#endif

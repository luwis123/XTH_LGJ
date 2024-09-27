#ifndef __GUIFONT_CREATE_H
#define	__GUIFONT_CREATE_H

#include "GUI.h"
#include "stm32f4xx.h"

//����XBF����洢��λ�ã�
//FLASH���ļ�ϵͳ�����Ƽ��� 	USE_FLASH_FONT             	0 
//SD���ļ�ϵͳ����							USE_SDCARD_FONT							1
#define XBF_FONT_SOURCE				0

//���ٶ���죩�ֿ���FLASH�ķ��ļ�ϵͳ����ʹ��ǰ��Ҫ��FLASH�ض���ַ���������ļ�
#define USE_FLASH_FONT							0	
//���ٶ��еȣ��ֿ�洢��SD���ļ�ϵͳ���򣬵��ԱȽϷ��㣬ֱ��ʹ�ö������ӵ��Կ��������ļ�����
#define USE_SDCARD_FONT							1


/*֧�ֵ��ֿ�����*/
extern GUI_FONT     XBF_Font16;
extern GUI_FONT     XBF_Font24;
extern GUI_FONT     XBF_Font32;

void GUI_SetXBF(void);

#endif /* __GUIFONT_CREATE_H */

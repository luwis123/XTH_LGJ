#ifndef __MAINTASK_H
#define __MAINTASK_H

#include "GUI.h"
#include "TEXT.h"

void MainTask(void);
void Display_String(void);//�ı���ʾ
void Display_Num(void);//��ֵ��ʾ
void QR_Code_Drawing(const char *pText, int PixelSize, int EccLevel, int x0, int y0);
#endif /* __MAINTASK_H */

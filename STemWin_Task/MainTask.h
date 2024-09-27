#ifndef __MAINTASK_H
#define __MAINTASK_H

#include "GUI.h"
#include "TEXT.h"

void MainTask(void);
void Display_String(void);//文本显示
void Display_Num(void);//数值显示
void QR_Code_Drawing(const char *pText, int PixelSize, int EccLevel, int x0, int y0);
#endif /* __MAINTASK_H */

#ifndef __GUIFONT_CREATE_H
#define	__GUIFONT_CREATE_H

#include "GUI.h"
#include "stm32f4xx.h"

//设置XBF字体存储的位置：
//FLASH非文件系统区域（推荐） 	USE_FLASH_FONT             	0 
//SD卡文件系统区域							USE_SDCARD_FONT							1
#define XBF_FONT_SOURCE				0

//（速度最快）字库在FLASH的非文件系统区域，使用前需要往FLASH特定地址拷贝字体文件
#define USE_FLASH_FONT							0	
//（速度中等）字库存储在SD卡文件系统区域，调试比较方便，直接使用读卡器从电脑拷贝字体文件即可
#define USE_SDCARD_FONT							1


/*支持的字库类型*/
extern GUI_FONT     XBF_Font16;
extern GUI_FONT     XBF_Font24;
extern GUI_FONT     XBF_Font32;

void GUI_SetXBF(void);

#endif /* __GUIFONT_CREATE_H */

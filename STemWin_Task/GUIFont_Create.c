/**
  ******************************************************************************
  * @file    GUIFont_Create.c
  * @author  
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   XBF格式字体emwin函数接口
  ******************************************************************************

  *
  ******************************************************************************
  */
	
#include "spiflash/bsp_spiflash.h"
#include "GUIFont_Create.h"
//#include "ff.h"
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"


#include <string.h>
#include <stdlib.h>



/* 存储器初始化标志 */
//static uint8_t storage_init_flag = 0;

///* 字库结构体 */
//GUI_XBF_DATA 	XBF_XINSONGTI_18_Data;
//GUI_FONT     	FONT_XINSONGTI_18;

//GUI_XBF_DATA 	XBF_SIYUANHEITI_36_Data;
//GUI_FONT     	FONT_SIYUANHEITI_36;

/* 宋体16点阵定义 */
#define   XBF_FONT16_ADDR    0x00001000
GUI_XBF_DATA XBF_Data16;
GUI_FONT     XBF_Font16;
void         *Fontfile16;

/* 宋体24点阵定义 */
#define   XBF_FONT24_ADDR    0x0015BADE+0x00001000
GUI_XBF_DATA XBF_Data24;
GUI_FONT     XBF_Font24;
void         *Fontfile24;

/* 宋体32点阵定义 */
#define   XBF_FONT32_ADDR    0x003CEF64
GUI_XBF_DATA XBF_Data32;
GUI_FONT     XBF_Font32;
void         *Fontfile32;

//#define XBF_KAITI24_ADDR       0     //字库存放在SPI_FLash地址
//uint8_t tempbuf[256]={0};            /* 从SD卡读取数据的缓冲 */
//#define XBF_KAITI24_SIZE    (2020)   // kaiti24.xbf字库文件存占用扇区数(每个扇区为4096个字节)



///* 字库存储路径 */
//#if (XBF_FONT_SOURCE == USE_FLASH_FONT)

//	/* 资源烧录到的FLASH基地址（目录地址，需与烧录程序一致） */
//	#define RESOURCE_BASE_ADDR	 (1*4096)//(16*1024*1024)
//	/* 存储在FLASH中的资源目录大小 */
//	#define CATALOG_SIZE				(8*1024)

//	/* 字库目录信息类型 */
//	typedef struct 
//	{
//		char 	      name[40];  /* 资源的名字 */
//		uint32_t  	size;      /* 资源的大小 */ 
//		uint32_t 	  offset;    /* 资源相对于基地址的偏移 */
//	}CatalogTypeDef;
//	/* 资源文件名称 */
//	static const char FONT_XINSONGTI_18_ADDR[] = "xinsongti18.xbf";
//	static const char FONT_SIYUANHEITI_36_ADDR[] = "siyuanheiti36_2bpp.xbf";

//#elif (XBF_FONT_SOURCE == USE_SDCARD_FONT)

//	static const char FONT_STORAGE_ROOT_DIR[]  =   "0:";
//	static const char FONT_XINSONGTI_18_ADDR[] = 	 "0:/Font/新宋体18.xbf";
//	static const char FONT_SIYUANHEITI_36_ADDR[] = "0:/Font/思源黑体36_2bpp.xbf";

//#endif

///* 字库存储在文件系统时需要使用的变量 */
//#if (XBF_FONT_SOURCE == USE_SDCARD_FONT)
//	static FIL fnew;									/* file objects */
//	static FATFS fs;									/* Work area (file system object) for logical drives */
//	static FRESULT res; 
//	static UINT br;            				/* File R/W count */
//#endif

//#if (XBF_FONT_SOURCE == USE_FLASH_FONT)
///**
//  * @brief  从FLASH中的目录查找相应的资源位置
//  * @param  res_base 目录在FLASH中的基地址
//  * @param  res_name[in] 要查找的资源名字
//  * @retval -1表示找不到，其余值表示资源在FLASH中的基地址
//  */
//int GetResOffset(const char *res_name)
//{
//	int i,len;
//	CatalogTypeDef Catalog;
//	
//	len =strlen(res_name);
//	for(i=0;i<CATALOG_SIZE;i+=sizeof(CatalogTypeDef))
//	{
//		taskENTER_CRITICAL();//进入临界区
//		SPI_FLASH_BufferRead((uint8_t*)&Catalog,RESOURCE_BASE_ADDR+i,sizeof(CatalogTypeDef));
//    taskEXIT_CRITICAL();//退出临界区
//		
//		if(strncasecmp(Catalog.name,res_name,len)==0)
//		{
//			return Catalog.offset;
//		}
//	}
//	return -1;
//}
//#endif


/**
  * 函数功能: XBF字体的回调函数, 16点阵
  * 输入参数: Offset 地址偏移，Numbytes 需要读出的字节数，pVoid 指针变量，pBuffer 获取字体的点阵数据
  * 返 回 值: 0 表示成功 1 表示失败
  * 说    明: 无
  */
static int _cbGetData_Font16(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
//		if (storage_init_flag == 0)
//	{
//		/* 初始化SPI FLASH */
//		MX_SPIFlash_Init();
//		storage_init_flag = 1;
//	}
	SPI_FLASH_BufferRead(pBuffer,Offset+XBF_FONT16_ADDR,NumBytes);
 // printf("NumBytes=%d\n",NumBytes);
	return 0;
}

/**
  * 函数功能: XBF字体的回调函数, 24点阵
  * 输入参数: Offset 地址偏移，Numbytes 需要读出的字节数，pVoid 指针变量，pBuffer 获取字体的点阵数据
  * 返 回 值: 0 表示成功 1 表示失败
  * 说    明: 无
  */
static int _cbGetData_Font24(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer,Offset+XBF_FONT24_ADDR,NumBytes);
	return 0;
}

/**
  * 函数功能: XBF字体的回调函数, 32点阵
  * 输入参数: Offset 地址偏移，Numbytes 需要读出的字节数，pVoid 指针变量，pBuffer 获取字体的点阵数据
  * 返 回 值: 0 表示成功 1 表示失败
  * 说    明: 无
  */
static int _cbGetData_Font32(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer,Offset+XBF_FONT32_ADDR,NumBytes);
	return 0;
}

///**
//  * @brief  获取字体数据的回调函数
//  * @param  Offset：要读取的内容在XBF文件中的偏移位置
//  * @param  NumBytes：要读取的字节数
//	* @param  pVoid：自定义数据的指针
//  * @param  pBuffer：存储读取内容的指针
//  * @retval 0 成功, 1 失败
//  */
//static int _cb_FONT_XBF_GetData(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
//{
//#if (XBF_FONT_SOURCE == USE_FLASH_FONT)
//	int32_t FontOffset;
//	uint32_t FONT_BASE_ADDR;
//	
//	if (storage_init_flag == 0)
//	{
//		/* 初始化SPI FLASH */
//		MX_SPIFlash_Init();
//		storage_init_flag = 1;
//	}
//	
//	/* 从pVoid中获取字库在FLASH中的偏移量(pvoid的值在GUI_XBF_CreateFont中传入) */
//	FontOffset = GetResOffset(pVoid);
//	if(FontOffset == -1)
//	{
//		printf("无法在FLASH中找到字库文件\r\n");
//		while(1);
//	}
//	
//	/* 字库的实际地址=资源目录地址+字库相对于目录的偏移量 */
//	FONT_BASE_ADDR = RESOURCE_BASE_ADDR + FontOffset;
//	
//	/* 读取内容 */
//	SPI_FLASH_BufferRead(pBuffer,FONT_BASE_ADDR+Offset,NumBytes);
//	
//	return 0;
//	
//#elif (XBF_FONT_SOURCE == USE_SDCARD_FONT)
//	
//	if (storage_init_flag == 0)
//	{
//		/* 挂载sd卡文件系统 */
//		res = f_mount(&fs,FONT_STORAGE_ROOT_DIR,1);
//		storage_init_flag = 1;
//	}
//	
//	/* 从pVoid中获取字库的存储地址(pvoid的值在GUI_XBF_CreateFont中传入) */
//	res = f_open(&fnew , (char *)pVoid, FA_OPEN_EXISTING | FA_READ);

//	if (res == FR_OK) 
//	{
//		f_lseek (&fnew, Offset);/* 指针偏移 */
//		/* 读取内容 */
//		res = f_read( &fnew, pBuffer, NumBytes, &br );		 
//		f_close(&fnew);
//		return 0;  
//	}    
//	else
//	  return 1; 
//#endif
//}

void GUI_SetXBF(void) 
{
	/* 创建16点阵字体 */
	GUI_XBF_CreateFont(&XBF_Font16,        /* GUI_FONT类型变量     */
					 &XBF_Data16,          /* GUI_XBF_DATA类型变量 */
					 GUI_XBF_TYPE_PROP,    /* 字体类型             */
					 _cbGetData_Font16,         /* 回调函数             */
					 &Fontfile16);         /* 回调函数参数         */
	
	/* 创建24点阵字体 */
	GUI_XBF_CreateFont(&XBF_Font24,        /* GUI_FONT类型变量     */
					 &XBF_Data24,          /* GUI_XBF_DATA类型变量 */
					 GUI_XBF_TYPE_PROP,    /* 字体类型             */
					 _cbGetData_Font24,         /* 回调函数             */
					 &Fontfile24);         /* 回调函数参数         */
	
	/* 创建32点阵字体 */
	GUI_XBF_CreateFont(&XBF_Font32,        /* GUI_FONT类型变量     */
					 &XBF_Data32,          /* GUI_XBF_DATA类型变量 */
					 GUI_XBF_TYPE_PROP,    /* 字体类型             */
					 _cbGetData_Font32,         /* 回调函数             */
					 &Fontfile32);         /* 回调函数参数         */
}

///**
//  * @brief  创建XBF字体
//  * @param  无
//  * @retval 无
//  */
//void Create_XBF_Font(void) 
//{
//	/* 新宋体18 */
//	GUI_XBF_CreateFont(&FONT_XINSONGTI_18,              /* GUI_FONT 字体结构体指针 */
//					           &XBF_XINSONGTI_18_Data,          /* GUI_XBF_DATA 结构体指针 */
//					           GUI_XBF_TYPE_PROP_EXT,           /* 字体类型 */
//					           _cb_FONT_XBF_GetData,            /* 获取字体数据的回调函数 */
//					           (void *)&FONT_XINSONGTI_18_ADDR);/* 要传输给回调函数的自定义数据指针，此处传输字库的地址 */
//	/* 思源黑体36 */
//	GUI_XBF_CreateFont(&FONT_SIYUANHEITI_36,              /* GUI_FONT 字体结构体指针 */
//					           &XBF_SIYUANHEITI_36_Data,          /* GUI_XBF_DATA 结构体指针 */
//					           GUI_XBF_TYPE_PROP_AA2_EXT,           /* 字体类型 */
//					           _cb_FONT_XBF_GetData,            /* 获取字体数据的回调函数 */
//					           (void *)&FONT_SIYUANHEITI_36_ADDR);/* 要传输给回调函数的自定义数据指针，此处传输字库的地址 */
//}

/*********************************************END OF FILE**********************/

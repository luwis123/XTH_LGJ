/**
  ******************************************************************************
  * @file    GUIFont_Create.c
  * @author  
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   XBF��ʽ����emwin�����ӿ�
  ******************************************************************************

  *
  ******************************************************************************
  */
	
#include "spiflash/bsp_spiflash.h"
#include "GUIFont_Create.h"
//#include "ff.h"
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"


#include <string.h>
#include <stdlib.h>



/* �洢����ʼ����־ */
//static uint8_t storage_init_flag = 0;

///* �ֿ�ṹ�� */
//GUI_XBF_DATA 	XBF_XINSONGTI_18_Data;
//GUI_FONT     	FONT_XINSONGTI_18;

//GUI_XBF_DATA 	XBF_SIYUANHEITI_36_Data;
//GUI_FONT     	FONT_SIYUANHEITI_36;

/* ����16������ */
#define   XBF_FONT16_ADDR    0x00001000
GUI_XBF_DATA XBF_Data16;
GUI_FONT     XBF_Font16;
void         *Fontfile16;

/* ����24������ */
#define   XBF_FONT24_ADDR    0x0015BADE+0x00001000
GUI_XBF_DATA XBF_Data24;
GUI_FONT     XBF_Font24;
void         *Fontfile24;

/* ����32������ */
#define   XBF_FONT32_ADDR    0x003CEF64
GUI_XBF_DATA XBF_Data32;
GUI_FONT     XBF_Font32;
void         *Fontfile32;

//#define XBF_KAITI24_ADDR       0     //�ֿ�����SPI_FLash��ַ
//uint8_t tempbuf[256]={0};            /* ��SD����ȡ���ݵĻ��� */
//#define XBF_KAITI24_SIZE    (2020)   // kaiti24.xbf�ֿ��ļ���ռ��������(ÿ������Ϊ4096���ֽ�)



///* �ֿ�洢·�� */
//#if (XBF_FONT_SOURCE == USE_FLASH_FONT)

//	/* ��Դ��¼����FLASH����ַ��Ŀ¼��ַ��������¼����һ�£� */
//	#define RESOURCE_BASE_ADDR	 (1*4096)//(16*1024*1024)
//	/* �洢��FLASH�е���ԴĿ¼��С */
//	#define CATALOG_SIZE				(8*1024)

//	/* �ֿ�Ŀ¼��Ϣ���� */
//	typedef struct 
//	{
//		char 	      name[40];  /* ��Դ������ */
//		uint32_t  	size;      /* ��Դ�Ĵ�С */ 
//		uint32_t 	  offset;    /* ��Դ����ڻ���ַ��ƫ�� */
//	}CatalogTypeDef;
//	/* ��Դ�ļ����� */
//	static const char FONT_XINSONGTI_18_ADDR[] = "xinsongti18.xbf";
//	static const char FONT_SIYUANHEITI_36_ADDR[] = "siyuanheiti36_2bpp.xbf";

//#elif (XBF_FONT_SOURCE == USE_SDCARD_FONT)

//	static const char FONT_STORAGE_ROOT_DIR[]  =   "0:";
//	static const char FONT_XINSONGTI_18_ADDR[] = 	 "0:/Font/������18.xbf";
//	static const char FONT_SIYUANHEITI_36_ADDR[] = "0:/Font/˼Դ����36_2bpp.xbf";

//#endif

///* �ֿ�洢���ļ�ϵͳʱ��Ҫʹ�õı��� */
//#if (XBF_FONT_SOURCE == USE_SDCARD_FONT)
//	static FIL fnew;									/* file objects */
//	static FATFS fs;									/* Work area (file system object) for logical drives */
//	static FRESULT res; 
//	static UINT br;            				/* File R/W count */
//#endif

//#if (XBF_FONT_SOURCE == USE_FLASH_FONT)
///**
//  * @brief  ��FLASH�е�Ŀ¼������Ӧ����Դλ��
//  * @param  res_base Ŀ¼��FLASH�еĻ���ַ
//  * @param  res_name[in] Ҫ���ҵ���Դ����
//  * @retval -1��ʾ�Ҳ���������ֵ��ʾ��Դ��FLASH�еĻ���ַ
//  */
//int GetResOffset(const char *res_name)
//{
//	int i,len;
//	CatalogTypeDef Catalog;
//	
//	len =strlen(res_name);
//	for(i=0;i<CATALOG_SIZE;i+=sizeof(CatalogTypeDef))
//	{
//		taskENTER_CRITICAL();//�����ٽ���
//		SPI_FLASH_BufferRead((uint8_t*)&Catalog,RESOURCE_BASE_ADDR+i,sizeof(CatalogTypeDef));
//    taskEXIT_CRITICAL();//�˳��ٽ���
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
  * ��������: XBF����Ļص�����, 16����
  * �������: Offset ��ַƫ�ƣ�Numbytes ��Ҫ�������ֽ�����pVoid ָ�������pBuffer ��ȡ����ĵ�������
  * �� �� ֵ: 0 ��ʾ�ɹ� 1 ��ʾʧ��
  * ˵    ��: ��
  */
static int _cbGetData_Font16(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
//		if (storage_init_flag == 0)
//	{
//		/* ��ʼ��SPI FLASH */
//		MX_SPIFlash_Init();
//		storage_init_flag = 1;
//	}
	SPI_FLASH_BufferRead(pBuffer,Offset+XBF_FONT16_ADDR,NumBytes);
 // printf("NumBytes=%d\n",NumBytes);
	return 0;
}

/**
  * ��������: XBF����Ļص�����, 24����
  * �������: Offset ��ַƫ�ƣ�Numbytes ��Ҫ�������ֽ�����pVoid ָ�������pBuffer ��ȡ����ĵ�������
  * �� �� ֵ: 0 ��ʾ�ɹ� 1 ��ʾʧ��
  * ˵    ��: ��
  */
static int _cbGetData_Font24(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer,Offset+XBF_FONT24_ADDR,NumBytes);
	return 0;
}

/**
  * ��������: XBF����Ļص�����, 32����
  * �������: Offset ��ַƫ�ƣ�Numbytes ��Ҫ�������ֽ�����pVoid ָ�������pBuffer ��ȡ����ĵ�������
  * �� �� ֵ: 0 ��ʾ�ɹ� 1 ��ʾʧ��
  * ˵    ��: ��
  */
static int _cbGetData_Font32(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer,Offset+XBF_FONT32_ADDR,NumBytes);
	return 0;
}

///**
//  * @brief  ��ȡ�������ݵĻص�����
//  * @param  Offset��Ҫ��ȡ��������XBF�ļ��е�ƫ��λ��
//  * @param  NumBytes��Ҫ��ȡ���ֽ���
//	* @param  pVoid���Զ������ݵ�ָ��
//  * @param  pBuffer���洢��ȡ���ݵ�ָ��
//  * @retval 0 �ɹ�, 1 ʧ��
//  */
//static int _cb_FONT_XBF_GetData(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
//{
//#if (XBF_FONT_SOURCE == USE_FLASH_FONT)
//	int32_t FontOffset;
//	uint32_t FONT_BASE_ADDR;
//	
//	if (storage_init_flag == 0)
//	{
//		/* ��ʼ��SPI FLASH */
//		MX_SPIFlash_Init();
//		storage_init_flag = 1;
//	}
//	
//	/* ��pVoid�л�ȡ�ֿ���FLASH�е�ƫ����(pvoid��ֵ��GUI_XBF_CreateFont�д���) */
//	FontOffset = GetResOffset(pVoid);
//	if(FontOffset == -1)
//	{
//		printf("�޷���FLASH���ҵ��ֿ��ļ�\r\n");
//		while(1);
//	}
//	
//	/* �ֿ��ʵ�ʵ�ַ=��ԴĿ¼��ַ+�ֿ������Ŀ¼��ƫ���� */
//	FONT_BASE_ADDR = RESOURCE_BASE_ADDR + FontOffset;
//	
//	/* ��ȡ���� */
//	SPI_FLASH_BufferRead(pBuffer,FONT_BASE_ADDR+Offset,NumBytes);
//	
//	return 0;
//	
//#elif (XBF_FONT_SOURCE == USE_SDCARD_FONT)
//	
//	if (storage_init_flag == 0)
//	{
//		/* ����sd���ļ�ϵͳ */
//		res = f_mount(&fs,FONT_STORAGE_ROOT_DIR,1);
//		storage_init_flag = 1;
//	}
//	
//	/* ��pVoid�л�ȡ�ֿ�Ĵ洢��ַ(pvoid��ֵ��GUI_XBF_CreateFont�д���) */
//	res = f_open(&fnew , (char *)pVoid, FA_OPEN_EXISTING | FA_READ);

//	if (res == FR_OK) 
//	{
//		f_lseek (&fnew, Offset);/* ָ��ƫ�� */
//		/* ��ȡ���� */
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
	/* ����16�������� */
	GUI_XBF_CreateFont(&XBF_Font16,        /* GUI_FONT���ͱ���     */
					 &XBF_Data16,          /* GUI_XBF_DATA���ͱ��� */
					 GUI_XBF_TYPE_PROP,    /* ��������             */
					 _cbGetData_Font16,         /* �ص�����             */
					 &Fontfile16);         /* �ص���������         */
	
	/* ����24�������� */
	GUI_XBF_CreateFont(&XBF_Font24,        /* GUI_FONT���ͱ���     */
					 &XBF_Data24,          /* GUI_XBF_DATA���ͱ��� */
					 GUI_XBF_TYPE_PROP,    /* ��������             */
					 _cbGetData_Font24,         /* �ص�����             */
					 &Fontfile24);         /* �ص���������         */
	
	/* ����32�������� */
	GUI_XBF_CreateFont(&XBF_Font32,        /* GUI_FONT���ͱ���     */
					 &XBF_Data32,          /* GUI_XBF_DATA���ͱ��� */
					 GUI_XBF_TYPE_PROP,    /* ��������             */
					 _cbGetData_Font32,         /* �ص�����             */
					 &Fontfile32);         /* �ص���������         */
}

///**
//  * @brief  ����XBF����
//  * @param  ��
//  * @retval ��
//  */
//void Create_XBF_Font(void) 
//{
//	/* ������18 */
//	GUI_XBF_CreateFont(&FONT_XINSONGTI_18,              /* GUI_FONT ����ṹ��ָ�� */
//					           &XBF_XINSONGTI_18_Data,          /* GUI_XBF_DATA �ṹ��ָ�� */
//					           GUI_XBF_TYPE_PROP_EXT,           /* �������� */
//					           _cb_FONT_XBF_GetData,            /* ��ȡ�������ݵĻص����� */
//					           (void *)&FONT_XINSONGTI_18_ADDR);/* Ҫ������ص��������Զ�������ָ�룬�˴������ֿ�ĵ�ַ */
//	/* ˼Դ����36 */
//	GUI_XBF_CreateFont(&FONT_SIYUANHEITI_36,              /* GUI_FONT ����ṹ��ָ�� */
//					           &XBF_SIYUANHEITI_36_Data,          /* GUI_XBF_DATA �ṹ��ָ�� */
//					           GUI_XBF_TYPE_PROP_AA2_EXT,           /* �������� */
//					           _cb_FONT_XBF_GetData,            /* ��ȡ�������ݵĻص����� */
//					           (void *)&FONT_SIYUANHEITI_36_ADDR);/* Ҫ������ص��������Զ�������ָ�룬�˴������ֿ�ĵ�ַ */
//}

/*********************************************END OF FILE**********************/

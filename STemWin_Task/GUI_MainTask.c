/**
  *********************************************************************
  * @file    MainTask.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   FreeRTOS v9.0.0 + STM32 工程模版
  *********************************************************************
  ******************************************************************************
  */
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
/*******************************************************************************
 * 包含的头文件
 ******************************************************************************/
#include "MainTask.h"
#include "GUIFont_Create.h"
#include "ICONVIEW.h"
#include "GUIFont_Create.h"
#include "led/bsp_led.h"
#include <string.h>

extern WM_HWIN Create_Homepage_Framewin(void);
//位图显示
//extern GUI_CONST_STORAGE GUI_BITMAP bm123;
/*******************************************************************************
 * 全局变量
 ******************************************************************************/
 
///* 回调函数 */
//static WM_CALLBACK * _cbBkWindowOld;

///* 句柄*/
//static WM_HWIN _hWindow1;
//static WM_HWIN _hWindow2;

///* 颜色 */
//static GUI_COLOR _WindowColor1 = GUI_GREEN;
//static GUI_COLOR _FrameColor1  = GUI_GREEN;
//static GUI_COLOR _WindowColor2 = GUI_RED;
//static GUI_COLOR _FrameColor2  = GUI_RED;

///* 自定义消息ID */
//#define MSG_CHANGE_TEXT (WM_USER + 0)
// /* 文本缓冲去 */
//static char _acInfoText[40];
// 
// 
// 
// 
// GUI_RECT BasicRect = {0, 0, 50, 50};
// 
// 
//char acText[] = "This example demostrates text wrapping";
//GUI_RECT rect = {10, 150, 75, 270};
//GUI_WRAPMODE aWm[] = {GUI_WRAPMODE_NONE, GUI_WRAPMODE_CHAR, GUI_WRAPMODE_WORD};

//static const char QR_TEXT[] = "http://www.xitaihua.com.cn";

//static const GUI_POINT _aPointArrow[] = {
//  {  0,   0 },
//  {-20, -15 },
//  {-5 , -10 },
//  {-5 , -35 },
//  { 5 , -35 },
//  { 5 , -10 },
//  { 20, -15 },
//};

///* 起始坐标 */
//#define X_START 60
//#define Y_START 5

//typedef struct {
//  int NumBars;

//  GUI_COLOR Color;
//  const char * s;
//} BAR_DATA;

//static const BAR_DATA _aBarData[] = {
//  { 2, GUI_RED    , "Red" },
//  { 2, GUI_GREEN  , "Green" },
//  { 2, GUI_BLUE   , "Blue" },
//  { 1, GUI_WHITE  , "Grey" },
//  { 2, GUI_YELLOW , "Yellow" },
//  { 2, GUI_CYAN   , "Cyan" },
//  { 2, GUI_MAGENTA, "Magenta" },
//};

//static const GUI_COLOR _aColorStart[] = { GUI_BLACK, GUI_WHITE };

///*******************************************************************************
// * 文本显示
// ******************************************************************************/
//void Display_String(void)
//{
//	U8 i;
//	
////	/* 设置背景色 */
////	GUI_SetBkColor(GUI_GREEN);	
////	GUI_Clear();
//	
////	/* 开启光标 */
////	GUI_CURSOR_Show();
//	
//	/* 设置字体大小 */
//	GUI_SetFont(GUI_FONT_32_1);
//	GUI_DispStringAt("STemWIN", 10, 10);
//	
//	/* 画线 */
//	GUI_SetPenSize(8);
//	GUI_SetColor(GUI_RED);
//	GUI_DrawLine(10, 40, 230, 120);
//	GUI_DrawLine(10, 120, 230, 40);
//	
//	/* 绘制文本 */
//	GUI_SetBkColor(GUI_BLACK);
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetFont(GUI_FONT_16B_ASCII);
//	/* 正常模式 */
//	GUI_SetTextMode(GUI_TM_NORMAL);
//	GUI_DispStringHCenterAt("GUI_TM_NORMAL" , 120, 40);
//	/* 反转显示 */
//	GUI_SetTextMode(GUI_TM_REV);
//	GUI_DispStringHCenterAt("GUI_TM_REV" , 120, 40 + 16);
//	/* 透明文本 */
//	GUI_SetTextMode(GUI_TM_TRANS);
//	GUI_DispStringHCenterAt("GUI_TM_TRANS" , 120, 40 + 16 * 2);
//	/* 异或文本 */
//	GUI_SetTextMode(GUI_TM_XOR);
//	GUI_DispStringHCenterAt("GUI_TM_XOR" , 120, 40 + 16 * 3);
//	/* 透明反转文本 */
//	GUI_SetTextMode(GUI_TM_TRANS | GUI_TM_REV);
//	GUI_DispStringHCenterAt("GUI_TM_TRANS | GUI_TM_REV", 120, 40 + 16 * 4);
//	
//	/* 在矩形区域内显示文本 */
//	GUI_SetFont(GUI_FONT_16B_ASCII);
//	GUI_SetTextMode(GUI_TM_TRANS);
//	for(i = 0;i < 3;i++)
//	{
//		GUI_SetColor(GUI_WHITE);
//		GUI_FillRectEx(&rect);
//		GUI_SetColor(GUI_RED);
//		GUI_DispStringInRectWrap(acText, &rect, GUI_TA_LEFT, aWm[i]);
//		rect.x0 += 75;
//		rect.x1 += 75;
//	}
//}
///*******************************************************************************
// * 数值显示
// ******************************************************************************/
///**
//  * @brief 十进制数显示
//  * @note 无
//  * @param 无
//  * @retval 无
//  */
//static void Disp_DecNum(void)
//{
//	GUI_SetFont(GUI_FONT_24B_ASCII);
//	GUI_SetColor(GUI_WHITE);
//	
//	GUI_DispStringAt("GUI_DispDec():", 0, 0);
//	GUI_DispNextLine();
//	GUI_DispDec(12345, 6);
//	GUI_GotoX(12 * 9);
//	GUI_DispDec(-12345, 6);
//	
//	GUI_DispStringAt("GUI_DispDecAt():", 0, 24 * 2);
//	GUI_DispDecAt(12345, 0, 24 * 3, 6);
//	GUI_DispDecAt(-12345, 12 * 9, 24 * 3, 6);
//	
//	GUI_DispStringAt("GUI_DispDecMin():", 0, 24 * 4);
//	GUI_DispNextLine();
//	GUI_DispDecMin(12345);
//	GUI_GotoX(12 * 9);
//	GUI_DispDecMin(-12345);
//	
//	GUI_DispStringAt("GUI_DispDecShift():", 0, 24 * 6);
//	GUI_DispNextLine();
//	GUI_DispDecShift(12345, 7, 2);
//	GUI_GotoX(12 * 9);
//	GUI_DispDecShift(-12345, 7, 2);
//	
//	GUI_DispStringAt("GUI_DispDecSpace():", 0, 24 * 8);
//	GUI_DispNextLine();
//	GUI_DispDecSpace(12345, 6);
////	GUI_GotoX(12 * 9);
////	GUI_DispDecSpace(-12345, 7);

//  GUI_DispStringAt("GUI_DispSDec():", 0, 24 * 10);
//	GUI_DispNextLine();
//	GUI_DispSDec(12345,6);
//	
//	GUI_DispStringAt("GUI_DispSDecShift():", 0, 24 * 12);
//	GUI_DispNextLine();
//	GUI_DispSDecShift(12345, 7, 2);
//}

///**
//  * @brief 浮点数显示
//  * @note 无
//  * @param 无
//  * @retval 无
//  */
//static void Disp_FloatingNum(void)
//{
//	int x0 = 230;
//	
//	GUI_SetFont(GUI_FONT_24B_ASCII);
//	GUI_SetColor(GUI_WHITE);
//	
//	GUI_GotoX(x0);
//	GUI_DispStringAt("GUI_DispFloat():", x0, 0);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispFloat(123.4567, 9);
//	GUI_GotoX(x0 + 12 * 12);
//	GUI_DispFloat(-123.4567, 9);
//	
//	GUI_DispStringAt("GUI_DispFloatFix():", x0, 24 * 2);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispFloatFix(123.4567, 9, 3);
//	GUI_GotoX(x0 + 12 * 12);
//	GUI_DispFloatFix(-123.4567, 9, 3);
//	
//	GUI_DispStringAt("GUI_DispFloatMin():", x0, 24 * 4);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispFloatMin(123.4567, 3);
//	GUI_GotoX(x0 + 12 * 12);
//	GUI_DispFloatMin(-123.4567, 3);
//	
//	GUI_DispStringAt("GUI_DispSFloatFix():", x0, 24 * 6);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispSFloatFix(123.4567, 9, 3);
//	GUI_GotoX(x0 + 12 * 12);
//	GUI_DispSFloatFix(-123.4567, 9, 3);
//	
//	GUI_DispStringAt("GUI_DispSFloatMin():", x0, 24 * 8);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispSFloatMin(123.4567, 3);
//	GUI_GotoX(x0 + 12 * 12);
//	GUI_DispSFloatMin(-123.4567, 3);
//}

///**
//  * @brief 二进制数和十六进制数显示
//  * @note 无
//  * @param 无
//  * @retval 无
//  */
//static void Disp_BinHexNum(void)
//{
//	int x0 = 0;
//	
//	GUI_SetFont(GUI_FONT_24B_ASCII);
//	GUI_SetColor(GUI_WHITE);
//	
//	GUI_DispStringAt("GUI_DispBin():", x0, 24 * 16);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispBin(10, 8);
//	
//	GUI_DispStringAt("GUI_DispBinAt():", x0, 24 * 18);
//	GUI_DispBinAt(10, x0, 24 * 19, 8);
//	
//	GUI_DispStringAt("GUI_DispHex():", x0, 24 * 20);
//	GUI_DispNextLine();
//	GUI_GotoX(x0);
//	GUI_DispHex(4779, 4);
//	
//	GUI_DispStringAt("GUI_DispHexAt():", x0, 24 * 22);
//	GUI_DispNextLine();
//	GUI_DispHexAt(4779, x0, 24 * 23, 4);
//	
//	GUI_DispStringAt("GUI_GetVersionString()", x0, 24 * 24);
//	GUI_DispStringAt(GUI_GetVersionString(), x0, 24 * 25);
//}

/**
  * @brief 二维码生成
  * @note 无
  * @param pText：二维码内容
  *        PixelSize：二维码数据色块的大小，单位：像素
  *        EccLevel：纠错编码级别
  *        x0：二维码图像在LCD的坐标x
  *        y0：二维码图像在LCD的坐标y
  * @retval 无
  */
	void QR_Code_Drawing(const char *pText, int PixelSize, int EccLevel, int x0, int y0)
{
	GUI_HMEM hQR;
	
	/* 创建二维码对象 */
	hQR = GUI_QR_Create(pText, PixelSize, EccLevel, 0);
	/* 绘制二维码到LCD */
	GUI_QR_Draw(hQR, x0, y0);
	/* 删除二维码对象 */
	GUI_QR_Delete(hQR);
}

///**
//  * @brief 2D绘图函数
//  * @note 无
//  * @param 无
//  * @retval 无
//  */
//static void _2D_Graph_Drawing(void)
//{
////		/* 绘制各种矩形 */
////	GUI_SetColor(GUI_GREEN);
////	GUI_DrawRectEx(&BasicRect);
////	BasicRect.x0+=30;
////	BasicRect.x1+=30;
////	GUI_SetColor(GUI_RED);
////	GUI_FillRectEx(&BasicRect);
////	GUI_DrawRoundedRect(0,60,100,100,5);
////	GUI_DrawRoundedFrame(110,100,200,200,5,5);
////	GUI_FillRoundedRect(190, 10, 230, 50, 5);
////	GUI_DrawGradientRoundedH(10, 55, 50, 95, 5,0xff0000,0x00ffff);
////	GUI_DrawGradientRoundedV(55, 55, 95, 95, 5, GUI_LIGHTMAGENTA, GUI_LIGHTCYAN);

////	/* 绘制线条 */
////	GUI_SetPenSize(5);
////  GUI_SetColor(GUI_RED);
////	//GUI_SetLineStyle(GUI_LS_DASH);
////	GUI_DrawLine(200, 55, 380, 95);
////	
////		/* 绘制多边形 */
////	GUI_SetColor(GUI_RED);
////	
////	GUI_FillPolygon(_aPointArrow, 5, 210,100);
//	
///* 绘制二维码 */
//	QR_Code_Drawing(QR_TEXT, 3, GUI_QR_ECLEVEL_L, 200, 100);
//	
//	GUI_SetFont(GUI_FONT_32_1);
//	GUI_SetTextMode(GUI_TM_TRANS);
//	GUI_SetColor(GUI_RED);
//	GUI_DispStringHCenterAt("anhuixitiahua0551-67953897", 240, 180);
//}

////static void ShowBitmap(void)  //显示位图
////{
////	GUI_DrawBitmap(&bm123, 0, 0);
////}

//static void ShowColor(void)
//{
//	GUI_RECT Rect;
//		U8 i;
//	U8 j;
//		U16     yStep;
//		U16     xSize;
//  	U16    ySize;
//	  U8      NumColors;
//		U8      NumBars;
//		xSize = LCD_GetXSize();
//	  ySize = LCD_GetYSize();
//	/* 可以显示的色条数 */
//	  NumColors = GUI_COUNTOF(_aBarData);//查询目标所含有元素个数
//	for (i = NumBars = 0, NumBars = 0; i < NumColors; i++) 
//	{
//		NumBars += _aBarData[i].NumBars;
//	}
//		yStep = (ySize - Y_START) / NumBars;
//	/* 显示文本 */
//	Rect.x0 = 0;
//	Rect.x1 = X_START - 1;
//	Rect.y0 = Y_START;
//	GUI_SetFont(&GUI_Font16B_ASCII);
//	for (i = 0; i < NumColors; i++) 
//	{
//		Rect.y1 = Rect.y0 + yStep * _aBarData[i].NumBars - 1;
//		GUI_DispStringInRect(_aBarData[i].s, &Rect, GUI_TA_LEFT | GUI_TA_VCENTER);
//		Rect.y0 = Rect.y1 + 1;
//	}
//	 /* 绘制色条 */
//	Rect.x0 = X_START;
//	Rect.x1 = xSize - 1;
//	Rect.y0 = Y_START;
//	for (i = 0; i < NumColors; i++) 
//	{
//		for (j = 0; j < _aBarData[i].NumBars; j++) 
//		{
//			Rect.y1 = Rect.y0 + yStep - 1;
//			GUI_DrawGradientH(Rect.x0, Rect.y0, Rect.x1, Rect.y1, _aColorStart[j], _aBarData[i].Color);
//			Rect.y0 = Rect.y1 + 1;
//		}
//	}
//}

////内存设备
//static void _Draw(int x0, int y0, int x1, int y1, int i)
//{
//  char buf[] = {0};

//  /* 绘制矩形背景 */
//  GUI_SetColor(GUI_BLUE);
//	GUI_FillRect(x0, y0, x1, y1);
//  
//  /* 绘制文本 */
//	GUI_SetFont(GUI_FONT_D64);
//  GUI_SetTextMode(GUI_TEXTMODE_XOR);
//  sprintf(buf, "%d", i);
//	GUI_DispStringHCenterAt(buf, x0 + (x1 - x0)/2, (y0 + (y1 - y0)/2) - 32);
//}

///* 创建内存设备 */
//GUI_MEMDEV_Handle hMem = 0;

//static void _DemoMemDev(void)
//{


//	
//	/* 设置背景色 */
//  GUI_SetBkColor(GUI_BLACK);
//  GUI_Clear();
//	
//	/* 显示提示文字 */
//  GUI_SetColor(GUI_WHITE);
//	GUI_SetFont(GUI_FONT_32_ASCII);
//	GUI_DispStringHCenterAt("MEMDEV_MemDev", 240, 5);
//	GUI_SetFont(GUI_FONT_24_ASCII);
//	GUI_DispStringHCenterAt("Shows the advantage of using a\nmemorydevice", 240, 45);  //支持直接换行
//	GUI_SetFont(GUI_FONT_20_ASCII);
//	GUI_DispStringHCenterAt("Draws the number\nwithout a\nmemory device", 100, 250);
//  GUI_DispStringHCenterAt("Draws the number\nusing a\nmemory device", 350, 250);
//	
//	 /* 创建内存设备 */
//  hMem = GUI_MEMDEV_Create(275, 150, 150, 100);
//	
//}


////static void _cbWindow(WM_MESSAGE* pMsg)
////{
////	GUI_RECT Rect;
////	
////	  switch (pMsg->MsgId)
////	{
////		case WM_PAINT:
////      /* 返回窗口客户区坐标 */
////			WM_GetInsideRect(&Rect);
////      /* 设置窗口背景颜色 */
////			GUI_SetBkColor(GUI_RED);
////      /* 设置前景颜色 */
////			GUI_SetColor(GUI_YELLOW);
////      /* 绘制窗口 */    
////			GUI_ClearRectEx(&Rect);
////			GUI_DrawRectEx(&Rect);
////      /* 设置文本颜色 */
////			GUI_SetColor(GUI_BLACK);
////      /* 设置文本格式 */
////			GUI_SetFont(&GUI_Font8x16);
////      /* 显示提示信息 */
////			GUI_DispStringAt("Foreground window", 0, 0);
////			break;
////		default:
////			WM_DefaultProc(pMsg);
////  }
////}


////static void _MoveWindow(const char *pText)
////{
////	WM_HWIN  hWnd;
////	U8     i;
////	  /* 创建前景窗口 */
////  hWnd = WM_CreateWindow(10, 50, 150, 100, WM_CF_SHOW, _cbWindow, 0);
////	GUI_Delay(500);
////	 /* 移动前景窗口 */
////  for (i = 0; i < 40; i++)
////	{
////    WM_MoveWindow(hWnd, 2, 2);
////    GUI_Delay(10);
////  }
////	/* 移动结束后显示提示文字 */
////	  GUI_DispStringAt(pText, 5, 50);
////    GUI_Delay(2500);
////	
////	/* 删除前景窗口 */
////  WM_DeleteWindow(hWnd);
////  WM_Invalidate(WM_HBKWIN);
////  GUI_Exec();
////}



////static void _DemoRedraw(void)
////{
////	WM_CALLBACK * _cbOldBk;
////	/* 设置背景色 */
////	GUI_SetBkColor(GUI_BLACK);
////	GUI_Clear();
////	/*字体显示*/
////	GUI_SetColor(GUI_WHITE);
////  GUI_SetFont(&GUI_Font24_ASCII);
////  GUI_DispStringHCenterAt("WM_Redraw - Sample", 160, 5);
////	 
////	while(1)
////	{
////		 /* 在背景上移动窗口 */
////    _MoveWindow("Background has not been redrawn");
////     /* 清除背景 */
////    GUI_ClearRect(0, 50, 480, 230);
////    GUI_Delay(1000);
////		/* 重定向背景窗口的回调函数 */
////    _cbOldBk = WM_SetCallback(WM_HBKWIN, _cbBkWindow);
////		  /* 在背景上移动窗口 */
////    _MoveWindow("Background has been redrawn");
////		  /* 还原背景窗口的回调函数 */
////    WM_SetCallback(WM_HBKWIN, _cbOldBk);
////	}
////	
////	
////}

////演示例程
//#define SPEED           1500

//static void _DemoSetDesktopColor(void)
//{
//	 GUI_SetBkColor(GUI_BLUE);
//   GUI_Clear(); 
//	
//	 GUI_SetColor(GUI_WHITE);
//	 GUI_SetFont(&GUI_Font24_ASCII);
//   GUI_DispStringHCenterAt("WindowManager - Sample", 160, 5);
//	 GUI_SetFont(&GUI_Font8x16);
//	 GUI_DispStringAtCEOL("WM_SetDesktopColor()", 5, 40);
//	
////	 GUI_Delay(SPEED*3/2);
////	 WM_SetDesktopColor(GUI_BLACK);
////	 GUI_Delay(SPEED/2);
////	 GUI_SetBkColor(GUI_BLACK);
////	 WM_SetDesktopColor(GUI_INVALID_COLOR);
//}


//static void _ChangeInfoText(char * pStr)
//{
//  WM_MESSAGE Message;

//  Message.MsgId  = MSG_CHANGE_TEXT;
//  Message.Data.p = pStr;
//  WM_SendMessage(WM_HBKWIN, &Message);
//  WM_InvalidateWindow(WM_HBKWIN);
//}

///**
//  * @brief 窗口1回调函数
//  * @note 无
//  * @param 无
//  * @retval 无
//  */
//static void _cbWindow1(WM_MESSAGE * pMsg)
//{
//  GUI_RECT Rect;
//  int      x;
//  int      y;

//  switch (pMsg->MsgId)
//	{
//		case WM_PAINT:
//			WM_GetInsideRect(&Rect);
//			GUI_SetBkColor(_WindowColor1);
//			GUI_SetColor(_FrameColor1);
//			GUI_ClearRectEx(&Rect);
//			GUI_DrawRectEx(&Rect);
//			GUI_SetColor(GUI_WHITE);
//			GUI_SetFont(&GUI_Font24_ASCII);
//			x = WM_GetWindowSizeX(pMsg->hWin);
//			y = WM_GetWindowSizeY(pMsg->hWin);
//			GUI_DispStringHCenterAt("Window 1", x / 2, (y / 2) - 12);
//			break;
//		default:
//			WM_DefaultProc(pMsg);
//  }
//}
//static void _cbWindow2(WM_MESSAGE * pMsg)
//{
//  GUI_RECT Rect;
//  int      x;
//  int      y;

//  switch (pMsg->MsgId)
//	{
//		case WM_PAINT:
//			WM_GetInsideRect(&Rect);
//			GUI_SetBkColor(_WindowColor2);
//			GUI_SetColor(_FrameColor2);
//			GUI_ClearRectEx(&Rect);
//			GUI_DrawRectEx(&Rect);
//			GUI_SetColor(GUI_WHITE);
//			GUI_SetFont(&GUI_Font24_ASCII);
//			x = WM_GetWindowSizeX(pMsg->hWin);
//			y = WM_GetWindowSizeY(pMsg->hWin);
//			GUI_DispStringHCenterAt("Window 2", x / 2, (y / 4) - 12);
//			break;
//		default:
//			WM_DefaultProc(pMsg);
//  }
//}
//static void _DemoCreateWindow(void)
//{
//  /* 重定向背景窗口回调函数 */
// // _cbBkWindowOld = WM_SetCallback(WM_HBKWIN, _cbBkWindow);
//  /* 创建窗口 */
//  //_ChangeInfoText("WM_CreateWindow()");
//  GUI_Delay(SPEED);
//  _hWindow1 = WM_CreateWindow( 0,  30, 120, 250, WM_CF_SHOW , _cbWindow1, 0);//| WM_CF_MEMDEV
// // GUI_Delay(SPEED/3);
//  _hWindow2 = WM_CreateWindow(125, 30, 120, 250, WM_CF_SHOW , _cbWindow2, 0);
// // GUI_Delay(SPEED);
//	  /* 还原背景窗口的回调函数 */
//    //WM_SetCallback(WM_HBKWIN, _cbBkWindowOld);
//}


#define ID_ICONVIEW_0 (GUI_ID_USER + 0x00)
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_0     (GUI_ID_USER + 0x02)


//窗口重绘

extern const char Framewin_text[];

#define MSG_CHANGE_TEXT (WM_USER + 0)
//自定义消息函数
void _ChangeInfoText()//char * pStr
{
	GUI_HWIN Thim;
  WM_MESSAGE Message;
  //Thim= WM_GetParent(CreateFramewin());
  Message.MsgId  = MSG_CHANGE_TEXT;
  //Message.Data.p = pStr;
  WM_SendMessage(WM_HBKWIN, &Message);
  //WM_InvalidateWindow(WM_HBKWIN);
}

static void _cbBkWindow(WM_MESSAGE* pMsg)
{
   switch (pMsg->MsgId)
	{
	
		case WM_PAINT:
			GUI_SetBkColor(GUI_RED);
			GUI_Clear();
		//	GUI_SetColor(GUI_BLACK);
		//	GUI_SetFont(&XBF_Font24);
		//	GUI_DispStringHCenterAt(Framewin_text, 240, 5);
		//	GUI_SetFont(&GUI_Font8x16);
			//GUI_DispStringAt(_acInfoText, 5, 40);
			break;
			case MSG_CHANGE_TEXT:
				LED1_TOGGLE;
		break;
		default:
			WM_DefaultProc(pMsg);
  }
}



/**
  * @brief GUI主任务
  * @note 无
  * @param 无
  * @retval 无
  */
void MainTask(void)
{
	// GUI_Init();
	U8   NumITEM;
	WM_HWIN hWin;

		/* 启用UTF-8编码 */
	GUI_UC_SetEncodeUTF8();
	GUI_SetXBF();

//	
//	/* 在指定位置创建ICONVIEW控件 */
//	hWin = ICONVIEW_CreateEx(30,                     /* 相对于父窗口坐标的最左像素 */
//	                         20,                       /* 相对于父窗口坐标的最上像素 */
//	                         400,                      /* 水平尺寸 */
//	                         150,                      /* 垂直尺寸 */
//	                         WM_HBKWIN,                /* 父窗口句柄 */
//	                         WM_CF_SHOW|WM_CF_HASTRANS,/* 窗口创建标志 */
//	                         0,                        /* 不设置自动滚动条 */
//	                         ID_ICONVIEW_0,            /* 控件ID */
//	                         50,                       /* 单个图标的水平尺寸 */
//	                         40+10);                   /* 单个图标的垂直尺寸 */
//	 ICONVIEW_SetBkColor(hWin,ICONVIEW_CI_BK,GUI_BLUE);
//	 ICONVIEW_SetItemText(hWin,ICONVIEW_CI_SEL,"123");
//		/* 设置初始选择的图标，-1表示不选中任何图标 */
//	ICONVIEW_SetSel(hWin, -1);
//	/* 设置图标标题的字体 */
//	ICONVIEW_SetFont(hWin, &XBF_Font24);
//	/* 设置标题的对齐方式 */
//	ICONVIEW_SetTextAlign(hWin, GUI_TA_HCENTER | GUI_TA_BOTTOM);
//	/* 设置图标被选中时的背景色 */
//	ICONVIEW_SetBkColor(hWin, ICONVIEW_CI_SEL, GUI_MAKE_COLOR(0x40ul << 24 | 0xFFFFFF));
//	/* 设置图标的对齐方式 */
//	ICONVIEW_SetIconAlign(hWin, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
//	/* 设置图标在X和Y方向上的间距 */
//	ICONVIEW_SetSpace(hWin, GUI_COORD_X, 20);
//	ICONVIEW_SetSpace(hWin, GUI_COORD_Y, 20);
	
	
		
	WM_SetCreateFlags(WM_CF_MEMDEV);
	WM_EnableMemdev(WM_HBKWIN);
	
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
	//WM_SetDesktopColor(GUI_BLUE); 
	Create_Homepage_Framewin();
	/* 设置背景色 */
//	GUI_SetBkColor(GUI_WHITE);
//	GUI_Clear();
//	GUI_SetColor(GUI_BLACK);
//	GUI_SetFont(&XBF_Font24);
//	GUI_DispStringAt("智能车道管理机", 10, 10);
	//Display_String();
	//CreateFramewin();
//	/* 显示十进制数 */
//	Disp_DecNum();
//	/* 显示浮点数 */
//	Disp_FloatingNum();
//	/* 显示二进制和十六进制数 */
//	Disp_BinHexNum();
	
//	vTaskDelay(200);
//	GUI_Clear();
//	Display_String();
	//绘制二维码
	//_2D_Graph_Drawing();
//	ShowBitmap();
//	ShowColor();
//	U16 i;
//	_DemoMemDev();
//	while(1)
//	{
//		/* 直接绘制 */
//    _Draw(25, 150, 175, 250, i);
//		 /* 激活内存设备 */
//    GUI_MEMDEV_Select(hMem);
//		 /* 向内存设备中绘制图形 */
//    _Draw(275, 150, 425, 250, i);
//		/* 选择LCD */
//    GUI_MEMDEV_Select(0);
//		 /* 将内存设备中的内容复制到LCD */
//    GUI_MEMDEV_CopyToLCDAt(hMem, 275, 150);
//		GUI_Delay(100);
//		i++;
//		if (i > 999)
//		{
//			i = 0;
//		}
//	}

//_DemoRedraw();
//GUI_SetBkColor(GUI_WHITE);
  // GUI_Clear(); 
//WM_SetCreateFlags(WM_CF_MEMDEV);
//WM_EnableMemdev(WM_HBKWIN);
while(1)
{
	//_DemoSetDesktopColor();
//	_DemoCreateWindow();
		GUI_Delay(100);
}

}

/**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2017-03-30
  * 功    能: 板载调试串口底层驱动程序：默认使用USART1
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F4Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/  
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "usart/bsp_debug_usart.h"
#include "spiflash/bsp_spiflash.h"
#include "led/bsp_led.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
UART_HandleTypeDef   husart_debug;
DMA_HandleTypeDef    hdma_usart1_rx;
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

extern SemaphoreHandle_t   USART_BinarySem_Handle;


uint32_t Write_Sector_Count=0;



uint8_t USART_RX_BUF[FLASH_SECTOR_SIZE*2]={0};              //接收数据缓存

/**
  * 函数功能: 串口硬件初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  if(huart->Instance==DEBUG_USARTx)
  {
    /* 串口外设时钟使能 */
    DEBUG_USART_RCC_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE();
  
    /* 串口外设功能GPIO配置 */
    GPIO_InitStruct.Pin = DEBUG_USARTx_Tx_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = DEBUG_USARTx_AFx;
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = DEBUG_USARTx_Rx_GPIO_PIN;  
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct); 
   /* 配置DMA */
		hdma_usart1_rx.Instance = DMA2_Stream5;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_usart1_rx);
		
    __HAL_LINKDMA(huart,hdmarx,hdma_usart1_rx);

    HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);    
  }  
}

/**
  * 函数功能: 串口硬件反初始化配置
  * 输入参数: huart：串口句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==DEBUG_USARTx)
  {
    /* 串口外设时钟禁用 */
    DEBUG_USART_RCC_CLK_DISABLE();
  
    /* 串口外设功能GPIO配置 */
    HAL_GPIO_DeInit(DEBUG_USARTx_Tx_GPIO, DEBUG_USARTx_Tx_GPIO_PIN);
    HAL_GPIO_DeInit(DEBUG_USARTx_Rx_GPIO, DEBUG_USARTx_Rx_GPIO_PIN);
		
	//	HAL_DMA_DeInit(huart->hdmarx);
    
    /* 串口中断禁用 */
    HAL_NVIC_DisableIRQ(DEBUG_USART_IRQn);
  }
}

/**
  * 函数功能: 串口参数配置.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void MX_DEBUG_USART_Init(void)
{
  /* 使能串口功能引脚GPIO时钟 */
  DEBUG_USARTx_GPIO_ClK_ENABLE();
  
  husart_debug.Instance = DEBUG_USARTx;
  husart_debug.Init.BaudRate = DEBUG_USARTx_BAUDRATE;
  husart_debug.Init.WordLength = UART_WORDLENGTH_8B;
  husart_debug.Init.StopBits = UART_STOPBITS_1;
  husart_debug.Init.Parity = UART_PARITY_NONE;
  husart_debug.Init.Mode = UART_MODE_TX_RX;
  husart_debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  husart_debug.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&husart_debug);
	
	
 // __HAL_UART_ENABLE_IT(&husart_debug, UART_IT_IDLE);//使能idle中断
	
	//HAL_UART_Receive_DMA(&husart_debug,USART_RX_BUF,FLASH_SECTOR_SIZE*2);//打开DMA接收，数据存入rx_buffer数组中。
}

/**
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&husart_debug, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

/**
  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&husart_debug,&ch, 1, 0xffff);
  return ch;
}

void USART1_IRQHandler(void)
{
   uint32_t ulReturn;
	 BaseType_t pxHigherPriorityTaskWoken;
		/* 进入临界段，临界段可以嵌套 */
   ulReturn = taskENTER_CRITICAL_FROM_ISR();
	HAL_UART_IRQHandler(&husart_debug); 
	
  if(__HAL_UART_GET_IT_SOURCE(&husart_debug,USART_IT_IDLE)!=RESET)
  {        
    if(Write_Sector_Count)
    {
      LED2_ON;
      if(Write_Sector_Count%2)
      {
        LED1_OFF;
        SPI_FLASH_BufferWrite(&USART_RX_BUF[FLASH_SECTOR_SIZE],FLASH_UNIGBK_ADDR+Write_Sector_Count*FLASH_SECTOR_SIZE,UNIGBK_FILE_SIZE-Write_Sector_Count*FLASH_SECTOR_SIZE);
      }
      else
      {
        LED1_ON;
        SPI_FLASH_BufferWrite(USART_RX_BUF,FLASH_UNIGBK_ADDR+Write_Sector_Count*FLASH_SECTOR_SIZE,UNIGBK_FILE_SIZE-Write_Sector_Count*FLASH_SECTOR_SIZE);
      }
      printf("Number Sector:%d\r\n",Write_Sector_Count);
      
			HAL_UART_DMAStop(&husart_debug);
     // write_finish=1;
			
			
      __HAL_UART_CLEAR_IDLEFLAG(&husart_debug);
      __HAL_UART_DISABLE_IT(&husart_debug,UART_IT_IDLE);
			
			
			 //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
       xSemaphoreGiveFromISR(USART_BinarySem_Handle,&pxHigherPriorityTaskWoken);	//释放二值信号量
			 portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    }
  }
	 /* 退出临界段 */
			taskEXIT_CRITICAL_FROM_ISR( ulReturn );
}

void DMA2_Stream5_IRQHandler(void)
{

	 uint32_t ulReturn;
	 BaseType_t pxHigherPriorityTaskWoken;
		/* 进入临界段，临界段可以嵌套 */
   ulReturn = taskENTER_CRITICAL_FROM_ISR();
	
  if(__HAL_DMA_GET_FLAG(&hdma_usart1_rx, __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_usart1_rx)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(&hdma_usart1_rx, DMA_IT_HT) != RESET)
    {       
      /* Clear the half transfer complete flag */
      __HAL_DMA_CLEAR_FLAG(&hdma_usart1_rx, __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_usart1_rx));
      LED2_ON;
      SPI_FLASH_BufferWrite(USART_RX_BUF,FLASH_UNIGBK_ADDR+Write_Sector_Count*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
      Write_Sector_Count++;
      LED1_TOGGLE;
      LED2_OFF;
    }
  }
  if(__HAL_DMA_GET_FLAG(&hdma_usart1_rx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_usart1_rx)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(&hdma_usart1_rx, DMA_IT_TC) != RESET)
    {      
      /* Clear the transfer complete flag */
      __HAL_DMA_CLEAR_FLAG(&hdma_usart1_rx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_usart1_rx));
      LED2_ON;
      SPI_FLASH_BufferWrite(&USART_RX_BUF[FLASH_SECTOR_SIZE],FLASH_UNIGBK_ADDR+Write_Sector_Count*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
      Write_Sector_Count++;
      LED1_TOGGLE;
      LED2_OFF;
    }
  }
	
	 /* 退出临界段 */
		taskEXIT_CRITICAL_FROM_ISR( ulReturn );
	
}


/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/

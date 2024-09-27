/**
  ******************************************************************************
  * �ļ�����: main.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2017-03-30
  * ��    ��: ���ص��Դ��ڵײ���������Ĭ��ʹ��USART1
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F4Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/  
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "usart/bsp_debug_usart.h"
#include "spiflash/bsp_spiflash.h"
#include "led/bsp_led.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
UART_HandleTypeDef   husart_debug;
DMA_HandleTypeDef    hdma_usart1_rx;
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

extern SemaphoreHandle_t   USART_BinarySem_Handle;


uint32_t Write_Sector_Count=0;



uint8_t USART_RX_BUF[FLASH_SECTOR_SIZE*2]={0};              //�������ݻ���

/**
  * ��������: ����Ӳ����ʼ������
  * �������: huart�����ھ������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  if(huart->Instance==DEBUG_USARTx)
  {
    /* ��������ʱ��ʹ�� */
    DEBUG_USART_RCC_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE();
  
    /* �������蹦��GPIO���� */
    GPIO_InitStruct.Pin = DEBUG_USARTx_Tx_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = DEBUG_USARTx_AFx;
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = DEBUG_USARTx_Rx_GPIO_PIN;  
    HAL_GPIO_Init(DEBUG_USARTx_Tx_GPIO, &GPIO_InitStruct); 
   /* ����DMA */
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
  * ��������: ����Ӳ������ʼ������
  * �������: huart�����ھ������ָ��
  * �� �� ֵ: ��
  * ˵    ��: �ú�����HAL���ڲ�����
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==DEBUG_USARTx)
  {
    /* ��������ʱ�ӽ��� */
    DEBUG_USART_RCC_CLK_DISABLE();
  
    /* �������蹦��GPIO���� */
    HAL_GPIO_DeInit(DEBUG_USARTx_Tx_GPIO, DEBUG_USARTx_Tx_GPIO_PIN);
    HAL_GPIO_DeInit(DEBUG_USARTx_Rx_GPIO, DEBUG_USARTx_Rx_GPIO_PIN);
		
	//	HAL_DMA_DeInit(huart->hdmarx);
    
    /* �����жϽ��� */
    HAL_NVIC_DisableIRQ(DEBUG_USART_IRQn);
  }
}

/**
  * ��������: ���ڲ�������.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void MX_DEBUG_USART_Init(void)
{
  /* ʹ�ܴ��ڹ�������GPIOʱ�� */
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
	
	
 // __HAL_UART_ENABLE_IT(&husart_debug, UART_IT_IDLE);//ʹ��idle�ж�
	
	//HAL_UART_Receive_DMA(&husart_debug,USART_RX_BUF,FLASH_SECTOR_SIZE*2);//��DMA���գ����ݴ���rx_buffer�����С�
}

/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&husart_debug, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

/**
  * ��������: �ض���c�⺯��getchar,scanf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
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
		/* �����ٽ�Σ��ٽ�ο���Ƕ�� */
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
			
			
			 //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
       xSemaphoreGiveFromISR(USART_BinarySem_Handle,&pxHigherPriorityTaskWoken);	//�ͷŶ�ֵ�ź���
			 portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    }
  }
	 /* �˳��ٽ�� */
			taskEXIT_CRITICAL_FROM_ISR( ulReturn );
}

void DMA2_Stream5_IRQHandler(void)
{

	 uint32_t ulReturn;
	 BaseType_t pxHigherPriorityTaskWoken;
		/* �����ٽ�Σ��ٽ�ο���Ƕ�� */
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
	
	 /* �˳��ٽ�� */
		taskEXIT_CRITICAL_FROM_ISR( ulReturn );
	
}


/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/

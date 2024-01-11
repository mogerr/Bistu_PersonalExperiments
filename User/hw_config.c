/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           hw_config.c
** Last modified Date:  2012-08-27
** Last Version:        V1.00
** Descriptions:        硬件配置文件
**
**----------------------------------------------------------------------------------------------------
** Created by:          openmcu
** Created date:        2012-08-27
** Version:             V1.00
** Descriptions:        编写示例代码
**
**----------------------------------------------------------------------------------------------------
** Modified by:         ZQJ
** Modified date:        
** Version:            
** Descriptions:        
**
*****************************************************************/ 

#include "hw_config.h" 
#include "os_cpu.h"
#include "os_cfg.h"
#include <stdio.h>
/*****************************************************************************
** 函数名称: void NVIC_Configuration(void)
** 功能描述: NVIC初始化
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*****************************************************************************
** 函数名称: void  SysTick_Configuration(void)
** 功能描述: 系统定时器初始化
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
void  SysTick_Configuration(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;
    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config(cnts);
}

/*****************************************************************************
** 函数名称: void LED_Configuration(void)
** 功能描述: LED初始化
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	/*---------初始化状态四个LED全OFF------------*/
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);
}

/*****************************************************************************
** 函数名称: void USART_Configuration(void)
** 功能描述: 串口1初始化	波特率115200
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
void USART_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

    /*USART1端口配置
	  PA9 TX 复用推挽输出 PA10 RX 浮空输入模式*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    /*--------------USART1 USART2配置-------------------*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

/*****************************************************************************
** 函数名称: int main(void)
** 功能描述: 主函数入口
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
int fputc(int ch, FILE *f)
{
  USART_SendData(USART1, (uint8_t) ch);   
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  return ch;
}


/**************************************************
*函数名称：void ADC_Configuration(void)
*入口参数：无
*出口参数：无
*功能说明：ADC初始化配置  测内核电压使用ADC_Channel_17
*	       测温度传感器输出电压使用ADC_Channel_16
***************************************************/
void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);      //使能ADC时钟
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	      //ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;		      //多通道扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		  //连续模数转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	 //转换由软件触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				 //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 							 //进行规则转换的通道数为1
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_239Cycles5);

	ADC_TempSensorVrefintCmd(ENABLE);			  //使能温度传感器和内部参考电压通道
		  
	ADC_ResetCalibration(ADC1);	                  //复位校准寄存器

	while(ADC_GetResetCalibrationStatus(ADC1));	  //等待ADC1复位校准寄存器结束
	
	ADC_StartCalibration(ADC1);			          //开始校准

	while(ADC_GetCalibrationStatus(ADC1));		  //等待校准结束
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		  //启动软件转换，这句必须加上去
}

/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           hw_config.c
** Last modified Date:  2012-08-27
** Last Version:        V1.00
** Descriptions:        Ӳ�������ļ�
**
**----------------------------------------------------------------------------------------------------
** Created by:          openmcu
** Created date:        2012-08-27
** Version:             V1.00
** Descriptions:        ��дʾ������
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
** ��������: void NVIC_Configuration(void)
** ��������: NVIC��ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
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
** ��������: void  SysTick_Configuration(void)
** ��������: ϵͳ��ʱ����ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
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
** ��������: void LED_Configuration(void)
** ��������: LED��ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
*****************************************************************************/
void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LED, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(LED_PORT, &GPIO_InitStructure);

	/*---------��ʼ��״̬�ĸ�LEDȫOFF------------*/
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);
}

/*****************************************************************************
** ��������: void USART_Configuration(void)
** ��������: ����1��ʼ��	������115200
** ��ڲ���: ��
** ���ڲ���: ��
*****************************************************************************/
void USART_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

    /*USART1�˿�����
	  PA9 TX ����������� PA10 RX ��������ģʽ*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    /*--------------USART1 USART2����-------------------*/
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
** ��������: int main(void)
** ��������: ���������
** ��ڲ���: ��
** ���ڲ���: ��
*****************************************************************************/
int fputc(int ch, FILE *f)
{
  USART_SendData(USART1, (uint8_t) ch);   
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  return ch;
}


/**************************************************
*�������ƣ�void ADC_Configuration(void)
*��ڲ�������
*���ڲ�������
*����˵����ADC��ʼ������  ���ں˵�ѹʹ��ADC_Channel_17
*	       ���¶ȴ����������ѹʹ��ADC_Channel_16
***************************************************/
void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);      //ʹ��ADCʱ��
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	      //ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;		      //��ͨ��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		  //����ģ��ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	 //ת���������������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				 //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 							 //���й���ת����ͨ����Ϊ1
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_239Cycles5);

	ADC_TempSensorVrefintCmd(ENABLE);			  //ʹ���¶ȴ��������ڲ��ο���ѹͨ��
		  
	ADC_ResetCalibration(ADC1);	                  //��λУ׼�Ĵ���

	while(ADC_GetResetCalibrationStatus(ADC1));	  //�ȴ�ADC1��λУ׼�Ĵ�������
	
	ADC_StartCalibration(ADC1);			          //��ʼУ׼

	while(ADC_GetCalibrationStatus(ADC1));		  //�ȴ�У׼����
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		  //�������ת�������������ȥ
}

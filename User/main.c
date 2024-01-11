/****************************Copyright(c)*****************************
**                      http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2012-07-23
** Last Version:        V1.00
** Descriptions:        
**
**----------------------------------------------------------------------------------------------------
** Created by:          openmcu
** Created date:        2012-08-27
** Version:             V1.00
** Descriptions:        ��дʾ������
**
**----------------------------------------------------------------------------------------------------
** Modified by:         jeanson
** Modified date:       2014-3-6
** Version:            
** Descriptions:        ucos ii���񴴽���ɾ��
**
*****************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "hw_config.h"
#include "stm32f10x.h"
#include <ucos_ii.h>
#include "os_cpu.h"
#include  <cpu.h>
#include  <app_cfg.h>
// ���� ����3 LCD��ʾ & ADC��ȡ ��ͷ�ļ�
#include "107_32_Driver_IO16_uCOSII.h"
#include <app.h>

// �����ⲿ
// #include "font.h"
extern u8 gImage_fg[];

static OS_STK AppTask1Stk[APP_TASK1_STK_SIZE];		//����1��ջ
static OS_STK AppTask2Stk[APP_TASK2_STK_SIZE];		//����2��ջ
static OS_STK AppTask3Stk[APP_TASK3_STK_SIZE];		//����3��ջ

static void AppTaskCreate(void);		
static void AppTask1(void *p_arg);
static void AppTask2(void *p_arg);
static void AppTask3(void *p_arg);

/*****************************************************************************
** ��������: int main(void)
** ��������: ���������
** ��ڲ���: ��
** ���ڲ���: ��
*****************************************************************************/
int  main (void)
{
	SysTick_Configuration(); 	//ϵͳ��ʱ����ʼ��
	USART_Configuration();  	//���ڳ�ʼ��
	LED_Configuration();
	ADC_Configuration();

	OSInit();      	//usos ii��ʼ��

	AppTaskCreate();//��������

	OSStart();      //��ʼ�������
}

/*****************************************************************************
** ��������: static  void  AppTaskCreate(void)
** ��������: ��������
** ��ڲ���: ��
** ���ڲ���: ��
*****************************************************************************/
static  void  AppTaskCreate(void)
{
	INT8U  err;

	OSTaskCreateExt(AppTask1,(void *)0,(OS_STK *)&AppTask1Stk[APP_TASK1_STK_SIZE-1],APP_TASK1_PRIO,APP_TASK1_PRIO,(OS_STK *)&AppTask1Stk[0],
					APP_TASK1_STK_SIZE, (void *)0,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		//��������1

	OSTaskNameSet(APP_TASK1_PRIO, "AppTask1", &err);


	OSTaskCreateExt(AppTask2,(void *)0,(OS_STK *)&AppTask2Stk[APP_TASK2_STK_SIZE-1],APP_TASK2_PRIO,APP_TASK2_PRIO,(OS_STK *)&AppTask2Stk[0],
					APP_TASK2_STK_SIZE,(void *)0, OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		//��������2

	OSTaskNameSet(APP_TASK2_PRIO, "AppTask2", &err);
	
	// ��������: ����3 LCD��ʾ & ADC��ȡ
	OSTaskCreateExt(AppTask3,(void *)0,(OS_STK *)&AppTask3Stk[APP_TASK3_STK_SIZE-1],APP_TASK3_PRIO,APP_TASK3_PRIO,(OS_STK *)&AppTask3Stk[0],
					APP_TASK3_STK_SIZE,(void *)0, OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		//��������3

	OSTaskNameSet(APP_TASK3_PRIO, "AppTask3", &err);

}

/*****************************************************************************
** ��������: static  void  AppTask1 (void *p_arg)
** ��������: ����1ѭ����ӡ���AppTask1 LED1��˸
** ��ڲ���: p_arg
** ���ڲ���: ��
*****************************************************************************/
static  void  AppTask1 (void *p_arg)
{
	while(1)
	{
		// printf("\n\rAppTask1\r\n");
		LED1(0);
		OSTimeDlyHMSM(0,0,1,0);
		LED1(1);
		OSTimeDlyHMSM(0,0,1,0);
 	}
}

/*****************************************************************************
** ��������: static  void  AppTask2 (void *p_arg)
** ��������: ����2ѭ����ӡ���AppTask2 6�κ�ɾ��
** ��ڲ���: p_arg
** ���ڲ���: ��
*****************************************************************************/
static  void  AppTask2 (void *p_arg)
{
	INT8U i;
	for(i=0;i<6;i++)
	{
		// printf("\n\rAppTask2 \r\n");
		OSTimeDlyHMSM(0,0,0,500);	
	}
	// printf("\n\rɾ������2\r\n");
	OSTaskDel(APP_TASK2_PRIO);	//ɾ������2
}

/*****************************************************************************
** ��������: static  void  AppTask3 (void *p_arg)
** ��������: ����3 LCD��ʾ & ADC��ȡ
** ��ڲ���: p_arg
** ���ڲ���: ��
*****************************************************************************/
static void AppTask3(void *p_arg)
{
	LCD_Init();	

	LCD_ShowString(50, 30, " ������Ϣ�Ƽ���ѧ ", RED, BLACK);  /* ��ʾ�ַ��� */
	LCD_ShowString(60, 50, " ������  ������ ", LGRAY, BLACK);  /* ��ʾ�ַ��� */
	LCD_DrawPicture(0,100,240,320, gImage_fg);	  		         //240��320ΪͼƬ�ĸ߶ȺͿ��
	
	OSTimeDlyHMSM(0,0,2,0);
	LCD_Clear(BLACK);
	OSTimeDlyHMSM(0,0,2,0);

	LCD_ShowString(60, 70,"TEMPERATE TEST", RED, BLACK);	
	LCD_ShowString(60,130,"TEMP_VAL:", YELLOW, BLACK);	      
	LCD_ShowString(60,150,"TEMP_VOL:0.000V", YELLOW, BLACK);	      
	LCD_ShowString(60,170,"TEMPERATE:00.00C", YELLOW, BLACK);

	while (1)
	{	
		OSTimeDlyHMSM(0,0,1,0);
		Show_temperature();
	}

	// OSTimeDlyHMSM(0,0,1,0);	
	// OSTaskDel(APP_TASK3_PRIO);	//ɾ������3
}








/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

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
** Descriptions:        编写示例代码
**
**----------------------------------------------------------------------------------------------------
** Modified by:         jeanson
** Modified date:       2014-3-6
** Version:            
** Descriptions:        ucos ii任务创建与删除
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
// 引入 任务3 LCD显示 & ADC读取 的头文件
#include "107_32_Driver_IO16_uCOSII.h"
#include <app.h>

// 引入外部
// #include "font.h"
extern u8 gImage_fg[];

static OS_STK AppTask1Stk[APP_TASK1_STK_SIZE];		//任务1堆栈
static OS_STK AppTask2Stk[APP_TASK2_STK_SIZE];		//任务2堆栈
static OS_STK AppTask3Stk[APP_TASK3_STK_SIZE];		//任务3堆栈

static void AppTaskCreate(void);		
static void AppTask1(void *p_arg);
static void AppTask2(void *p_arg);
static void AppTask3(void *p_arg);

/*****************************************************************************
** 函数名称: int main(void)
** 功能描述: 主函数入口
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
int  main (void)
{
	SysTick_Configuration(); 	//系统定时器初始化
	USART_Configuration();  	//串口初始化
	LED_Configuration();
	ADC_Configuration();

	OSInit();      	//usos ii初始化

	AppTaskCreate();//创建任务

	OSStart();      //开始任务调度
}

/*****************************************************************************
** 函数名称: static  void  AppTaskCreate(void)
** 功能描述: 创建任务
** 入口参数: 无
** 出口参数: 无
*****************************************************************************/
static  void  AppTaskCreate(void)
{
	INT8U  err;

	OSTaskCreateExt(AppTask1,(void *)0,(OS_STK *)&AppTask1Stk[APP_TASK1_STK_SIZE-1],APP_TASK1_PRIO,APP_TASK1_PRIO,(OS_STK *)&AppTask1Stk[0],
					APP_TASK1_STK_SIZE, (void *)0,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		//创建任务1

	OSTaskNameSet(APP_TASK1_PRIO, "AppTask1", &err);


	OSTaskCreateExt(AppTask2,(void *)0,(OS_STK *)&AppTask2Stk[APP_TASK2_STK_SIZE-1],APP_TASK2_PRIO,APP_TASK2_PRIO,(OS_STK *)&AppTask2Stk[0],
					APP_TASK2_STK_SIZE,(void *)0, OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		//创建任务2

	OSTaskNameSet(APP_TASK2_PRIO, "AppTask2", &err);
	
	// 功能描述: 任务3 LCD显示 & ADC读取
	OSTaskCreateExt(AppTask3,(void *)0,(OS_STK *)&AppTask3Stk[APP_TASK3_STK_SIZE-1],APP_TASK3_PRIO,APP_TASK3_PRIO,(OS_STK *)&AppTask3Stk[0],
					APP_TASK3_STK_SIZE,(void *)0, OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);		//创建任务3

	OSTaskNameSet(APP_TASK3_PRIO, "AppTask3", &err);

}

/*****************************************************************************
** 函数名称: static  void  AppTask1 (void *p_arg)
** 功能描述: 任务1循环打印输出AppTask1 LED1闪烁
** 入口参数: p_arg
** 出口参数: 无
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
** 函数名称: static  void  AppTask2 (void *p_arg)
** 功能描述: 任务2循环打印输出AppTask2 6次后删除
** 入口参数: p_arg
** 出口参数: 无
*****************************************************************************/
static  void  AppTask2 (void *p_arg)
{
	INT8U i;
	for(i=0;i<6;i++)
	{
		// printf("\n\rAppTask2 \r\n");
		OSTimeDlyHMSM(0,0,0,500);	
	}
	// printf("\n\r删除任务2\r\n");
	OSTaskDel(APP_TASK2_PRIO);	//删除任务2
}

/*****************************************************************************
** 函数名称: static  void  AppTask3 (void *p_arg)
** 功能描述: 任务3 LCD显示 & ADC读取
** 入口参数: p_arg
** 出口参数: 无
*****************************************************************************/
static void AppTask3(void *p_arg)
{
	LCD_Init();	

	LCD_ShowString(50, 30, " 北京信息科技大学 ", RED, BLACK);  /* 显示字符串 */
	LCD_ShowString(60, 50, " 李李李  王王王 ", LGRAY, BLACK);  /* 显示字符串 */
	LCD_DrawPicture(0,100,240,320, gImage_fg);	  		         //240和320为图片的高度和宽度
	
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
	// OSTaskDel(APP_TASK3_PRIO);	//删除任务3
}








/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

/*
 * @Author: 
 * @Date: 2023-12-05 23:45:05
 * @LastEditTime: 2023-12-06 00:03:55
 * @FilePath: 
 * @Description: 
 */
#include <app.h>
/**************************************************
*函数名称：void Show_temperature(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：显示采集到得温度值
***************************************************/
void Show_temperature(void)
{
	
	uint16_t temp;
	uint16_t ADC_Int;
	float ADC_Value=0.00; 
	float temperate;

	temp = ADC_GetConversionValue(ADC1);
	LCD_ShowNum(132, 130, temp, 4, YELLOW, BLACK);             //显示ADC的值 
	ADC_Value = (3.3/4096)*temp;		                        // 电压值 
	temperate = ADC_Value;			                            // 保存电压值 
	ADC_Int = ADC_Value;
	LCD_ShowNum(132, 150 , ADC_Int, 1, YELLOW, BLACK);        	//显示电压值整数部分 
	ADC_Value-=(u8)ADC_Value;				                        //减掉整数部分	     
	LCD_ShowNum(148, 150, ADC_Value*1000, 3,  YELLOW, BLACK);	//显示电压小数部分  

	temperate=(1.43-temperate)/0.0043+25;                   //计算出当前温度值	 
	LCD_ShowNum(140, 170, (u8)temperate, 2, YELLOW, BLACK);    //显示温度整数部分	
	temperate-=(u8)temperate;	  
	LCD_ShowNum(164,170,temperate*100,2, YELLOW, BLACK);       //显示温度小数部分	
}				

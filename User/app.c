/*
 * @Author: 
 * @Date: 2023-12-05 23:45:05
 * @LastEditTime: 2023-12-06 00:03:55
 * @FilePath: 
 * @Description: 
 */
#include <app.h>
/**************************************************
*�������ƣ�void Show_temperature(void)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵������ʾ�ɼ������¶�ֵ
***************************************************/
void Show_temperature(void)
{
	
	uint16_t temp;
	uint16_t ADC_Int;
	float ADC_Value=0.00; 
	float temperate;

	temp = ADC_GetConversionValue(ADC1);
	LCD_ShowNum(132, 130, temp, 4, YELLOW, BLACK);             //��ʾADC��ֵ 
	ADC_Value = (3.3/4096)*temp;		                        // ��ѹֵ 
	temperate = ADC_Value;			                            // �����ѹֵ 
	ADC_Int = ADC_Value;
	LCD_ShowNum(132, 150 , ADC_Int, 1, YELLOW, BLACK);        	//��ʾ��ѹֵ�������� 
	ADC_Value-=(u8)ADC_Value;				                        //������������	     
	LCD_ShowNum(148, 150, ADC_Value*1000, 3,  YELLOW, BLACK);	//��ʾ��ѹС������  

	temperate=(1.43-temperate)/0.0043+25;                   //�������ǰ�¶�ֵ	 
	LCD_ShowNum(140, 170, (u8)temperate, 2, YELLOW, BLACK);    //��ʾ�¶���������	
	temperate-=(u8)temperate;	  
	LCD_ShowNum(164,170,temperate*100,2, YELLOW, BLACK);       //��ʾ�¶�С������	
}				

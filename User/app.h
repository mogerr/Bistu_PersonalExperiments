/*
 * @Author: 
 * @Date: 2023-12-05 23:45:05
 * @LastEditTime: 2023-12-06 00:05:01
 * @FilePath: 
 * @Description: 
 */
#ifndef __APP_H
#define __APP_H

// 引入宏定义
#include "hw_config.h"
#include "stm32f10x.h"
#include <ucos_ii.h>
// 引入LCD宏定义
#include "107_32_Driver_IO16_uCOSII.h"
// 引入ADC函数可调用
#include "stm32f10x_adc.h"



void Show_temperature(void);

#endif

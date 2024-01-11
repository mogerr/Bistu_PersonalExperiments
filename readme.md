# stm32f107_ucosii_lcd_adc_led

Bistu PostGraduate 嵌入式设计 Experiment

实验要求：  使用开发板LCD显示图片和名字，显示adc读数，要求运行操作系统。

完成效果：

 ![IMG_20231206](/Doc/IMG_20231206.jpg)
0 error
0 warning



board：    金龙开发板_stm32f107VCT6

显示屏：    配套的3.2寸屏（SSD1298）

官方论坛：  [帖子 - 金龙107开发板例程汇总](https://www.eefocus.com/forum/thread-32851-1-1.html)

完成时间：  2023_12_06

MDK_keil:      V5.29.0

ARM_Compiler:  V5.06_Update_6(build 750)

Pack:          Keil.STM32F1xx_DFP.2.4.0

VSCode_Plugin: Keil_Assistant

如何使用：  

* 更改 /User/main.c 第144行。
* 同时更改 /User/LCD/font.h 第420~442行字库数据。
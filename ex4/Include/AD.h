#pragma once
//  预编译头文件, 请在vs2019设置"预编译头"
//#include"stdafx.h"
// 20230110 不推荐使用"预编译头"

#include <iostream>
#include <string>
#include <Windows.h>

// 请设置 Include 路径
// 例如：D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64
#include"Usb5935.h"

// 请设置vc "库目录"
// 目录一：D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64\amd64
// 中所有的文件
// USB5935.sys
// USB5935_32.dll
// USB5935_64.dll
// 目录二：D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64
// 中所有的文件
// USB5935_64.lib
// USB5935_32.lib



//1 定义AD板卡（USB接口）类，完成对板卡的封装；
//2 实现单通道和多通道的单点采集、多点采集；
//3 实现单通道和多通道的单点输出、多点输出。

class AD
{
public:
	AD(int);

	void Scs();//单通道的单点采集
	void Scm();//单通道的多点采集
	void Mcs();//多通道的单点采集
	void Mcm();//多通道的多点采集
	void Scso();//单通道的单点输出
	void Scmo();//单通道的多点输出
	void Mcso();//多通道的单点输出
	void Mcmo();//多通道的多点输出
	int SelectInputRange(void);

	~AD();

private:
	HANDLE hDevice;			// 设备对象句柄
	int DeviceLgcID;		// 物理设备ID号(由板上JP1决定)
	BOOL bReturn;			// 函数的返回值
	int nReadSizeWords;		// 每次读取AD数据个数
	LONG nRetWords = 0;     // 实际读取的数据个数
	int nChannelCount = 0;  // 采样通道数
	WORD ADBuffer[2048];	// 接收AD 数据的缓冲区
	float Volt;				// 将AD原始数据转换为电压值
	int nRemainder = 0;
	USB5935_PARA_AD ADPara; // 初始化AD的参数结构
	
	
};

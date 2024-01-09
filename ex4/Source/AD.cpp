#include"AD.h"
#include "conio.h"

AD::AD(int DeviceID)
{
	DeviceLgcID = DeviceID;
	// 创建设备对象
	hDevice = USB5935_CreateDevice(DeviceLgcID); 
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
	}
}

//单通道的单点采集
void AD::Scs()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;	// 首通道0
	ADPara.LastChannel = 0;		// 末通道0
	ADPara.GroundingMode = USB5935_GNDMODE_SE;	// 单端

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1;	 // 采样通道数

	DeviceLgcID = 0;	// 设备ID号, 假设系统中只有一个USB5935设备，即DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID);	// 创建设备对象
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara);	// 初始化AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 1;
	nRemainder = 0;
	nReadSizeWords = 1 - nRemainder;   // 读取数据的大小
	while (!_kbhit())	// kbhit()探测用户是否有按键动作,若有按键则退出
	{
		printf("请等待，您可以按任意键退出，但请不要直接关闭窗口强制退出...\n");
		// 读取AD转换数据
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) 
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 1; Index++) // 总共显示1个点的AD数据
		{
			switch (InputRange) // 根据量程选择，将AD原码按相应公式换算成电压值
			{
			case USB5935_INPUT_N10000_P10000mV: // ±10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N5000_P5000mV: // ±5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N2500_P2500mV: // ±2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_0_P10000mV: // 0～10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // 将AD数据转换为电压值
				break;
			default:
				printf("输入量程无效\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // 通道号递加，准备换算下一个通道的数据
			if (nChannel > ADPara.LastChannel) // 如果换算到末通道，再回到首通道
			{
				printf("\n"); // 将显示光标位置移到下一项
				nChannel = ADPara.FirstChannel;
			}
		} // 多点数据换算显示
	} // 循环采集

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // 释放AD，停止AD数据转换

ExitReleaseDevice:
	return;
	
}

//单通道的多点采集
void AD::Scm()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;	// 首通道0
	ADPara.LastChannel = 0;		// 末通道0
	//保证通道数为1
	ADPara.GroundingMode = USB5935_GNDMODE_SE; // 单端

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1; // 采样通道数

	DeviceLgcID = 0;  // 设备ID号, 假设系统中只有一个USB5935设备，即DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID); // 创建设备对象
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara); // 初始化AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 64;//保证每次采集的数据为64，实现多点采集
	nRemainder = 64%(nChannelCount*256);
	nReadSizeWords = 64 - nRemainder;   // 读取数据的大小
	while (!_kbhit()) // kbhit()探测用户是否有按键动作,若有按键则退出
	{
		printf("请等待，您可以按任意键退出，但请不要直接关闭窗口强制退出...\n");
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) // 读取AD转换数据
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 64; Index++) // 总共显示64个点的AD数据
		{
			switch (InputRange) // 根据量程选择，将AD原码按相应公式换算成电压值
			{
			case USB5935_INPUT_N10000_P10000mV: // ±10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N5000_P5000mV: // ±5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N2500_P2500mV: // ±2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_0_P10000mV: // 0～10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // 将AD数据转换为电压值
				break;
			default:
				printf("输入量程无效\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // 通道号递加，准备换算下一个通道的数据
			if (nChannel > ADPara.LastChannel) // 如果换算到末通道，再回到首通道
			{
				printf("\n"); // 将显示光标位置移到下一项
				nChannel = ADPara.FirstChannel;
			}
		} // 多点数据换算显示
	} // 循环采集

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // 释放AD，停止AD数据转换

ExitReleaseDevice:
	return;
}

//多通道的单点采集
void AD::Mcs()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;   // 首通道0
	ADPara.LastChannel = 3;   // 末通道3
	// 保证通道数是4，实现多通道数据采集
	ADPara.GroundingMode = USB5935_GNDMODE_SE; // 单端

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1; // 采样通道数

	DeviceLgcID = 0;  // 设备ID号, 假设系统中只有一个USB5935设备，即DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID); // 创建设备对象
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara); // 初始化AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 1;
	nRemainder = 0;
	nReadSizeWords = 1 - nRemainder;   // 读取数据的大小
	while (!_kbhit()) // kbhit()探测用户是否有按键动作,若有按键则退出
	{
		printf("请等待，您可以按任意键退出，但请不要直接关闭窗口强制退出...\n");
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) // 读取AD转换数据
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 1; Index++) // 总共显示1个点的AD数据
		{
			switch (InputRange) // 根据量程选择，将AD原码按相应公式换算成电压值
			{
			case USB5935_INPUT_N10000_P10000mV: // ±10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N5000_P5000mV: // ±5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N2500_P2500mV: // ±2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_0_P10000mV: // 0～10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // 将AD数据转换为电压值
				break;
			default:
				printf("输入量程无效\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // 通道号递加，准备换算下一个通道的数据
			if (nChannel > ADPara.LastChannel) // 如果换算到末通道，再回到首通道
			{
				printf("\n"); // 将显示光标位置移到下一项
				nChannel = ADPara.FirstChannel;
			}
		} // 多点数据换算显示
	} // 循环采集

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // 释放AD，停止AD数据转换

ExitReleaseDevice:
	return;
}

//多通道的多点采集
void AD::Mcm()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;   // 首通道0
	ADPara.LastChannel = 3;   // 末通道3
	ADPara.GroundingMode = USB5935_GNDMODE_SE; // 单端

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1; // 采样通道数

	DeviceLgcID = 0;  // 设备ID号, 假设系统中只有一个USB5935设备，即DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID); // 创建设备对象
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara); // 初始化AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 64;
	nRemainder = 64 % (nChannelCount * 256);
	nReadSizeWords = 64 - nRemainder;   // 读取数据的大小
	while (!_kbhit()) // kbhit()探测用户是否有按键动作,若有按键则退出
	{
		printf("请等待，您可以按任意键退出，但请不要直接关闭窗口强制退出...\n");
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) // 读取AD转换数据
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 64; Index++) // 总共显示64个点的AD数据
		{
			switch (InputRange) // 根据量程选择，将AD原码按相应公式换算成电压值
			{
			case USB5935_INPUT_N10000_P10000mV: // ±10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N5000_P5000mV: // ±5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_N2500_P2500mV: // ±2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // 将AD数据转换为电压值
				break;
			case USB5935_INPUT_0_P10000mV: // 0～10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // 将AD数据转换为电压值
				break;
			default:
				printf("输入量程无效\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // 通道号递加，准备换算下一个通道的数据
			if (nChannel > ADPara.LastChannel) // 如果换算到末通道，再回到首通道
			{
				printf("\n"); // 将显示光标位置移到下一项
				nChannel = ADPara.FirstChannel;
			}
		} // 多点数据换算显示
	} // 循环采集

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // 释放AD，停止AD数据转换

ExitReleaseDevice:
	return;
}

//单通道的单点输出
void AD::Scso()
{
	BYTE bDOSts[6];


	bDOSts[0] = 1;
	bDOSts[1] = 0;
	bDOSts[2] = 0;
	bDOSts[3] = 0;
	bDOSts[4] = 0;
	bDOSts[5] = 0;
Repeat:

	printf("Press any key to set DO\n\n");
	_getch();
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // 开关量输出
	{
		printf("SetDeviceDO Error...\n");
		_getch();
		return ;
	}

	if (bDOSts[0])  printf("DO0 = On\n"); else printf("DO0 = Off\n");
	/*if (bDOSts[1])  printf("DO1 = On\n"); else printf("DO1 = Off\n");
	if (bDOSts[2])  printf("DO2 = On\n"); else printf("DO2 = Off\n");
	if (bDOSts[3])  printf("DO3 = On\n"); else printf("DO3 = Off\n");
	if (bDOSts[4])  printf("DO4 = On\n"); else printf("DO4 = Off\n");
	if (bDOSts[5])  printf("DO5 = On\n"); else printf("DO5 = Off\n");*/

	printf("\n");
}

//单通道的多点输出
void AD::Scmo()
{
	BYTE bDOSts[6];


	bDOSts[0] = 1;
	bDOSts[1] = 0;
	bDOSts[2] = 0;
	bDOSts[3] = 0;
	bDOSts[4] = 0;
	bDOSts[5] = 0;
Repeat:

	printf("Press any key to set DO\n\n");
	_getch();
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // 开关量输出
	{
		printf("SetDeviceDO Error...\n");
		_getch();
		return;
	}

	if (bDOSts[0])  printf("DO0 = On\n"); else printf("DO0 = Off\n");
	/*if (bDOSts[1])  printf("DO1 = On\n"); else printf("DO1 = Off\n");
	if (bDOSts[2])  printf("DO2 = On\n"); else printf("DO2 = Off\n");
	if (bDOSts[3])  printf("DO3 = On\n"); else printf("DO3 = Off\n");
	if (bDOSts[4])  printf("DO4 = On\n"); else printf("DO4 = Off\n");
	if (bDOSts[5])  printf("DO5 = On\n"); else printf("DO5 = Off\n");*/

	printf("\n");
}

//多通道的单点输出
void AD::Mcso()
{
	BYTE bDOSts[6];


	bDOSts[0] = 1;
	bDOSts[1] = 0;
	bDOSts[2] = 1;
	bDOSts[3] = 0;
	bDOSts[4] = 1;
	bDOSts[5] = 0;
Repeat:

	printf("Press any key to set DO\n\n");
	_getch();
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // 开关量输出
	{
		printf("SetDeviceDO Error...\n");
		_getch();
		return;
	}

	if (bDOSts[0])  printf("DO0 = On\n"); else printf("DO0 = Off\n");
	if (bDOSts[1])  printf("DO1 = On\n"); else printf("DO1 = Off\n");
	if (bDOSts[2])  printf("DO2 = On\n"); else printf("DO2 = Off\n");
	if (bDOSts[3])  printf("DO3 = On\n"); else printf("DO3 = Off\n");
	if (bDOSts[4])  printf("DO4 = On\n"); else printf("DO4 = Off\n");
	if (bDOSts[5])  printf("DO5 = On\n"); else printf("DO5 = Off\n");

	printf("\n");
}

//多通道的多点输出
void AD::Mcmo()
{
	BYTE bDOSts[6];


	bDOSts[0] = 1;
	bDOSts[1] = 0;
	bDOSts[2] = 0;
	bDOSts[3] = 0;
	bDOSts[4] = 0;
	bDOSts[5] = 0;
Repeat:

	printf("Press any key to set DO\n\n");
	_getch();
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // 开关量输出
	{
		printf("SetDeviceDO Error...\n");
		_getch();
		return;
	}

	if (bDOSts[0])  printf("DO0 = On\n"); else printf("DO0 = Off\n");
	/*if (bDOSts[1])  printf("DO1 = On\n"); else printf("DO1 = Off\n");
	if (bDOSts[2])  printf("DO2 = On\n"); else printf("DO2 = Off\n");
	if (bDOSts[3])  printf("DO3 = On\n"); else printf("DO3 = Off\n");
	if (bDOSts[4])  printf("DO4 = On\n"); else printf("DO4 = Off\n");
	if (bDOSts[5])  printf("DO5 = On\n"); else printf("DO5 = Off\n");*/

	printf("\n");
}

int AD::SelectInputRange(void)
{

	LONG InputRange;
Repeat:
	printf("\n");
	printf("0. -10V  ～ +10V\n");
	printf("1. -5V   ～ +5V\n");
	printf("2. -2.5V   ～ +2.5V\n");
	printf("3. 0V    ～ +10V\n");
	printf("Please Select Input Range[0-4]:");
	scanf_s("%d", &InputRange);
	if (InputRange < 0 || InputRange>4) goto Repeat; // 判断用户选择的量程是否合法，不合法，则重新选择
	return InputRange;

	return 0;
}


AD::~AD()
{
	USB5935_ReleaseDevice(hDevice);   // 释放设备对象	
}



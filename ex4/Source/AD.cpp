#include"AD.h"
#include "conio.h"

AD::AD(int DeviceID)
{
	DeviceLgcID = DeviceID;
	// �����豸����
	hDevice = USB5935_CreateDevice(DeviceLgcID); 
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
	}
}

//��ͨ���ĵ���ɼ�
void AD::Scs()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;	// ��ͨ��0
	ADPara.LastChannel = 0;		// ĩͨ��0
	ADPara.GroundingMode = USB5935_GNDMODE_SE;	// ����

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1;	 // ����ͨ����

	DeviceLgcID = 0;	// �豸ID��, ����ϵͳ��ֻ��һ��USB5935�豸����DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID);	// �����豸����
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara);	// ��ʼ��AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 1;
	nRemainder = 0;
	nReadSizeWords = 1 - nRemainder;   // ��ȡ���ݵĴ�С
	while (!_kbhit())	// kbhit()̽���û��Ƿ��а�������,���а������˳�
	{
		printf("��ȴ��������԰�������˳������벻Ҫֱ�ӹرմ���ǿ���˳�...\n");
		// ��ȡADת������
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) 
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 1; Index++) // �ܹ���ʾ1�����AD����
		{
			switch (InputRange) // ��������ѡ�񣬽�ADԭ�밴��Ӧ��ʽ����ɵ�ѹֵ
			{
			case USB5935_INPUT_N10000_P10000mV: // ��10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N5000_P5000mV: // ��5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N2500_P2500mV: // ��2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_0_P10000mV: // 0��10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // ��AD����ת��Ϊ��ѹֵ
				break;
			default:
				printf("����������Ч\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // ͨ���ŵݼӣ�׼��������һ��ͨ��������
			if (nChannel > ADPara.LastChannel) // ������㵽ĩͨ�����ٻص���ͨ��
			{
				printf("\n"); // ����ʾ���λ���Ƶ���һ��
				nChannel = ADPara.FirstChannel;
			}
		} // ������ݻ�����ʾ
	} // ѭ���ɼ�

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // �ͷ�AD��ֹͣAD����ת��

ExitReleaseDevice:
	return;
	
}

//��ͨ���Ķ��ɼ�
void AD::Scm()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;	// ��ͨ��0
	ADPara.LastChannel = 0;		// ĩͨ��0
	//��֤ͨ����Ϊ1
	ADPara.GroundingMode = USB5935_GNDMODE_SE; // ����

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1; // ����ͨ����

	DeviceLgcID = 0;  // �豸ID��, ����ϵͳ��ֻ��һ��USB5935�豸����DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID); // �����豸����
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara); // ��ʼ��AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 64;//��֤ÿ�βɼ�������Ϊ64��ʵ�ֶ��ɼ�
	nRemainder = 64%(nChannelCount*256);
	nReadSizeWords = 64 - nRemainder;   // ��ȡ���ݵĴ�С
	while (!_kbhit()) // kbhit()̽���û��Ƿ��а�������,���а������˳�
	{
		printf("��ȴ��������԰�������˳������벻Ҫֱ�ӹرմ���ǿ���˳�...\n");
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) // ��ȡADת������
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 64; Index++) // �ܹ���ʾ64�����AD����
		{
			switch (InputRange) // ��������ѡ�񣬽�ADԭ�밴��Ӧ��ʽ����ɵ�ѹֵ
			{
			case USB5935_INPUT_N10000_P10000mV: // ��10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N5000_P5000mV: // ��5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N2500_P2500mV: // ��2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_0_P10000mV: // 0��10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // ��AD����ת��Ϊ��ѹֵ
				break;
			default:
				printf("����������Ч\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // ͨ���ŵݼӣ�׼��������һ��ͨ��������
			if (nChannel > ADPara.LastChannel) // ������㵽ĩͨ�����ٻص���ͨ��
			{
				printf("\n"); // ����ʾ���λ���Ƶ���һ��
				nChannel = ADPara.FirstChannel;
			}
		} // ������ݻ�����ʾ
	} // ѭ���ɼ�

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // �ͷ�AD��ֹͣAD����ת��

ExitReleaseDevice:
	return;
}

//��ͨ���ĵ���ɼ�
void AD::Mcs()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;   // ��ͨ��0
	ADPara.LastChannel = 3;   // ĩͨ��3
	// ��֤ͨ������4��ʵ�ֶ�ͨ�����ݲɼ�
	ADPara.GroundingMode = USB5935_GNDMODE_SE; // ����

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1; // ����ͨ����

	DeviceLgcID = 0;  // �豸ID��, ����ϵͳ��ֻ��һ��USB5935�豸����DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID); // �����豸����
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara); // ��ʼ��AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 1;
	nRemainder = 0;
	nReadSizeWords = 1 - nRemainder;   // ��ȡ���ݵĴ�С
	while (!_kbhit()) // kbhit()̽���û��Ƿ��а�������,���а������˳�
	{
		printf("��ȴ��������԰�������˳������벻Ҫֱ�ӹرմ���ǿ���˳�...\n");
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) // ��ȡADת������
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 1; Index++) // �ܹ���ʾ1�����AD����
		{
			switch (InputRange) // ��������ѡ�񣬽�ADԭ�밴��Ӧ��ʽ����ɵ�ѹֵ
			{
			case USB5935_INPUT_N10000_P10000mV: // ��10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N5000_P5000mV: // ��5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N2500_P2500mV: // ��2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_0_P10000mV: // 0��10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // ��AD����ת��Ϊ��ѹֵ
				break;
			default:
				printf("����������Ч\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // ͨ���ŵݼӣ�׼��������һ��ͨ��������
			if (nChannel > ADPara.LastChannel) // ������㵽ĩͨ�����ٻص���ͨ��
			{
				printf("\n"); // ����ʾ���λ���Ƶ���һ��
				nChannel = ADPara.FirstChannel;
			}
		} // ������ݻ�����ʾ
	} // ѭ���ɼ�

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // �ͷ�AD��ֹͣAD����ת��

ExitReleaseDevice:
	return;
}

//��ͨ���Ķ��ɼ�
void AD::Mcm()
{
	char key;
	int InputRange;
	ADPara.FirstChannel = 0;   // ��ͨ��0
	ADPara.LastChannel = 3;   // ĩͨ��3
	ADPara.GroundingMode = USB5935_GNDMODE_SE; // ����

	InputRange = SelectInputRange();
	ADPara.InputRange = InputRange;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1; // ����ͨ����

	DeviceLgcID = 0;  // �豸ID��, ����ϵͳ��ֻ��һ��USB5935�豸����DeviceLgcID=0;
	hDevice = USB5935_CreateDevice(DeviceLgcID); // �����豸����
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("Create Device Error\n");
		return;
	}

	bReturn = USB5935_InitDeviceAD(hDevice, &ADPara); // ��ʼ��AD
	if (!bReturn)
	{
		printf("USB5935_InitDeviceAD Error\n");
		_getch();
		goto ExitReleaseDevice;
	}

	nReadSizeWords = 64;
	nRemainder = 64 % (nChannelCount * 256);
	nReadSizeWords = 64 - nRemainder;   // ��ȡ���ݵĴ�С
	while (!_kbhit()) // kbhit()̽���û��Ƿ��а�������,���а������˳�
	{
		printf("��ȴ��������԰�������˳������벻Ҫֱ�ӹرմ���ǿ���˳�...\n");
		if (!USB5935_ReadDeviceAD(hDevice, ADBuffer, nReadSizeWords, &nRetWords)) // ��ȡADת������
		{
			printf("ReadDeviceAD Error...\n");
			_getch();
			goto ExitReleaseDeviceAD;
		}

		int nChannel = ADPara.FirstChannel;
		for (int Index = 0; Index < 64; Index++) // �ܹ���ʾ64�����AD����
		{
			switch (InputRange) // ��������ѡ�񣬽�ADԭ�밴��Ӧ��ʽ����ɵ�ѹֵ
			{
			case USB5935_INPUT_N10000_P10000mV: // ��10V
				Volt = (float)((20000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 10000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N5000_P5000mV: // ��5V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 5000.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_N2500_P2500mV: // ��2.5V
				Volt = (float)((5000.00 / 8192) * (ADBuffer[Index] & 0x1FFF) - 2500.00); // ��AD����ת��Ϊ��ѹֵ
				break;
			case USB5935_INPUT_0_P10000mV: // 0��10V
				Volt = (float)((10000.00 / 8192) * (ADBuffer[Index] & 0x1FFF)); // ��AD����ת��Ϊ��ѹֵ
				break;
			default:
				printf("����������Ч\n");
				break;
			}

			printf("[AI%d]=%8.2f\t", nChannel, Volt);
			nChannel++; // ͨ���ŵݼӣ�׼��������һ��ͨ��������
			if (nChannel > ADPara.LastChannel) // ������㵽ĩͨ�����ٻص���ͨ��
			{
				printf("\n"); // ����ʾ���λ���Ƶ���һ��
				nChannel = ADPara.FirstChannel;
			}
		} // ������ݻ�����ʾ
	} // ѭ���ɼ�

ExitReleaseDeviceAD:
	USB5935_ReleaseDeviceAD(hDevice); // �ͷ�AD��ֹͣAD����ת��

ExitReleaseDevice:
	return;
}

//��ͨ���ĵ������
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
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // ���������
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

//��ͨ���Ķ�����
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
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // ���������
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

//��ͨ���ĵ������
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
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // ���������
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

//��ͨ���Ķ�����
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
	if (!USB5935_SetDeviceDO(hDevice, bDOSts)) // ���������
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
	printf("0. -10V  �� +10V\n");
	printf("1. -5V   �� +5V\n");
	printf("2. -2.5V   �� +2.5V\n");
	printf("3. 0V    �� +10V\n");
	printf("Please Select Input Range[0-4]:");
	scanf_s("%d", &InputRange);
	if (InputRange < 0 || InputRange>4) goto Repeat; // �ж��û�ѡ��������Ƿ�Ϸ������Ϸ���������ѡ��
	return InputRange;

	return 0;
}


AD::~AD()
{
	USB5935_ReleaseDevice(hDevice);   // �ͷ��豸����	
}



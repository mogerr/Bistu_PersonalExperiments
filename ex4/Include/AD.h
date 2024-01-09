#pragma once
//  Ԥ����ͷ�ļ�, ����vs2019����"Ԥ����ͷ"
//#include"stdafx.h"
// 20230110 ���Ƽ�ʹ��"Ԥ����ͷ"

#include <iostream>
#include <string>
#include <Windows.h>

// ������ Include ·��
// ���磺D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64
#include"Usb5935.h"

// ������vc "��Ŀ¼"
// Ŀ¼һ��D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64\amd64
// �����е��ļ�
// USB5935.sys
// USB5935_32.dll
// USB5935_64.dll
// Ŀ¼����D:\Program Files (x86)\ART\USB5935\Driver\INF\Win32&Win64
// �����е��ļ�
// USB5935_64.lib
// USB5935_32.lib



//1 ����AD�忨��USB�ӿڣ��࣬��ɶ԰忨�ķ�װ��
//2 ʵ�ֵ�ͨ���Ͷ�ͨ���ĵ���ɼ������ɼ���
//3 ʵ�ֵ�ͨ���Ͷ�ͨ���ĵ����������������

class AD
{
public:
	AD(int);

	void Scs();//��ͨ���ĵ���ɼ�
	void Scm();//��ͨ���Ķ��ɼ�
	void Mcs();//��ͨ���ĵ���ɼ�
	void Mcm();//��ͨ���Ķ��ɼ�
	void Scso();//��ͨ���ĵ������
	void Scmo();//��ͨ���Ķ�����
	void Mcso();//��ͨ���ĵ������
	void Mcmo();//��ͨ���Ķ�����
	int SelectInputRange(void);

	~AD();

private:
	HANDLE hDevice;			// �豸������
	int DeviceLgcID;		// �����豸ID��(�ɰ���JP1����)
	BOOL bReturn;			// �����ķ���ֵ
	int nReadSizeWords;		// ÿ�ζ�ȡAD���ݸ���
	LONG nRetWords = 0;     // ʵ�ʶ�ȡ�����ݸ���
	int nChannelCount = 0;  // ����ͨ����
	WORD ADBuffer[2048];	// ����AD ���ݵĻ�����
	float Volt;				// ��ADԭʼ����ת��Ϊ��ѹֵ
	int nRemainder = 0;
	USB5935_PARA_AD ADPara; // ��ʼ��AD�Ĳ����ṹ
	
	
};

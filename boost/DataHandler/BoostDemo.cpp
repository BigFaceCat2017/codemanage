// BoostDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataHandler/DataHandler.h"
#include <iostream>

// ����Windows.h����Ϊʹ��Sleep����
#include <Windows.h>

// Demo����ʾ�����ʹ��CWnQueue, CWnEvent, CWnLock, CWnScopedLock�����ʹ�÷���
// CWnLock, CWnScopedLock��ʹ�÷��������Բο�CWnQueue���ʵ��
// CWnQueue, CWnEvent��ʹ�ã��ɲο�CDataHandler����̳����ʹ��

class CDemoDataHandler : public CDataHandler<int>
{
public:
	CDemoDataHandler(void){}
	~CDemoDataHandler(){}
protected:
	// �������ݵĺ�������������ʱ��
	virtual void DataFunc(int& t)
	{
		std::cout << t << std::endl;
	}
};

// ��CDemoDataHandler��ʹ���п��Կ�����
// �����ݴ�����ʹ�÷ǳ��򵥣�һ�����Ҫʵ��DataFunc��������ʵ�������ݵĽ����봦����̻߳���
// �������ݵĽ�����һ���߳��У����ݵĴ���������һ���߳�
// ����ڴ����������ݵ�����£�����֤ȯ��ҵ��������Ч��
// �����Ա�֤���յļ�ʱ�ԣ������ᵼ���������ݴ����ڵ�ӵ��������������ݶ�ʧ
// �˻����Ѿ�Ӧ���ڡ��Ϻ������Ѷ����Feedhandler���ݷ�������
int _tmain(int argc, _TCHAR* argv[])
{
	CDataHandler<int>* pDataHandler = new CDemoDataHandler;

	int val = 0;
	while(true)
	{
		pDataHandler->Put(++val);

		// �ȴ�һ��
		// SleepΪwindows�º������˴���Ϊʾ��ʹ��
		// �����޸�Ϊboost��sleep������������ƽ̨
		Sleep(10);
	}

	return 0;
}
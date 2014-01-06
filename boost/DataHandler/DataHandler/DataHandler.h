#pragma once

// Author: Huangzhidan | great3779@sina.com 
// copyright: @Wind Information Co., Ltd (Wind Info) ShangHai
// Create time: 2011-09-10

// һ���������̼߳䴫�����ݵ��ࡣ������������ڣ�
// 1. ��ƽ̨
// 2. ���߳�ͨ�ż�Ƚ��ѵ��̰߳�ȫ���ź�֪ͨ�Ȼ��ƾ���װ�ڶ�����
// 3. �������ݵĴ�����ȫ�����¼�֪ͨ��������ݵ���תЧ���Լ����������ǳ��ߣ��Ѿ�ʹ���ڹ�˾�����ƱFeedHandler�ϣ�����������ͻ��ÿ��500,000������
// 4. �ӿڼ򵥣�ʹ�÷ǳ����㣨�ɲο�BoostDemo����

// ʹ�÷���
// CDataHandler��һ�����࣬ʹ��ʱ�������������м̳С�
// �̳�����дDataThread��DataFunc������һ������½�����дDataFunc�������ɣ�

#include "AtomQueue/WnQueue.h"
#include "Synchronous/WnEvent.h"
#include <boost/thread.hpp>

// a pure virtual function
template <class T> class CDataHandler
{
public:
	CDataHandler(void) {Start();}
	virtual ~CDataHandler() {}

public:
	// ����֪ͨ�ӿڣ�һ�㲻����ã�
	void NotifyOne() {m_event.notify_one();}

	// ȫ��֪ͨ�ӿڣ�һ�㲻����ã�
	void NotifyAll() {m_event.notify_all();}

	// ����������
	void Put(T& t)
	{
		m_record_set.push(t);

		// ����֪ͨ�ź�
		m_event.notify_one();
	}

	// ��ȡ������buffer size�Ľӿ�
	int BufferSize() { return m_record_set.size(); }

protected:
	// �������ݵ��̣߳���������ʱ��
	virtual void DataThread()
	{
		while(true)
		{
			m_event.wait();
			while(!m_record_set.empty())
			{
				T t;
				if(m_record_set.get(t))
				{
					DataFunc(t);
				}
			}
		}
	}

	// �������ݵĺ�������������ʱ��
	virtual void DataFunc(T& t) {}

// ����Ϊ�ڲ�����
protected:
	// ��ʼ����
	void Start()
	{
		boost::thread t(&CDataHandler::DataThread, this);
	}

protected:
	// �����ݼ�
	CWnQueue<T> m_record_set;

	// �ź�
	CWnEvent m_event;	
};

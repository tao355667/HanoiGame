#pragma once
#include <chrono>
#include <iostream>
using namespace std::chrono;
class MyClock
{
protected:
	steady_clock::time_point start, end;//��¼ʱ��������յ�
public:
	void resetClock();	//��ʼ��ʱ������ǰʱ����Ϊ0��
	int getClock();		//��ȡ��ǰ��ʱʱ��
};


#pragma once
#include <chrono>
#include <iostream>
using namespace std::chrono;
class MyClock
{
protected:
	steady_clock::time_point start, end;//记录时间的起点和终点
public:
	void resetClock();	//开始定时（将当前时刻置为0）
	int getClock();		//获取当前定时时间
};


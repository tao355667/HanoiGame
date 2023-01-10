#pragma once
#include "BasicWidget.h"
#include "graphics.h"
class MoveTowerButton :
	public BasicWidget
{
	ExMessage m_msg;
	bool isStart = false;//该按键是否是起点
public:
	MoveTowerButton(int x, int y, int w, int h);
	void show()override;	//显示按键
	bool isin();			//鼠标是否在当前按钮上
	bool isClicked();		//鼠标是否点击了按钮
	void eventLoop(const ExMessage& msg);//传入鼠标事件
	void setIsStart();		//该按键是起点
	void resetIsStart();	//该按键不是起点
	void traIsStart();		//是/不是起点，状态转换
};


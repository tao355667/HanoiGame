#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "graphics.h"
#include <string>
class PushButton :public BasicWidget, public Text
{
	ExMessage m_msg;//消息
public:
	PushButton(const std::string& text = "BUTTON", int x = 0, int y = 0, int w = 300, int h = 50, int textSize = 50);
	void setText(const std::string& text);//重新设置文字
	void show() override;	//显示按键
	bool isin();			//鼠标是否在当前按钮上
	bool isClicked();		//鼠标是否点击了按钮
	void eventLoop(const ExMessage& msg);//传入鼠标键盘消息
};


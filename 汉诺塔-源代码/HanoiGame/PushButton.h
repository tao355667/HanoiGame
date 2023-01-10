#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "graphics.h"
#include <string>
class PushButton :public BasicWidget, public Text
{
	ExMessage m_msg;//��Ϣ
public:
	PushButton(const std::string& text = "BUTTON", int x = 0, int y = 0, int w = 300, int h = 50, int textSize = 50);
	void setText(const std::string& text);//������������
	void show() override;	//��ʾ����
	bool isin();			//����Ƿ��ڵ�ǰ��ť��
	bool isClicked();		//����Ƿ����˰�ť
	void eventLoop(const ExMessage& msg);//������������Ϣ
};


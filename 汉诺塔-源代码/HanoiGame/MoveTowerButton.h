#pragma once
#include "BasicWidget.h"
#include "graphics.h"
class MoveTowerButton :
	public BasicWidget
{
	ExMessage m_msg;
	bool isStart = false;//�ð����Ƿ������
public:
	MoveTowerButton(int x, int y, int w, int h);
	void show()override;	//��ʾ����
	bool isin();			//����Ƿ��ڵ�ǰ��ť��
	bool isClicked();		//����Ƿ����˰�ť
	void eventLoop(const ExMessage& msg);//��������¼�
	void setIsStart();		//�ð��������
	void resetIsStart();	//�ð����������
	void traIsStart();		//��/������㣬״̬ת��
};


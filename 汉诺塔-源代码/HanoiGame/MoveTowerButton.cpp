#include "MoveTowerButton.h"
#include "graphics.h"

MoveTowerButton::MoveTowerButton(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
}
void MoveTowerButton::show()
{
	//���Ʋ㣬��ɫ�����仯
	if (isStart)
		setfillcolor(RGB(255, 20, 10));
	else if (isin())//����ڰ�����
		setfillcolor(YELLOW);
	else//����ԭʼ״̬
		setfillcolor(BROWN);
	setlinestyle(PS_SOLID, 3);//������ʽ
	setlinecolor(WHITE);//����ɫ
	fillrectangle(m_x - m_w / 2, m_y - m_h / 2, m_x + m_w / 2, m_y + m_h / 2);
}

bool MoveTowerButton::isin()
{
	if (m_msg.x >= m_x - m_w / 2 && m_msg.x <= m_x + m_w / 2 && m_msg.y >= m_y - m_h / 2 && m_msg.y <= m_y + m_h / 2)
	{//����ڰ�ť��
		return true;
	}
	return false;
}

bool MoveTowerButton::isClicked()
{
	if (m_msg.x >= m_x - m_w / 2 && m_msg.x <= m_x + m_w / 2 && m_msg.y >= m_y - m_h / 2 && m_msg.y <= m_y + m_h / 2)
	{//����ڰ�ť��
		if (m_msg.message == WM_LBUTTONDOWN)
		{//��걻���
			return true;
		}
	}
	return false;
}

void MoveTowerButton::eventLoop(const ExMessage& msg)
{
	m_msg = msg;
}

void MoveTowerButton::setIsStart()
{
	isStart = true;
}

void MoveTowerButton::resetIsStart()
{
	isStart = false;
}

void MoveTowerButton::traIsStart()
{
	isStart = !isStart;
}

#include "MoveTowerButton.h"
#include "graphics.h"

MoveTowerButton::MoveTowerButton(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
}
void MoveTowerButton::show()
{
	//绘制层，颜色随鼠标变化
	if (isStart)
		setfillcolor(RGB(255, 20, 10));
	else if (isin())//鼠标在按键上
		setfillcolor(YELLOW);
	else//按键原始状态
		setfillcolor(BROWN);
	setlinestyle(PS_SOLID, 3);//线条样式
	setlinecolor(WHITE);//线颜色
	fillrectangle(m_x - m_w / 2, m_y - m_h / 2, m_x + m_w / 2, m_y + m_h / 2);
}

bool MoveTowerButton::isin()
{
	if (m_msg.x >= m_x - m_w / 2 && m_msg.x <= m_x + m_w / 2 && m_msg.y >= m_y - m_h / 2 && m_msg.y <= m_y + m_h / 2)
	{//鼠标在按钮上
		return true;
	}
	return false;
}

bool MoveTowerButton::isClicked()
{
	if (m_msg.x >= m_x - m_w / 2 && m_msg.x <= m_x + m_w / 2 && m_msg.y >= m_y - m_h / 2 && m_msg.y <= m_y + m_h / 2)
	{//鼠标在按钮上
		if (m_msg.message == WM_LBUTTONDOWN)
		{//鼠标被点击
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

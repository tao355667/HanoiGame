#include "PushButton.h"
#include "graphics.h"
#include "string"
#include "iostream"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h, int textSize)
	:BasicWidget(x, y, w, h), Text(text, textSize)
{

}

void PushButton::setText(const std::string& text)
{
	this->text.assign(text);
}

void PushButton::show()
{
	//绘制按钮，颜色随鼠标变化
	if (isin())
		setfillcolor(YELLOW);
	else
		setfillcolor(RGB(10, 134, 217));
	fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//绘制文字
	settextcolor(BLACK);//文字颜色
	settextstyle(textSize, 0, "楷体");//设置字号、字体
	//文字居中显示在按钮中间
	text_x = m_x + (m_w - textwidth(text.c_str())) / 2;
	text_y = m_y + (m_h - textheight(text.c_str())) / 2;
	showText();//显示文字
}

bool PushButton::isin()
{
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{//鼠标在按钮上
		return true;
	}
	return false;
}

bool PushButton::isClicked()
{
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{//鼠标在按钮上
		if (m_msg.message == WM_LBUTTONDOWN)
		{//按钮被点击
			std::cout << "按钮被点击\n";
			return true;
		}
	}
	return false;
}

void PushButton::eventLoop(const ExMessage& msg)
{
	m_msg = msg;
}

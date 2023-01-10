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
	//���ư�ť����ɫ�����仯
	if (isin())
		setfillcolor(YELLOW);
	else
		setfillcolor(RGB(10, 134, 217));
	fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	//��������
	settextcolor(BLACK);//������ɫ
	settextstyle(textSize, 0, "����");//�����ֺš�����
	//���־�����ʾ�ڰ�ť�м�
	text_x = m_x + (m_w - textwidth(text.c_str())) / 2;
	text_y = m_y + (m_h - textheight(text.c_str())) / 2;
	showText();//��ʾ����
}

bool PushButton::isin()
{
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{//����ڰ�ť��
		return true;
	}
	return false;
}

bool PushButton::isClicked()
{
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{//����ڰ�ť��
		if (m_msg.message == WM_LBUTTONDOWN)
		{//��ť�����
			std::cout << "��ť�����\n";
			return true;
		}
	}
	return false;
}

void PushButton::eventLoop(const ExMessage& msg)
{
	m_msg = msg;
}

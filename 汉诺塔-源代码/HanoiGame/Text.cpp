#include "Text.h"
#include "graphics.h"
#include <string>

Text::Text(const std::string& arr, int textSize, int text_x, int text_y)
{
	//��ʼ�����ݳ�Ա
	text.assign(arr);
	this->textSize = textSize;
	this->text_x = text_x;
	this->text_y = text_y;
}
void Text::showText()
{
	settextcolor(BLACK);//������ɫ
	settextstyle(textSize, 0, "����");//�����ֺš�����
	outtextxy(text_x, text_y, text.c_str());
}

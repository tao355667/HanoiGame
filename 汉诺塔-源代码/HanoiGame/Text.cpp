#include "Text.h"
#include "graphics.h"
#include <string>

Text::Text(const std::string& arr, int textSize, int text_x, int text_y)
{
	//初始化数据成员
	text.assign(arr);
	this->textSize = textSize;
	this->text_x = text_x;
	this->text_y = text_y;
}
void Text::showText()
{
	settextcolor(BLACK);//文字颜色
	settextstyle(textSize, 0, "楷体");//设置字号、字体
	outtextxy(text_x, text_y, text.c_str());
}

#include "Layer.h"
#include "graphics.h"
#include <iostream>
Layer::Layer(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h)
{
}


void Layer::show()
{
	//绘制层
	setfillcolor(RGB(10, 134, 217));
	setlinestyle(PS_SOLID, 3);//线条样式
	setlinecolor(WHITE);//线颜色
	fillrectangle(m_x - m_w / 2, m_y - m_h / 2, m_x + m_w / 2, m_y + m_h / 2);
}

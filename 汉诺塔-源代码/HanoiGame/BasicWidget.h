#pragma once
class BasicWidget
{
protected:
	int m_x;//坐标x
	int m_y;//坐标y
	int m_w;//宽度
	int m_h;//高度
public:
	BasicWidget(int x, int y, int w, int h);
	int x();		//返回坐标x
	int y();		//返回坐标y
	int width();	//返回宽度
	int height();	//返回高度
	void setFixedSize(int w, int h);//重设高宽
	void move(int x, int y);		//移动位置
	virtual void show() = 0;		//纯虚函数，显示控件
};


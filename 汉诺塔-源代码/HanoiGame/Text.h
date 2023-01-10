#pragma once
#include <string>
class Text
{
protected:
	int textSize = 50;	//文字大小
	std::string text;	//文字
	int text_x;			//文字坐标x
	int text_y;			//文字坐标y
public:
	Text(const std::string& arr, int textSize, int text_x = 0, int text_y = 0);
	void showText();//显示文字
};


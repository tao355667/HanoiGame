#pragma once
#include <string>
class Text
{
protected:
	int textSize = 50;	//���ִ�С
	std::string text;	//����
	int text_x;			//��������x
	int text_y;			//��������y
public:
	Text(const std::string& arr, int textSize, int text_x = 0, int text_y = 0);
	void showText();//��ʾ����
};


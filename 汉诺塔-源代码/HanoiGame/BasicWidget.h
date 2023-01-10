#pragma once
class BasicWidget
{
protected:
	int m_x;//����x
	int m_y;//����y
	int m_w;//���
	int m_h;//�߶�
public:
	BasicWidget(int x, int y, int w, int h);
	int x();		//��������x
	int y();		//��������y
	int width();	//���ؿ��
	int height();	//���ظ߶�
	void setFixedSize(int w, int h);//����߿�
	void move(int x, int y);		//�ƶ�λ��
	virtual void show() = 0;		//���麯������ʾ�ؼ�
};


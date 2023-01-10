#pragma once
#include <list>
#include <string>
#include "Layer.h"
#include "MoveTowerButton.h"
#include "graphics.h"
class HanoiTower
{
protected:
	//����������������
	int bottomy = 400;
	int ax = 150;
	int bx = 400;
	int cx = 650;
	//��λ��
	int towerSize = 40;
	//��ѡ�е���,���ڲ���
	int startTower = 0;
	int endTower = 0;
	//��������
	std::list<Layer*> A;
	std::list<Layer*> B;
	std::list<Layer*> C;
	//��Ϸ�̳���,�ⲽ��ָ��
	int nowStep = 0;
	int i = 0;//�����ļ�����
	//��һ����
	int step[64][2] = {};
	//�浵�ļ���
	std::string fileName;
	//�ƶ���ŵ������������
	MoveTowerButton moveA;
	MoveTowerButton moveB;
	MoveTowerButton moveC;
	int stepNum = 0;//�û��ƶ��˼���
	int stepShift = 0;//�û��ƶ��˼�����λ��
public:
	HanoiTower();
	~HanoiTower();
	void initTower(int num);//��ʼ����
	void moveTower(int start, int end);//�ƶ�����ͨ�����
	void move(std::list<Layer*>& s, std::list<Layer*>& e, int end);//�ƶ���
	void showTower();//��ʾ��
	void clearTower();//�����Ԫ��
	void sloveTower(int level, int src, int medium, int dest);//�Զ������
	void clearStep();//��ս�ռ�
	void saveFileTower(int level, int timeShift);//�浵��
	void readFileTower(int& level, int& timeShift);//������ʼ����
};


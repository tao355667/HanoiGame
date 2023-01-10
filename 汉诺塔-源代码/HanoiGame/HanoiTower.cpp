#include "HanoiTower.h"
#include "Layer.h"
#include "graphics.h"
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
HanoiTower::HanoiTower()
	:fileName("./sources/TowerLoad.txt")
	, moveA(150, 460, 246, 80), moveB(400, 460, 246, 80), moveC(650, 460, 246, 80)
{
}
HanoiTower::~HanoiTower()
{
	for (auto it = A.begin(); it != A.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	A.clear();
	for (auto it = B.begin(); it != B.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	B.clear();
	for (auto it = C.begin(); it != C.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	C.clear();
}
void HanoiTower::initTower(int num)
{
	for (int i = num; i >= 1; i--)
	{//�½�num���㣬�Ӵ�С
		int h = towerSize / 2;
		Layer* p = new Layer(ax, bottomy - (num - i) * (towerSize + 1) - h, i * towerSize, towerSize);
		//i * towerSize - h + bottomy + i
		A.push_front(p);
	}
}

void HanoiTower::moveTower(int start, int end)
{
	std::cout << "move " << start << end << "\n";
	startTower = endTower = 0;
	switch (start * 10 + end)
	{
	case 12:
		move(A, B, end);
		break;
	case 13:
		move(A, C, end);
		break;
	case 21:
		move(B, A, end);
		break;
	case 23:
		move(B, C, end);
		break;
	case 31:
		move(C, A, end);
		break;
	case 32:
		move(C, B, end);
		break;
	}

}

void HanoiTower::move(std::list<Layer*>& s, std::list<Layer*>& e, int end)
{
	if (s.size())
	{//s����Ϊ�գ���s�Ķ��ƶ���e�Ķ�
		int endx;
		switch (end)
		{
		case 1:endx = ax; break;
		case 2:endx = bx; break;
		case 3:endx = cx;
		}
		Layer* buf = s.front();//����Ԫ�ػ���
		if (e.size())//e��Ϊ�գ��ƶ���e�����Ϸ�
		{
			if (s.front()->width() < e.front()->width())//���Ҫ���յ�С
			{
				(*buf).move(endx, (*e.front()).y() - 1 - towerSize);//�޸ĵ���Ԫ�ص�����
				stepNum++;//����+1
			}
			else
				return;
		}
		else//e�գ��ƶ���e������Ϸ�
		{
			(*buf).move(endx, bottomy - 1 - towerSize / 2);//�޸ĵ���Ԫ�ص�����
			stepNum++;//����+1
		}

		s.pop_front();//��������Ԫ��
		e.push_front(buf);//��Ԫ��ѹ��e��
	}
}

void HanoiTower::showTower()
{
	//��������
	setlinecolor(BROWN);
	setlinestyle(PS_SOLID, 10);
	line(ax, bottomy, ax, 150);
	line(bx, bottomy, bx, 150);
	line(cx, bottomy, cx, 150);
	//���Ƶ���
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 10);
	line(0, bottomy + 6, 800, bottomy + 6);
	//������
	for (auto it = A.begin(); it != A.end(); it++)
	{
		(*it)->show();//��ʾһ����

	}
	for (auto it = B.begin(); it != B.end(); it++)
	{
		(*it)->show();//��ʾһ����
	}
	for (auto it = C.begin(); it != C.end(); it++)
	{
		(*it)->show();//��ʾһ����
	}
}

void HanoiTower::clearTower()
{
	stepNum = 0;
	stepShift = 0;
	for (auto it = A.begin(); it != A.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	A.clear();
	for (auto it = B.begin(); it != B.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	B.clear();
	for (auto it = C.begin(); it != C.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	C.clear();
}

void HanoiTower::sloveTower(int level, int src, int medium, int dest)
{
	if (level == 1)
	{
		step[i][0] = src;
		step[i][1] = dest;
		i++;
	}
	else
	{
		sloveTower(level - 1, src, dest, medium);
		step[i][0] = src;
		step[i][1] = dest;
		i++;
		sloveTower(level - 1, medium, src, dest);
	}
}

void HanoiTower::clearStep()
{
	i = 0;
	nowStep = 0;
	memset(step, 0, sizeof(step));//������������
}

void HanoiTower::saveFileTower(int level, int finalTime)
{
	std::fstream write(fileName, std::ios::out | std::ios::trunc);//���ļ�
	if (!write.is_open())
	{//��ʧ��
		return;
	}
	//д����
	std::stringstream ss;//�����
	//дA
	ss << A.size() << std::endl;
	for (auto it = A.begin(); it != A.end(); it++)
	{//��ʼ��
		ss << (*it)->x() << "\t" << (*it)->y() << "\t" << (*it)->width() << "\t" << (*it)->height() << "\t";
	}
	ss << std::endl;
	//дB
	ss << B.size() << std::endl;
	for (auto it = B.begin(); it != B.end(); it++)
	{//��ʼ��
		ss << (*it)->x() << "\t" << (*it)->y() << "\t" << (*it)->width() << "\t" << (*it)->height() << "\t";
	}
	ss << std::endl;
	//дC
	ss << C.size() << std::endl;
	for (auto it = C.begin(); it != C.end(); it++)
	{//��ʼ��
		ss << (*it)->x() << "\t" << (*it)->y() << "\t" << (*it)->width() << "\t" << (*it)->height() << "\t";
	}
	ss << std::endl;
	ss << level << std::endl;
	ss << finalTime << std::endl;
	ss << stepNum;
	//����д���ļ�
	write.write(ss.str().c_str(), ss.str().size());
}

void HanoiTower::readFileTower(int& level, int& timeShift)
{
	std::ifstream file;//���ļ�
	file.open(fileName);//���ļ�
	if (!file.is_open())
	{
		std::cout << "�浵�ļ���ʧ��\n";
		return;
	}std::cout << "�浵�ļ��򿪳ɹ�\n";
	int num;

	file >> num;
	for (int i = 0; i < num; i++)
	{//��A
		int x, y, w, h;
		file >> x >> y >> w >> h;
		Layer* p = new Layer(x, y, w, h);
		A.push_back(p);
	}
	file >> num;
	for (int i = 0; i < num; i++)
	{//��B
		int x, y, w, h;
		file >> x >> y >> w >> h;
		Layer* p = new Layer(x, y, w, h);
		B.push_back(p);
	}
	file >> num;
	for (int i = 0; i < num; i++)
	{//��C
		int x, y, w, h;
		file >> x >> y >> w >> h;
		Layer* p = new Layer(x, y, w, h);
		C.push_back(p);
	}
	//��level
	file >> level;
	//��timeShift
	file >> timeShift;
	//��stepNum
	file >> stepNum;

	file.close();//�ر��ļ�

}



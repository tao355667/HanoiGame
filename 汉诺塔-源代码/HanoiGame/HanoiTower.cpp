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
	{//新建num个层，从大到小
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
	{//s顶不为空，将s的顶移动到e的顶
		int endx;
		switch (end)
		{
		case 1:endx = ax; break;
		case 2:endx = bx; break;
		case 3:endx = cx;
		}
		Layer* buf = s.front();//顶部元素缓存
		if (e.size())//e不为空，移动到e顶的上方
		{
			if (s.front()->width() < e.front()->width())//起点要比终点小
			{
				(*buf).move(endx, (*e.front()).y() - 1 - towerSize);//修改弹出元素的坐标
				stepNum++;//步骤+1
			}
			else
				return;
		}
		else//e空，移动到e地面的上方
		{
			(*buf).move(endx, bottomy - 1 - towerSize / 2);//修改弹出元素的坐标
			stepNum++;//步骤+1
		}

		s.pop_front();//弹出顶部元素
		e.push_front(buf);//将元素压入e中
	}
}

void HanoiTower::showTower()
{
	//背景棒子
	setlinecolor(BROWN);
	setlinestyle(PS_SOLID, 10);
	line(ax, bottomy, ax, 150);
	line(bx, bottomy, bx, 150);
	line(cx, bottomy, cx, 150);
	//绘制地面
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 10);
	line(0, bottomy + 6, 800, bottomy + 6);
	//绘制塔
	for (auto it = A.begin(); it != A.end(); it++)
	{
		(*it)->show();//显示一个层

	}
	for (auto it = B.begin(); it != B.end(); it++)
	{
		(*it)->show();//显示一个层
	}
	for (auto it = C.begin(); it != C.end(); it++)
	{
		(*it)->show();//显示一个层
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
	memset(step, 0, sizeof(step));//步骤数组清零
}

void HanoiTower::saveFileTower(int level, int finalTime)
{
	std::fstream write(fileName, std::ios::out | std::ios::trunc);//打开文件
	if (!write.is_open())
	{//打开失败
		return;
	}
	//写数据
	std::stringstream ss;//输出流
	//写A
	ss << A.size() << std::endl;
	for (auto it = A.begin(); it != A.end(); it++)
	{//初始化
		ss << (*it)->x() << "\t" << (*it)->y() << "\t" << (*it)->width() << "\t" << (*it)->height() << "\t";
	}
	ss << std::endl;
	//写B
	ss << B.size() << std::endl;
	for (auto it = B.begin(); it != B.end(); it++)
	{//初始化
		ss << (*it)->x() << "\t" << (*it)->y() << "\t" << (*it)->width() << "\t" << (*it)->height() << "\t";
	}
	ss << std::endl;
	//写C
	ss << C.size() << std::endl;
	for (auto it = C.begin(); it != C.end(); it++)
	{//初始化
		ss << (*it)->x() << "\t" << (*it)->y() << "\t" << (*it)->width() << "\t" << (*it)->height() << "\t";
	}
	ss << std::endl;
	ss << level << std::endl;
	ss << finalTime << std::endl;
	ss << stepNum;
	//将流写入文件
	write.write(ss.str().c_str(), ss.str().size());
}

void HanoiTower::readFileTower(int& level, int& timeShift)
{
	std::ifstream file;//读文件
	file.open(fileName);//打开文件
	if (!file.is_open())
	{
		std::cout << "存档文件打开失败\n";
		return;
	}std::cout << "存档文件打开成功\n";
	int num;

	file >> num;
	for (int i = 0; i < num; i++)
	{//读A
		int x, y, w, h;
		file >> x >> y >> w >> h;
		Layer* p = new Layer(x, y, w, h);
		A.push_back(p);
	}
	file >> num;
	for (int i = 0; i < num; i++)
	{//读B
		int x, y, w, h;
		file >> x >> y >> w >> h;
		Layer* p = new Layer(x, y, w, h);
		B.push_back(p);
	}
	file >> num;
	for (int i = 0; i < num; i++)
	{//读C
		int x, y, w, h;
		file >> x >> y >> w >> h;
		Layer* p = new Layer(x, y, w, h);
		C.push_back(p);
	}
	//读level
	file >> level;
	//读timeShift
	file >> timeShift;
	//读stepNum
	file >> stepNum;

	file.close();//关闭文件

}



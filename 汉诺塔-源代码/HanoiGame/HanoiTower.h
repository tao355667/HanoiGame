#pragma once
#include <list>
#include <string>
#include "Layer.h"
#include "MoveTowerButton.h"
#include "graphics.h"
class HanoiTower
{
protected:
	//三个底座中心坐标
	int bottomy = 400;
	int ax = 150;
	int bx = 400;
	int cx = 650;
	//单位塔
	int towerSize = 40;
	//被选中的塔,用于操作
	int startTower = 0;
	int endTower = 0;
	//三个塔堆
	std::list<Layer*> A;
	std::list<Layer*> B;
	std::list<Layer*> C;
	//游戏教程中,解步骤指针
	int nowStep = 0;
	int i = 0;//计算解的计数器
	//下一步解
	int step[64][2] = {};
	//存档文件名
	std::string fileName;
	//移动汉诺塔的三个按键
	MoveTowerButton moveA;
	MoveTowerButton moveB;
	MoveTowerButton moveC;
	int stepNum = 0;//用户移动了几步
	int stepShift = 0;//用户移动了几步，位移
public:
	HanoiTower();
	~HanoiTower();
	void initTower(int num);//初始化塔
	void moveTower(int start, int end);//移动塔，通过标号
	void move(std::list<Layer*>& s, std::list<Layer*>& e, int end);//移动塔
	void showTower();//显示塔
	void clearTower();//清空塔元素
	void sloveTower(int level, int src, int medium, int dest);//自动求解塔
	void clearStep();//清空解空间
	void saveFileTower(int level, int timeShift);//存档塔
	void readFileTower(int& level, int& timeShift);//读档初始化塔
};


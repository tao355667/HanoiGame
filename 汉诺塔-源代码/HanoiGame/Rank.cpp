#include "Rank.h"
#include "string"
#include <fstream>
#include <sstream>
#include <iostream>
#include "graphics.h"
void Rank::score2time()
{
	for (auto it1 = rankList.begin(), it2 = rankTime.begin(); it1 != rankList.end(); it1++, it2++)
	{//转化
		int f = atoi((*it1).first.c_str());//string变整数
		int s = atoi((*it1).second.c_str());
		int t = atoi((*it1).third.c_str());
		if (f >= 0)
		{
			int fm = f / 60; int fs = f % 60;
			(*it2).first.assign(std::to_string(fm)); (*it2).first.append("分");
			(*it2).first.append(std::to_string(fs)); (*it2).first.append("秒");
		}
		else
		{
			(*it2).first.assign("无");
		}
		if (s >= 0)
		{
			int sm = s / 60; int ss = s % 60;
			(*it2).second.assign(std::to_string(sm)); (*it2).second.append("分");
			(*it2).second.append(std::to_string(ss)); (*it2).second.append("秒");
		}
		else
		{
			(*it2).second.assign("无");
		}
		if (t >= 0)
		{
			int tm = t / 60; int ts = t % 60;
			(*it2).third.assign(std::to_string(tm)); (*it2).third.append("分");
			(*it2).third.append(std::to_string(ts)); (*it2).third.append("秒");
		}
		else
		{
			(*it2).third.assign("无");
		}

	}
}
Rank::Rank()
	:fileName("./sources/Rank.txt")
{
	for (auto it = rankList.begin(); it != rankList.end(); it++)
	{//初始化
		(*it).first.assign("-1");
		(*it).second.assign("-1");
		(*it).third.assign("-1");
	}
}

void Rank::ReadRankFile()
{
	std::fstream read(fileName, std::ios::in);
	if (!read.is_open())
	{//文件没打开
		return;
	}
	for (auto it = rankList.begin(); it != rankList.end(); it++)
	{//读文件
		char buf[1024] = {};
		read.getline(buf, 1024);//读一行
		std::stringstream ss(buf);
		ss >> (*it).first >> (*it).second >> (*it).third;
	}
	read.close();//关闭文件
	score2time();
}

void Rank::SaveRankFile()
{
	std::fstream write(fileName, std::ios::out | std::ios::trunc);
	if (!write.is_open())
	{//打开失败
		return;
	}
	//写数据
	for (auto it = rankList.begin(); it != rankList.end(); it++)
	{//初始化
		std::stringstream ss;
		ss << (*it).first << "\t" << (*it).second << "\t" << (*it).third << std::endl;
		write.write(ss.str().c_str(), ss.str().size());
	}

	write.close();//关闭文件
}

void Rank::showRank()
{
	int base_x = 120, base_y = 80;
	int intervalx = 150; int intervaly = 50;
	//绘制矩形
	setfillcolor(RGB(10, 134, 217));
	fillroundrect(base_x - 50, base_y - 50, base_x + 600, base_y + 400, 10, 10);
	//绘制文字
	settextcolor(BLACK);//文字颜色
	settextstyle(40, 0, "楷体");//设置字号、字体
	outtextxy(base_x, base_y, "难度");
	outtextxy(base_x + intervalx, base_y, "冠军");
	outtextxy(base_x + intervalx * 2, base_y, "亚军");
	outtextxy(base_x + intervalx * 3, base_y, "季军");
	//成绩数据
	settextstyle(30, 0, "微软雅黑");//设置字号、字体
	int i = 1; auto it = rankTime.begin();
	for (; it != rankTime.end(); i++, it++)
	{
		outtextxy(base_x, base_y + intervaly * i, std::to_string(i).c_str());
		outtextxy(base_x + intervalx, base_y + intervaly * i, (*it).first.c_str());
		outtextxy(base_x + intervalx * 2, base_y + intervaly * i, (*it).second.c_str());
		outtextxy(base_x + intervalx * 3, base_y + intervaly * i, (*it).third.c_str());
	}


}

void Rank::newRank(HWND hnd, int level, int time)
{
	//此处将新纪录比对后储存
	int a1 = atoi(rankList.at(level - 1).first.c_str());
	int a2 = atoi(rankList.at(level - 1).second.c_str());
	int a3 = atoi(rankList.at(level - 1).third.c_str());
	if (a1 < 0 || time < a1)
	{
		rankList.at(level - 1).third.assign(rankList.at(level - 1).second);
		rankList.at(level - 1).second.assign(rankList.at(level - 1).first);//后移
		rankList.at(level - 1).first.assign(std::to_string(time));
		std::string text;
		text.append("你破了难度 ");
		text.append(std::to_string(level));
		text.append(" 的记录！\n");
		text.append("目前排名第一！");
		int isok = MessageBox(hnd, text.c_str(), "提示", MB_OK);
		if (isok == IDOK) { printf("你点击了确定\n"); }
	}
	else if (a2 < 0 || time < a2)
	{
		rankList.at(level - 1).third.assign(rankList.at(level - 1).second);
		rankList.at(level - 1).second.assign(std::to_string(time));
		std::string text;
		text.append("你破了难度 ");
		text.append(std::to_string(level));
		text.append(" 的记录！\n");
		text.append("目前排名第二！");
		int isok = MessageBox(hnd, text.c_str(), "提示", MB_OK);
		if (isok == IDOK) { printf("你点击了确定\n"); }
	}
	else if (a3 < 0 || time < a3)
	{
		rankList.at(level - 1).third.assign(std::to_string(time));
		std::string text;
		text.append("你破了难度 ");
		text.append(std::to_string(level));
		text.append(" 的记录！\n");
		text.append("目前排名第三！");
		int isok = MessageBox(hnd, text.c_str(), "提示", MB_OK);
		if (isok == IDOK) { printf("你点击了确定\n"); }
	}
	score2time();//转换为x分x秒
	SaveRankFile();//将记录存入文件
}


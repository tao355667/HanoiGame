#include "Record.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "graphics.h"
Record::~Record()
{//析构函数中释放申请的空间
	for (auto it = RecordList.begin(); it != RecordList.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	RecordList.clear();
}
void Record::addRecord(int level, int step, int time, int isSuccess)
{
	RecordData* p = new RecordData;
	if (!p)return;//申请空间失败
	//新元素赋值
	p->level = level;
	p->step = step;
	p->time = time;
	p->isSuccess = isSuccess;
	RecordList.push_back(p);//插入新元素
}

void Record::showRecord()
{
	int w = 110, h = 40;
	int x = 130, y = 100;
	//绘制背景
	setfillcolor(RGB(10, 134, 217));
	fillroundrect(x - 50, y - 50, x + 600, y + 400, 10, 10);
	//绘制文字
	settextcolor(BLACK);//文字颜色
	settextstyle(30, 0, "楷体");//设置字号、字体
	//显示表头
	outtextxy(x, y - h, "序号");
	outtextxy(x + w, y - h, "难度");
	outtextxy(x + w * 2, y - h, "步数");
	outtextxy(x + w * 3, y - h, "用时/秒");
	outtextxy(x + w * 4, y - h, "是否成功");
	//显示内容
	for (int i = beginRecordPage; i < beginRecordPage + 10; i++)
	{
		if (i < RecordList.size())
		{
			RecordData* it = RecordList[i];
			std::string buf;//缓冲区
			outtextxy(x, y, std::to_string(i + 1).c_str());
			outtextxy(x + w, y, std::to_string(it->level).c_str());
			outtextxy(x + w * 2, y, std::to_string(it->step).c_str());
			outtextxy(x + w * 3, y, std::to_string(it->time).c_str());
			if (it->isSuccess) buf.assign("是");
			else buf.assign("否");
			outtextxy(x + w * 4, y, buf.c_str());
			y += h;
		}
	}
}

void Record::saveRecord()
{
	std::ofstream ofs;
	ofs.open("./sources/Record.txt", std::ios::out);
	for (auto it : RecordList)
	{
		ofs << it->level << "\t" << it->step << "\t" << it->time << "\t" << it->isSuccess << "\n";
	}
	ofs.close();
}

void Record::readRecord()
{

	std::ifstream ifs;
	ifs.open("./sources/Record.txt");
	while (ifs.good())
	{
		int level, step, time, isSuccess;
		ifs >> level >> step >> time >> isSuccess;
		addRecord(level, step, time, isSuccess);
	}
	ifs.close();
	std::cout << "读记录文件成功！\n";
}

void Record::addRecordPage()
{
	if (beginRecordPage + 10 < RecordList.size())
	{
		beginRecordPage += 10;
	}
}

void Record::subRecordPage()
{
	if (beginRecordPage - 10 >= 0)
	{
		beginRecordPage -= 10;
	}
}

void Record::startRecordPage()
{
	beginRecordPage = 0;
}

void Record::endRecordPage()
{
	int i = 0;
	while (i + 10 < RecordList.size())
	{
		i += 10;
	}
	beginRecordPage = i;
}



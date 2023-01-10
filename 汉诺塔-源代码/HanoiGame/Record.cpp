#include "Record.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "graphics.h"
Record::~Record()
{//�����������ͷ�����Ŀռ�
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
	if (!p)return;//����ռ�ʧ��
	//��Ԫ�ظ�ֵ
	p->level = level;
	p->step = step;
	p->time = time;
	p->isSuccess = isSuccess;
	RecordList.push_back(p);//������Ԫ��
}

void Record::showRecord()
{
	int w = 110, h = 40;
	int x = 130, y = 100;
	//���Ʊ���
	setfillcolor(RGB(10, 134, 217));
	fillroundrect(x - 50, y - 50, x + 600, y + 400, 10, 10);
	//��������
	settextcolor(BLACK);//������ɫ
	settextstyle(30, 0, "����");//�����ֺš�����
	//��ʾ��ͷ
	outtextxy(x, y - h, "���");
	outtextxy(x + w, y - h, "�Ѷ�");
	outtextxy(x + w * 2, y - h, "����");
	outtextxy(x + w * 3, y - h, "��ʱ/��");
	outtextxy(x + w * 4, y - h, "�Ƿ�ɹ�");
	//��ʾ����
	for (int i = beginRecordPage; i < beginRecordPage + 10; i++)
	{
		if (i < RecordList.size())
		{
			RecordData* it = RecordList[i];
			std::string buf;//������
			outtextxy(x, y, std::to_string(i + 1).c_str());
			outtextxy(x + w, y, std::to_string(it->level).c_str());
			outtextxy(x + w * 2, y, std::to_string(it->step).c_str());
			outtextxy(x + w * 3, y, std::to_string(it->time).c_str());
			if (it->isSuccess) buf.assign("��");
			else buf.assign("��");
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
	std::cout << "����¼�ļ��ɹ���\n";
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



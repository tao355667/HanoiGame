#include "Rank.h"
#include "string"
#include <fstream>
#include <sstream>
#include <iostream>
#include "graphics.h"
void Rank::score2time()
{
	for (auto it1 = rankList.begin(), it2 = rankTime.begin(); it1 != rankList.end(); it1++, it2++)
	{//ת��
		int f = atoi((*it1).first.c_str());//string������
		int s = atoi((*it1).second.c_str());
		int t = atoi((*it1).third.c_str());
		if (f >= 0)
		{
			int fm = f / 60; int fs = f % 60;
			(*it2).first.assign(std::to_string(fm)); (*it2).first.append("��");
			(*it2).first.append(std::to_string(fs)); (*it2).first.append("��");
		}
		else
		{
			(*it2).first.assign("��");
		}
		if (s >= 0)
		{
			int sm = s / 60; int ss = s % 60;
			(*it2).second.assign(std::to_string(sm)); (*it2).second.append("��");
			(*it2).second.append(std::to_string(ss)); (*it2).second.append("��");
		}
		else
		{
			(*it2).second.assign("��");
		}
		if (t >= 0)
		{
			int tm = t / 60; int ts = t % 60;
			(*it2).third.assign(std::to_string(tm)); (*it2).third.append("��");
			(*it2).third.append(std::to_string(ts)); (*it2).third.append("��");
		}
		else
		{
			(*it2).third.assign("��");
		}

	}
}
Rank::Rank()
	:fileName("./sources/Rank.txt")
{
	for (auto it = rankList.begin(); it != rankList.end(); it++)
	{//��ʼ��
		(*it).first.assign("-1");
		(*it).second.assign("-1");
		(*it).third.assign("-1");
	}
}

void Rank::ReadRankFile()
{
	std::fstream read(fileName, std::ios::in);
	if (!read.is_open())
	{//�ļ�û��
		return;
	}
	for (auto it = rankList.begin(); it != rankList.end(); it++)
	{//���ļ�
		char buf[1024] = {};
		read.getline(buf, 1024);//��һ��
		std::stringstream ss(buf);
		ss >> (*it).first >> (*it).second >> (*it).third;
	}
	read.close();//�ر��ļ�
	score2time();
}

void Rank::SaveRankFile()
{
	std::fstream write(fileName, std::ios::out | std::ios::trunc);
	if (!write.is_open())
	{//��ʧ��
		return;
	}
	//д����
	for (auto it = rankList.begin(); it != rankList.end(); it++)
	{//��ʼ��
		std::stringstream ss;
		ss << (*it).first << "\t" << (*it).second << "\t" << (*it).third << std::endl;
		write.write(ss.str().c_str(), ss.str().size());
	}

	write.close();//�ر��ļ�
}

void Rank::showRank()
{
	int base_x = 120, base_y = 80;
	int intervalx = 150; int intervaly = 50;
	//���ƾ���
	setfillcolor(RGB(10, 134, 217));
	fillroundrect(base_x - 50, base_y - 50, base_x + 600, base_y + 400, 10, 10);
	//��������
	settextcolor(BLACK);//������ɫ
	settextstyle(40, 0, "����");//�����ֺš�����
	outtextxy(base_x, base_y, "�Ѷ�");
	outtextxy(base_x + intervalx, base_y, "�ھ�");
	outtextxy(base_x + intervalx * 2, base_y, "�Ǿ�");
	outtextxy(base_x + intervalx * 3, base_y, "����");
	//�ɼ�����
	settextstyle(30, 0, "΢���ź�");//�����ֺš�����
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
	//�˴����¼�¼�ȶԺ󴢴�
	int a1 = atoi(rankList.at(level - 1).first.c_str());
	int a2 = atoi(rankList.at(level - 1).second.c_str());
	int a3 = atoi(rankList.at(level - 1).third.c_str());
	if (a1 < 0 || time < a1)
	{
		rankList.at(level - 1).third.assign(rankList.at(level - 1).second);
		rankList.at(level - 1).second.assign(rankList.at(level - 1).first);//����
		rankList.at(level - 1).first.assign(std::to_string(time));
		std::string text;
		text.append("�������Ѷ� ");
		text.append(std::to_string(level));
		text.append(" �ļ�¼��\n");
		text.append("Ŀǰ������һ��");
		int isok = MessageBox(hnd, text.c_str(), "��ʾ", MB_OK);
		if (isok == IDOK) { printf("������ȷ��\n"); }
	}
	else if (a2 < 0 || time < a2)
	{
		rankList.at(level - 1).third.assign(rankList.at(level - 1).second);
		rankList.at(level - 1).second.assign(std::to_string(time));
		std::string text;
		text.append("�������Ѷ� ");
		text.append(std::to_string(level));
		text.append(" �ļ�¼��\n");
		text.append("Ŀǰ�����ڶ���");
		int isok = MessageBox(hnd, text.c_str(), "��ʾ", MB_OK);
		if (isok == IDOK) { printf("������ȷ��\n"); }
	}
	else if (a3 < 0 || time < a3)
	{
		rankList.at(level - 1).third.assign(std::to_string(time));
		std::string text;
		text.append("�������Ѷ� ");
		text.append(std::to_string(level));
		text.append(" �ļ�¼��\n");
		text.append("Ŀǰ����������");
		int isok = MessageBox(hnd, text.c_str(), "��ʾ", MB_OK);
		if (isok == IDOK) { printf("������ȷ��\n"); }
	}
	score2time();//ת��Ϊx��x��
	SaveRankFile();//����¼�����ļ�
}


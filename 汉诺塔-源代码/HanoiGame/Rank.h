#pragma once
#include "graphics.h"
#include <string>
#include <array>

typedef struct
{
	std::string first;
	std::string second;
	std::string third;
}Score;
class Rank
{
protected:
	std::array<Score, 6> rankList;//6���Ѷȵȼ����洢����
	std::array<Score, 6> rankTime;//6���Ѷȵȼ���x��x���ַ�
	std::string fileName;
	void  score2time();//����ת��Ϊx��x��
public:
	Rank();
	void ReadRankFile();//���ļ�
	void SaveRankFile();//д�ļ�
	void showRank();//��ʾ���а�
	void newRank(HWND hnd, int level, int time);//�¼�¼
};


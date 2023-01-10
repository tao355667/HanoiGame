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
	std::array<Score, 6> rankList;//6个难度等级，存储秒数
	std::array<Score, 6> rankTime;//6个难度等级，x分x秒字符
	std::string fileName;
	void  score2time();//秒数转换为x秒x分
public:
	Rank();
	void ReadRankFile();//读文件
	void SaveRankFile();//写文件
	void showRank();//显示排行榜
	void newRank(HWND hnd, int level, int time);//新纪录
};


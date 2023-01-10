#pragma once
#include "graphics.h"
#include "PushButton.h"
#include <vector>
#include <string>
#include "Text.h"
#include "Rank.h"
#include "Layer.h"
#include "HanoiTower.h"
#include "MoveTowerButton.h"
#include "MyClock.h"
#include "Record.h"
class Game
	:public Rank, public HanoiTower, public MyClock, public Record
{
	int w = 800, h = 600;//宽高
	int level = 6;//游戏难度
	bool Volume = true;//默认声音开
	//读取存档的时间值，计算时间时候增加此偏移值，新游戏偏移值为0
	int timeShift = 0;
	//游戏胜利时的时间值
	int finalTime = 0;
	//游戏菜单状态
	enum Operator {
		menu,			//主菜单
		newGame,		//新游戏难度选择
		newGame_Game,	//新游戏游戏界面
		readFile,		//读取游戏存档
		rank,			//排行榜
		tutorial,		//游戏教程难度选择
		tutorial_Game,	//游戏教程游戏界面
		GameRecord,		//查看游戏记录
		HowToPlay,		//查看游戏说明
		exitGame		//退出游戏
	};
	Operator op = menu;//菜单状态
	IMAGE bkImage;//背景图
	IMAGE htpImage;//游戏说明图
	HWND hnd;//窗口句柄
	//主菜单控件
	std::vector<PushButton*> menu_btns;//主菜单按键
	PushButton VolumeButton;//音乐按键
	PushButton MenuButton;//主菜单按键
	Text menu_text_hnt;//主菜单标题文字
	//选择难度的控件
	Text level_text_hnt;//难度选择文字
	std::vector<PushButton*> level_btns;//难度按键
	//教程按键（上一步，下一步）
	PushButton preStepButton;
	PushButton nexStepButton;
	//保存按键
	PushButton saveButton;
	//查看记录的按键
	PushButton prePageButton;//上一页
	PushButton nexPageButton;//下一页
	PushButton staPageButton;//首页
	PushButton endPageButton;//尾页
	PushButton saveRecordButton;//尾页
	//与用户输入无关的信息
	void undateWithoutInput();
	// 与用户输入有关的信息
	void undateWithInput();
	//绘制游戏画面
	void GameDraw();
	//游戏背景音乐
	void BGM();
	//游戏结束
	void gameover(int gameOverState = 1);//默认赢了
	//教学结束
	void tutorialover();
	//显示剩余时间
	void showTimeRemain(int level);
	//将游戏记录存档
	void saveGame();
	//加载存档
	void loadGame();
	//返回主菜单要做的事
	void MainMenu();
public:
	//Game构造函数
	Game();
	//Game析构函数
	~Game();
	//游戏初始化
	void init();
	//游戏主循环
	void loop();
};


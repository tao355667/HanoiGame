#include "Game.h"
#include "graphics.h"
#include <mmsystem.h>//包含多媒体设备接口头文件
#include <iostream>
#include <vector>
#include "Text.h"
#include "Layer.h"
#include "MoveTowerButton.h"
#include "MyClock.h"
#include "graphics.h"
#include "windows.h"
#pragma comment(lib,"Winmm.lib")//加载静态库，播放音乐
//构造函数
Game::Game()
	:menu_text_hnt("汉诺塔", 100, 250, 60), VolumeButton("关闭音乐", 0, 579, 100, 20, 20)
	, level_text_hnt("选择难度", 80, 250, 50), MenuButton("主菜单", 700, 579, 100, 20, 20)
	, preStepButton("上一步", 150, 450, 200, 50, 50), nexStepButton("下一步", 450, 450, 200, 50, 50)
	, saveButton("保存", 345, 525, 110, 50)
	, prePageButton("上一页", 150, 510, 150, 30, 30), nexPageButton("下一页", 350, 510, 150, 30, 30)
	, staPageButton("首页", 150, 550, 150, 30, 30), endPageButton("尾页", 350, 550, 150, 30, 30)
	, saveRecordButton("保存记录", 550, 510, 150, 30, 30)
{
	//初始化窗口
	initgraph(w, h, SHOWCONSOLE);//窗口初始化，带控制台
	//initgraph(w, h);	//窗口初始化
	hnd = GetHWnd();		//窗口句柄
	SetWindowText(hnd, "汉诺塔|计科二学位1班 202283730040 许辰涛");//设置窗口标题
	loadimage(&bkImage, "./sources/bkImage.jpg", 800, 600);//读取背景文件
	loadimage(&htpImage, "./sources/HowToPlay.png", 800, 600);//读取游戏说明文件
	setbkmode(TRANSPARENT);//设置背景模式，透明（文字）
	//主界面按钮初始化
	menu_btns.push_back(new PushButton("新游戏"));
	menu_btns.push_back(new PushButton("读取存档"));
	menu_btns.push_back(new PushButton("排行榜"));
	menu_btns.push_back(new PushButton("游戏教学"));
	menu_btns.push_back(new PushButton("游戏记录"));
	menu_btns.push_back(new PushButton("游戏说明"));
	menu_btns.push_back(new PushButton("退出游戏"));
	//设置按键位置
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(300, 50);//设置按键宽高
		//计算按键位置
		int bx = (w - menu_btns[i]->width()) / 2;
		int by = i * (menu_btns[i]->height() + 10) + 180;
		menu_btns[i]->move(bx, by);//设置按键位置
	}
	//难度按键初始化
	level_btns.push_back(new PushButton("1"));
	level_btns.push_back(new PushButton("2"));
	level_btns.push_back(new PushButton("3"));
	level_btns.push_back(new PushButton("4"));
	level_btns.push_back(new PushButton("5"));
	level_btns.push_back(new PushButton("6"));
	//设置按键位置
	for (int i = 0; i < level_btns.size(); i++)
	{
		level_btns[i]->setFixedSize(200, 50);//设置按键宽高
		//计算按键位置
		int bx = (w - level_btns[i]->width()) / 2;
		int by = i * (level_btns[i]->height() + 10) + 180;
		level_btns[i]->move(bx, by);//设置按键位置
	}
	//读取文件
	ReadRankFile();//读取排行榜
	readRecord();//读取游戏记录
}
Game::~Game()
{
	//释放menu_btns按键
	for (std::vector<PushButton*>::iterator it = menu_btns.begin(); it != menu_btns.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	menu_btns.clear();
	std::cout << "释放内存成功！\n";
}
//游戏初始化
void Game::init()
{
	//播放音乐
	BGM();
}
//与用户输入无关的信息
void Game::undateWithoutInput()
{
	switch (op)//根据系统状态执行不同操作
	{
	case readFile://读档
	case newGame_Game:
		finalTime = timeShift + getClock();//更新当前花费时间
		if (C.size() == level)//游戏胜利
			gameover();
		switch (level)
		{//游戏失败
		case 1:if (10 - finalTime <= 0) gameover(0); break;
		case 2:if (30 - finalTime <= 0) gameover(0); break;
		case 3:if (60 - finalTime <= 0) gameover(0); break;
		case 4:if (240 - finalTime <= 0) gameover(0); break;
		case 5:if (360 - finalTime <= 0) gameover(0); break;
		case 6:if (600 - finalTime <= 0) gameover(0); break;
		}
		break;
	case tutorial_Game://游戏教学模式
		if (C.size() == level)//演示结束
			tutorialover();
		break;
	}
}
// 与用户输入有关的信息
void Game::undateWithInput()
{
	// 获取一条鼠标或按键消息
	ExMessage msg;
	//若消息存在，则执行对应行为，否则什么也不干
	if (peekmessage(&msg, EX_MOUSE | EX_KEY))
	{
		//主菜单按键
		MenuButton.eventLoop(msg);
		if (MenuButton.isClicked()) { MainMenu(); }
		//根据系统状态执行不同操作
		switch (op)
		{
		case menu:
			for (int i = 0; i < menu_btns.size(); i++)
			{//主菜单各按键
				menu_btns[i]->eventLoop(msg);//传入消息
				if (menu_btns[i]->isClicked())
				{
					switch (i)
					{//第i个按键被点击
					case 0:
						op = newGame;
						clearTower();
						timeShift = 0;
						break;
					case 1:
						op = readFile;
						clearTower();
						resetClock();//重置时钟
						loadGame();//读取存储的塔状态
						break;
					case 2:op = rank; break;
					case 3:
						clearTower();
						clearStep();
						op = tutorial;
						break;
					case 4:op = GameRecord; break;
					case 5:op = HowToPlay; break;
					case 6:op = exitGame; break;
					}
				}
			}
			VolumeButton.eventLoop(msg);
			if (VolumeButton.isClicked())
			{//音量开关

				Volume = !Volume;//音乐状态取反
				if (Volume)//当前音乐状态应为开
				{
					VolumeButton.setText("关闭音乐");
					mciSendString("open ./sources/bkMusic.mp3 alias BGM", 0, 0, 0);
					mciSendString("play BGM repeat", 0, 0, 0);//重复播放
				}
				else//当前音乐状态应为关
				{
					VolumeButton.setText("打开音乐");
					mciSendString("close BGM", 0, 0, 0);//关闭音乐
				}
			}
			break;
		case newGame:
			for (int i = 0; i < level_btns.size(); i++)
			{//主菜单各按键
				level_btns[i]->eventLoop(msg);//传入消息
				if (level_btns[i]->isClicked())
				{
					level = i + 1;//难度=i+1
					initTower(level);
					resetClock();//启动时钟
					op = newGame_Game;
				}
			}
			break;
		case readFile:
		case newGame_Game:
			moveA.eventLoop(msg);
			moveB.eventLoop(msg);
			moveC.eventLoop(msg);
			saveButton.eventLoop(msg);
			if (saveButton.isClicked())
			{//保存游戏
				std::cout << "保存游戏，难度为" << level << "\n";
				saveGame();
			}
			if (moveA.isClicked())
			{//塔A被点击
				moveA.traIsStart();
				if (!startTower)//未开始
					startTower = 1;
				else if (!endTower)//开始了，接收第二个
				{
					endTower = 1;
					moveTower(startTower, endTower);
					moveA.resetIsStart();
					moveB.resetIsStart();
					moveC.resetIsStart();
				}
			}
			if (moveB.isClicked())
			{//塔B被点击
				moveB.traIsStart();
				if (!startTower)//未开始
					startTower = 2;
				else if (!endTower)//开始了，接收第二个
				{
					endTower = 2;
					moveTower(startTower, endTower);
					moveA.resetIsStart();
					moveB.resetIsStart();
					moveC.resetIsStart();
				}
			}
			if (moveC.isClicked())
			{//塔C被点击
				moveC.traIsStart();
				if (!startTower)//未开始
					startTower = 3;
				else if (!endTower)//开始了，接收第二个
				{
					endTower = 3;
					moveTower(startTower, endTower);
					moveA.resetIsStart();
					moveB.resetIsStart();
					moveC.resetIsStart();
				}
			}
			break;
		case tutorial:
			for (int i = 0; i < level_btns.size(); i++)
			{//各难度按键
				level_btns[i]->eventLoop(msg);//传入消息
				if (level_btns[i]->isClicked())
				{
					level = i + 1;//难度=i+1
					initTower(level);
					sloveTower(level, 1, 2, 3);
					op = tutorial_Game;
				}
			}
			break;
		case tutorial_Game:
			preStepButton.eventLoop(msg);
			nexStepButton.eventLoop(msg);
			if (preStepButton.isClicked())
			{
				if (nowStep)
				{
					nowStep--;
					moveTower(step[nowStep][1], step[nowStep][0]);
				}
			}
			if (nexStepButton.isClicked())
			{
				if (nowStep <= 63)
				{
					moveTower(step[nowStep][0], step[nowStep][1]);
					nowStep++;
				}
			}
			break;
		case GameRecord:
			prePageButton.eventLoop(msg);
			nexPageButton.eventLoop(msg);
			staPageButton.eventLoop(msg);
			endPageButton.eventLoop(msg);
			saveRecordButton.eventLoop(msg);
			if (prePageButton.isClicked()) { subRecordPage(); }
			if (nexPageButton.isClicked()) { addRecordPage(); }
			if (staPageButton.isClicked()) { startRecordPage(); }
			if (endPageButton.isClicked()) { endRecordPage(); }
			if (saveRecordButton.isClicked()) { saveRecord(); }
			break;
		}
		switch (msg.message)//输出调试信息，可丢弃
		{
		case WM_LBUTTONDOWN://左键按下
			std::cout << "左键按下" << "(" << msg.x << "," << msg.y << ")" << std::endl;
			break;
		case WM_KEYDOWN://ESC被按下
			if (msg.vkcode == VK_ESCAPE) { MainMenu(); }
		}
	}
}

//显示游戏画面
void Game::GameDraw()
{
	//绘制背景
	putimage(0, 0, &bkImage);
	switch (op)//根据系统的状态显示不同的界面
	{
	case menu:
		//绘制标题
		menu_text_hnt.showText();
		//绘制音乐按键
		VolumeButton.show();
		for (auto btn : menu_btns)
		{
			btn->show();
		}
		break;
	case tutorial://教程与新游戏界面1相同
	case newGame:
		//绘制标题
		level_text_hnt.showText();
		for (auto btn : level_btns)
		{
			btn->show();
		}
		break;
	case readFile://读档和正式游戏界面完全相同，只是进入时执行的操作不同
	case newGame_Game:
		showTower();
		moveA.show();
		moveB.show();
		moveC.show();
		showTimeRemain(level);
		saveButton.show();
		break;
	case rank:
		showRank();
		break;
	case tutorial_Game:
		preStepButton.show();
		nexStepButton.show();
		showTower();
		break;
	case GameRecord:
		showRecord();
		prePageButton.show();
		nexPageButton.show();
		staPageButton.show();
		endPageButton.show();
		saveRecordButton.show();
		break;
	case HowToPlay:
		putimage(0, 0, &htpImage);
		break;
	}
	//显示主菜单按键
	MenuButton.show();
}
//游戏背景音乐
void Game::BGM()
{
	//打开音乐
	mciSendString("open ./sources/bkMusic.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);//重复播放
}
//游戏主循环
void Game::loop()
{
	BeginBatchDraw();		//开始批量绘图
	while (op != exitGame)//游戏未结束
	{
		GameDraw();				//绘制游戏画面--这里画的图在后台
		FlushBatchDraw();		//刷新批量绘图--图在这里被刷新
		undateWithoutInput();	//与用户输入无关的信息
		undateWithInput();		//与用户输入有关的信息
	}
	EndBatchDraw();//结束批量绘图
}

void Game::gameover(int gameOverState/*=1*/)
{
	//增加，保存游戏记录
	addRecord(level, stepNum + stepShift, finalTime, gameOverState);
	saveRecord();
	//菜单状态刷新
	op = menu;
	//弹出窗口，提示用户操作
	std::string text;
	if (gameOverState)
	{//赢了
		newRank(hnd, level, finalTime);//更新排行榜
		text.append("你赢了！用时");
		text.append(std::to_string(finalTime / 60));
		text.append("分");
		text.append(std::to_string(finalTime % 60));
		text.append("秒！");
		int isok = MessageBox(hnd, text.c_str(), "提示", MB_OK);
		if (isok == IDOK) { printf("你点击了确定\n"); }
	}
	else//输了
	{
		text.append("你输了！");
		int isok = MessageBox(hnd, text.c_str(), "提示", MB_OK);
		if (isok == IDOK) { printf("你点击了确定\n"); }
	}
}

void Game::tutorialover()
{
	clearStep();
	clearTower();
	//菜单状态刷新
	op = menu;
	//弹出窗口，提示用户操作
	int isok = MessageBox(hnd, "教学结束！", "提示", MB_OK);
	if (isok == IDOK)
		printf("你点击了确定\n");
}

void Game::showTimeRemain(int level)
{
	int rtime = 0;
	switch (level)
	{//游戏失败
	case 1:rtime = 10 - finalTime; break;
	case 2:rtime = 30 - finalTime; break;
	case 3:rtime = 60 - finalTime; break;
	case 4:rtime = 240 - finalTime; break;
	case 5:rtime = 360 - finalTime; break;
	case 6:rtime = 600 - finalTime; break;
	}
	std::string timetext;
	timetext.append("剩余");
	timetext.append(std::to_string(rtime / 60));
	timetext.append("分");
	timetext.append(std::to_string(rtime % 60));
	timetext.append("秒");
	settextcolor(BLACK);//文字颜色
	settextstyle(30, 0, "微软雅黑");//设置字号、字体
	outtextxy(0, 0, timetext.c_str());
}

void Game::saveGame()
{
	saveFileTower(level, finalTime);
}

void Game::loadGame()
{
	readFileTower(level, timeShift);
}

void Game::MainMenu()
{
	if (A.size() || B.size() || C.size() && C.size() != level)
	{//塔不为空，则增加游戏记录-失败
		addRecord(level, stepNum + stepShift, finalTime, 0);
		saveRecord();//保存记录到本地
	}
	op = menu;
	clearStep();
	clearTower();
}

#include "Game.h"
#include "graphics.h"
#include <mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#include <iostream>
#include <vector>
#include "Text.h"
#include "Layer.h"
#include "MoveTowerButton.h"
#include "MyClock.h"
#include "graphics.h"
#include "windows.h"
#pragma comment(lib,"Winmm.lib")//���ؾ�̬�⣬��������
//���캯��
Game::Game()
	:menu_text_hnt("��ŵ��", 100, 250, 60), VolumeButton("�ر�����", 0, 579, 100, 20, 20)
	, level_text_hnt("ѡ���Ѷ�", 80, 250, 50), MenuButton("���˵�", 700, 579, 100, 20, 20)
	, preStepButton("��һ��", 150, 450, 200, 50, 50), nexStepButton("��һ��", 450, 450, 200, 50, 50)
	, saveButton("����", 345, 525, 110, 50)
	, prePageButton("��һҳ", 150, 510, 150, 30, 30), nexPageButton("��һҳ", 350, 510, 150, 30, 30)
	, staPageButton("��ҳ", 150, 550, 150, 30, 30), endPageButton("βҳ", 350, 550, 150, 30, 30)
	, saveRecordButton("�����¼", 550, 510, 150, 30, 30)
{
	//��ʼ������
	initgraph(w, h, SHOWCONSOLE);//���ڳ�ʼ����������̨
	//initgraph(w, h);	//���ڳ�ʼ��
	hnd = GetHWnd();		//���ھ��
	SetWindowText(hnd, "��ŵ��|�ƿƶ�ѧλ1�� 202283730040 ����");//���ô��ڱ���
	loadimage(&bkImage, "./sources/bkImage.jpg", 800, 600);//��ȡ�����ļ�
	loadimage(&htpImage, "./sources/HowToPlay.png", 800, 600);//��ȡ��Ϸ˵���ļ�
	setbkmode(TRANSPARENT);//���ñ���ģʽ��͸�������֣�
	//�����水ť��ʼ��
	menu_btns.push_back(new PushButton("����Ϸ"));
	menu_btns.push_back(new PushButton("��ȡ�浵"));
	menu_btns.push_back(new PushButton("���а�"));
	menu_btns.push_back(new PushButton("��Ϸ��ѧ"));
	menu_btns.push_back(new PushButton("��Ϸ��¼"));
	menu_btns.push_back(new PushButton("��Ϸ˵��"));
	menu_btns.push_back(new PushButton("�˳���Ϸ"));
	//���ð���λ��
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(300, 50);//���ð������
		//���㰴��λ��
		int bx = (w - menu_btns[i]->width()) / 2;
		int by = i * (menu_btns[i]->height() + 10) + 180;
		menu_btns[i]->move(bx, by);//���ð���λ��
	}
	//�ѶȰ�����ʼ��
	level_btns.push_back(new PushButton("1"));
	level_btns.push_back(new PushButton("2"));
	level_btns.push_back(new PushButton("3"));
	level_btns.push_back(new PushButton("4"));
	level_btns.push_back(new PushButton("5"));
	level_btns.push_back(new PushButton("6"));
	//���ð���λ��
	for (int i = 0; i < level_btns.size(); i++)
	{
		level_btns[i]->setFixedSize(200, 50);//���ð������
		//���㰴��λ��
		int bx = (w - level_btns[i]->width()) / 2;
		int by = i * (level_btns[i]->height() + 10) + 180;
		level_btns[i]->move(bx, by);//���ð���λ��
	}
	//��ȡ�ļ�
	ReadRankFile();//��ȡ���а�
	readRecord();//��ȡ��Ϸ��¼
}
Game::~Game()
{
	//�ͷ�menu_btns����
	for (std::vector<PushButton*>::iterator it = menu_btns.begin(); it != menu_btns.end(); it++)
	{
		if (NULL != *it)
		{
			delete* it;
			*it = NULL;
		}
	}
	menu_btns.clear();
	std::cout << "�ͷ��ڴ�ɹ���\n";
}
//��Ϸ��ʼ��
void Game::init()
{
	//��������
	BGM();
}
//���û������޹ص���Ϣ
void Game::undateWithoutInput()
{
	switch (op)//����ϵͳ״ִ̬�в�ͬ����
	{
	case readFile://����
	case newGame_Game:
		finalTime = timeShift + getClock();//���µ�ǰ����ʱ��
		if (C.size() == level)//��Ϸʤ��
			gameover();
		switch (level)
		{//��Ϸʧ��
		case 1:if (10 - finalTime <= 0) gameover(0); break;
		case 2:if (30 - finalTime <= 0) gameover(0); break;
		case 3:if (60 - finalTime <= 0) gameover(0); break;
		case 4:if (240 - finalTime <= 0) gameover(0); break;
		case 5:if (360 - finalTime <= 0) gameover(0); break;
		case 6:if (600 - finalTime <= 0) gameover(0); break;
		}
		break;
	case tutorial_Game://��Ϸ��ѧģʽ
		if (C.size() == level)//��ʾ����
			tutorialover();
		break;
	}
}
// ���û������йص���Ϣ
void Game::undateWithInput()
{
	// ��ȡһ�����򰴼���Ϣ
	ExMessage msg;
	//����Ϣ���ڣ���ִ�ж�Ӧ��Ϊ������ʲôҲ����
	if (peekmessage(&msg, EX_MOUSE | EX_KEY))
	{
		//���˵�����
		MenuButton.eventLoop(msg);
		if (MenuButton.isClicked()) { MainMenu(); }
		//����ϵͳ״ִ̬�в�ͬ����
		switch (op)
		{
		case menu:
			for (int i = 0; i < menu_btns.size(); i++)
			{//���˵�������
				menu_btns[i]->eventLoop(msg);//������Ϣ
				if (menu_btns[i]->isClicked())
				{
					switch (i)
					{//��i�����������
					case 0:
						op = newGame;
						clearTower();
						timeShift = 0;
						break;
					case 1:
						op = readFile;
						clearTower();
						resetClock();//����ʱ��
						loadGame();//��ȡ�洢����״̬
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
			{//��������

				Volume = !Volume;//����״̬ȡ��
				if (Volume)//��ǰ����״̬ӦΪ��
				{
					VolumeButton.setText("�ر�����");
					mciSendString("open ./sources/bkMusic.mp3 alias BGM", 0, 0, 0);
					mciSendString("play BGM repeat", 0, 0, 0);//�ظ�����
				}
				else//��ǰ����״̬ӦΪ��
				{
					VolumeButton.setText("������");
					mciSendString("close BGM", 0, 0, 0);//�ر�����
				}
			}
			break;
		case newGame:
			for (int i = 0; i < level_btns.size(); i++)
			{//���˵�������
				level_btns[i]->eventLoop(msg);//������Ϣ
				if (level_btns[i]->isClicked())
				{
					level = i + 1;//�Ѷ�=i+1
					initTower(level);
					resetClock();//����ʱ��
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
			{//������Ϸ
				std::cout << "������Ϸ���Ѷ�Ϊ" << level << "\n";
				saveGame();
			}
			if (moveA.isClicked())
			{//��A�����
				moveA.traIsStart();
				if (!startTower)//δ��ʼ
					startTower = 1;
				else if (!endTower)//��ʼ�ˣ����յڶ���
				{
					endTower = 1;
					moveTower(startTower, endTower);
					moveA.resetIsStart();
					moveB.resetIsStart();
					moveC.resetIsStart();
				}
			}
			if (moveB.isClicked())
			{//��B�����
				moveB.traIsStart();
				if (!startTower)//δ��ʼ
					startTower = 2;
				else if (!endTower)//��ʼ�ˣ����յڶ���
				{
					endTower = 2;
					moveTower(startTower, endTower);
					moveA.resetIsStart();
					moveB.resetIsStart();
					moveC.resetIsStart();
				}
			}
			if (moveC.isClicked())
			{//��C�����
				moveC.traIsStart();
				if (!startTower)//δ��ʼ
					startTower = 3;
				else if (!endTower)//��ʼ�ˣ����յڶ���
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
			{//���ѶȰ���
				level_btns[i]->eventLoop(msg);//������Ϣ
				if (level_btns[i]->isClicked())
				{
					level = i + 1;//�Ѷ�=i+1
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
		switch (msg.message)//���������Ϣ���ɶ���
		{
		case WM_LBUTTONDOWN://�������
			std::cout << "�������" << "(" << msg.x << "," << msg.y << ")" << std::endl;
			break;
		case WM_KEYDOWN://ESC������
			if (msg.vkcode == VK_ESCAPE) { MainMenu(); }
		}
	}
}

//��ʾ��Ϸ����
void Game::GameDraw()
{
	//���Ʊ���
	putimage(0, 0, &bkImage);
	switch (op)//����ϵͳ��״̬��ʾ��ͬ�Ľ���
	{
	case menu:
		//���Ʊ���
		menu_text_hnt.showText();
		//�������ְ���
		VolumeButton.show();
		for (auto btn : menu_btns)
		{
			btn->show();
		}
		break;
	case tutorial://�̳�������Ϸ����1��ͬ
	case newGame:
		//���Ʊ���
		level_text_hnt.showText();
		for (auto btn : level_btns)
		{
			btn->show();
		}
		break;
	case readFile://��������ʽ��Ϸ������ȫ��ͬ��ֻ�ǽ���ʱִ�еĲ�����ͬ
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
	//��ʾ���˵�����
	MenuButton.show();
}
//��Ϸ��������
void Game::BGM()
{
	//������
	mciSendString("open ./sources/bkMusic.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);//�ظ�����
}
//��Ϸ��ѭ��
void Game::loop()
{
	BeginBatchDraw();		//��ʼ������ͼ
	while (op != exitGame)//��Ϸδ����
	{
		GameDraw();				//������Ϸ����--���ﻭ��ͼ�ں�̨
		FlushBatchDraw();		//ˢ��������ͼ--ͼ�����ﱻˢ��
		undateWithoutInput();	//���û������޹ص���Ϣ
		undateWithInput();		//���û������йص���Ϣ
	}
	EndBatchDraw();//����������ͼ
}

void Game::gameover(int gameOverState/*=1*/)
{
	//���ӣ�������Ϸ��¼
	addRecord(level, stepNum + stepShift, finalTime, gameOverState);
	saveRecord();
	//�˵�״̬ˢ��
	op = menu;
	//�������ڣ���ʾ�û�����
	std::string text;
	if (gameOverState)
	{//Ӯ��
		newRank(hnd, level, finalTime);//�������а�
		text.append("��Ӯ�ˣ���ʱ");
		text.append(std::to_string(finalTime / 60));
		text.append("��");
		text.append(std::to_string(finalTime % 60));
		text.append("�룡");
		int isok = MessageBox(hnd, text.c_str(), "��ʾ", MB_OK);
		if (isok == IDOK) { printf("������ȷ��\n"); }
	}
	else//����
	{
		text.append("�����ˣ�");
		int isok = MessageBox(hnd, text.c_str(), "��ʾ", MB_OK);
		if (isok == IDOK) { printf("������ȷ��\n"); }
	}
}

void Game::tutorialover()
{
	clearStep();
	clearTower();
	//�˵�״̬ˢ��
	op = menu;
	//�������ڣ���ʾ�û�����
	int isok = MessageBox(hnd, "��ѧ������", "��ʾ", MB_OK);
	if (isok == IDOK)
		printf("������ȷ��\n");
}

void Game::showTimeRemain(int level)
{
	int rtime = 0;
	switch (level)
	{//��Ϸʧ��
	case 1:rtime = 10 - finalTime; break;
	case 2:rtime = 30 - finalTime; break;
	case 3:rtime = 60 - finalTime; break;
	case 4:rtime = 240 - finalTime; break;
	case 5:rtime = 360 - finalTime; break;
	case 6:rtime = 600 - finalTime; break;
	}
	std::string timetext;
	timetext.append("ʣ��");
	timetext.append(std::to_string(rtime / 60));
	timetext.append("��");
	timetext.append(std::to_string(rtime % 60));
	timetext.append("��");
	settextcolor(BLACK);//������ɫ
	settextstyle(30, 0, "΢���ź�");//�����ֺš�����
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
	{//����Ϊ�գ���������Ϸ��¼-ʧ��
		addRecord(level, stepNum + stepShift, finalTime, 0);
		saveRecord();//�����¼������
	}
	op = menu;
	clearStep();
	clearTower();
}

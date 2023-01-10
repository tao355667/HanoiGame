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
	int w = 800, h = 600;//���
	int level = 6;//��Ϸ�Ѷ�
	bool Volume = true;//Ĭ��������
	//��ȡ�浵��ʱ��ֵ������ʱ��ʱ�����Ӵ�ƫ��ֵ������Ϸƫ��ֵΪ0
	int timeShift = 0;
	//��Ϸʤ��ʱ��ʱ��ֵ
	int finalTime = 0;
	//��Ϸ�˵�״̬
	enum Operator {
		menu,			//���˵�
		newGame,		//����Ϸ�Ѷ�ѡ��
		newGame_Game,	//����Ϸ��Ϸ����
		readFile,		//��ȡ��Ϸ�浵
		rank,			//���а�
		tutorial,		//��Ϸ�̳��Ѷ�ѡ��
		tutorial_Game,	//��Ϸ�̳���Ϸ����
		GameRecord,		//�鿴��Ϸ��¼
		HowToPlay,		//�鿴��Ϸ˵��
		exitGame		//�˳���Ϸ
	};
	Operator op = menu;//�˵�״̬
	IMAGE bkImage;//����ͼ
	IMAGE htpImage;//��Ϸ˵��ͼ
	HWND hnd;//���ھ��
	//���˵��ؼ�
	std::vector<PushButton*> menu_btns;//���˵�����
	PushButton VolumeButton;//���ְ���
	PushButton MenuButton;//���˵�����
	Text menu_text_hnt;//���˵���������
	//ѡ���ѶȵĿؼ�
	Text level_text_hnt;//�Ѷ�ѡ������
	std::vector<PushButton*> level_btns;//�ѶȰ���
	//�̳̰�������һ������һ����
	PushButton preStepButton;
	PushButton nexStepButton;
	//���水��
	PushButton saveButton;
	//�鿴��¼�İ���
	PushButton prePageButton;//��һҳ
	PushButton nexPageButton;//��һҳ
	PushButton staPageButton;//��ҳ
	PushButton endPageButton;//βҳ
	PushButton saveRecordButton;//βҳ
	//���û������޹ص���Ϣ
	void undateWithoutInput();
	// ���û������йص���Ϣ
	void undateWithInput();
	//������Ϸ����
	void GameDraw();
	//��Ϸ��������
	void BGM();
	//��Ϸ����
	void gameover(int gameOverState = 1);//Ĭ��Ӯ��
	//��ѧ����
	void tutorialover();
	//��ʾʣ��ʱ��
	void showTimeRemain(int level);
	//����Ϸ��¼�浵
	void saveGame();
	//���ش浵
	void loadGame();
	//�������˵�Ҫ������
	void MainMenu();
public:
	//Game���캯��
	Game();
	//Game��������
	~Game();
	//��Ϸ��ʼ��
	void init();
	//��Ϸ��ѭ��
	void loop();
};


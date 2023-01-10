#pragma once
#include <vector>
typedef struct
{//��������
	int level;
	int step;
	int time;
	int isSuccess;
}RecordData;
class Record
{
protected:
	std::vector<RecordData*> RecordList;
	int beginRecordPage = 0;//ָʾ��ǰ��ʼҳ��
public:
	~Record();
	void addRecord(int level, int step, int time, int isSuccess);
	void showRecord();//��ʾ��¼
	void saveRecord();//����¼�����ļ�
	void readRecord();//��ȡ�ļ��еļ�¼
	void addRecordPage();//ҳ������
	void subRecordPage();//ҳ���С
	void startRecordPage();//��ҳ
	void endRecordPage();//βҳ
};


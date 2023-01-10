#pragma once
#include <vector>
typedef struct
{//数据类型
	int level;
	int step;
	int time;
	int isSuccess;
}RecordData;
class Record
{
protected:
	std::vector<RecordData*> RecordList;
	int beginRecordPage = 0;//指示当前起始页码
public:
	~Record();
	void addRecord(int level, int step, int time, int isSuccess);
	void showRecord();//显示记录
	void saveRecord();//将记录存入文件
	void readRecord();//读取文件中的记录
	void addRecordPage();//页码增加
	void subRecordPage();//页码减小
	void startRecordPage();//首页
	void endRecordPage();//尾页
};


#include "LogFilterThread.h"
#include "Data/DataConfig.h"
#include "Data/DataInput.h"
#include "Data/DataLog.h"
#include "FilePathGenerator.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include <stack>
using namespace std;

LogFilterThread::LogFilterThread()
{
}

LogFilterThread::~LogFilterThread()
{
}

void LogFilterThread::process(void) {
	stack<thread> stkThread;
	clock_t st, et;
	int iFileLimit = DataConfig::getInstance().getNumberOfLogFile();

	st = clock();

	for (int iFile = 1; iFile < iFileLimit + 1; iFile++) {
		stkThread.push(thread(&subprocess, iFile)); // ���� ���� ������ �Ҵ�
	}

	while (!stkThread.empty()) {
		stkThread.top().join(); // �����尡 ����� �� ���� ���
		stkThread.pop(); // ����� ������ ����
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;
}

void LogFilterThread::subprocess(const int &iFile) {
	ofstream ofResult;
	clock_t st, et;

	st = clock();

	DataLog dataLog(FilePathGenerator::getInFilePath(iFile)); // �α� ������ �а� �����ϴ� ��ü ����
	ofResult.open(FilePathGenerator::getOutFilePath(iFile)); // ����� ������ ���� ����

	while (!dataLog.nextRecord().empty()) // �α� ���Ͽ� �о�� ���ڵ尡 �����ִ� ���� ���� ���ڵ� �ҷ�����
	{
		if (!dataLog.isValidTime(DataInput::getInstance().getTimeEnd())) break; // �о�� �αװ� ��ϵ� �ð��� �˻� ���� �ð��� �Ѵ� ��� �ش� ���Ͽ��� ���ڵ� �ҷ����� ����
		else if (dataLog.isValidTime(DataInput::getInstance().getTimeStart(), DataInput::getInstance().getTimeEnd())) // �о�� �αװ� �˻��ϰ��� �ϴ� �ð��� ���ϴ� ���
		{
			if (dataLog.getResponseTime() >= DataInput::getInstance().getDelayLimit()) // �ش� �α��� �����ð��� ���� �����ð� �̻��� ���
			{
				ofResult << dataLog.getRecord() << endl; // ������Ͽ� �ش� �α� ���
			}
		}
	}
	et = clock();
	cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close(); // ��� ���� �ݱ�

}
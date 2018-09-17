#include "PathGenerator.h"
#include "ConfigData.h"
#include "ArgumentData.h"

const string PathGenerator::mkLogFilePath(const int &iLogFile) {
	char strBuffer[128];

	sprintf_s(strBuffer, 128, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), ArgumentData::getInstance().getDate().tm_year, ArgumentData::getInstance().getDate().tm_mon, ArgumentData::getInstance().getDate().tm_mday, iLogFile, "daouoffice.com_access", ArgumentData::getInstance().getDate().tm_year, ArgumentData::getInstance().getDate().tm_mon, ArgumentData::getInstance().getDate().tm_mday);

	return strBuffer;
}
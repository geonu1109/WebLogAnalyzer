#include "FilePathGenerator.h"

FilePathGenerator::~FilePathGenerator()
{
}

const string FilePathGenerator::getInFilePath(int iFile) {
	char strBuffer[512];

	sprintf(strBuffer, "%s\\%04d%02d%02d\\ap%d.%s_%s-%s-%s", DataConfig::getInstance().getPathLogFileDir(), DataInput::getInstance().getDate().tm_year, DataInput::getInstance().getDate().tm_mon, DataInput::getInstance().getDate().tm_mday, iFile, "daouoffice.com_access", DataInput::getInstance().getDate().tm_year, DataInput::getInstance().getDate().tm_mon, DataInput::getInstance().getDate().tm_mday);
	return string(strBuffer);
}

const string FilePathGenerator::getOutFilePath(int iFile) {
	char strBuffer[512];

	sprintf(strBuffer, "%s\\%04d%02d%02d\\ap%d.%s_%s-%s-%s_proc%d", DataConfig::getInstance().getPathLogFileDir(), DataInput::getInstance().getDate().tm_year, DataInput::getInstance().getDate().tm_mon, DataInput::getInstance().getDate().tm_mday, iFile, "daouoffice.com_access", DataInput::getInstance().getDate().tm_year, DataInput::getInstance().getDate().tm_mon, DataInput::getInstance().getDate().tm_mday, DataInput::getInstance().getSelect());
	return string(strBuffer);
}

FilePathGenerator::FilePathGenerator()
{
}

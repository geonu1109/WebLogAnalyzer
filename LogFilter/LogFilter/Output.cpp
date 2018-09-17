#include "Output.h"
#include "ArgumentData.h"
#include "Console.h"
#include "OutputFile.h"

Output *Output::getInstance(void) {
	if (ArgumentData::getInstance().getResultFilePath() == string()) {
		return Console::getInstance();
	}
	else {
		return OutputFile::getInstance();
	}
}
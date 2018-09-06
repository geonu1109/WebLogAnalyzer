#ifndef __FILEPATHGENERATOR_H__
#define __FILEPATHGENERATOR_H__

#include "Data/DataConfig.h"
#include "Data/DataInput.h"
#include <string>
using namespace std;

class FilePathGenerator {
public:
	~FilePathGenerator();
	static const string getInFilePath(int iFile);
	static const string getOutFilePath(int iFile);

private:
	FilePathGenerator();
};

#endif
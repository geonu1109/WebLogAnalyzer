#include "ArgumentData.h"

int main(int argc, char *argv[]) {
	ArgumentData::getInstance().init(argc, argv);


	return 0;
}
#include "Console.h"
#include <iostream>
#define WINDOWS

Console Console::instance;

Console &Console::getInstance(void) {
	return instance;
}

void Console::print(const string &strMsg) const {
	cout << strMsg << endl;
}

void Console::printErr(const string &strErrMsg) const {
	cout << "[error] " << strErrMsg << endl;
}

void Console::printChart(int arrValid[], int arrTotal[]) const {
	int sumValid = 0, sumTotal = 0;
	int ratio;
	
	printf("| %-4s | %-12s | %-20s | %-12s | %-12s |\n", "Hour","Conditional", "Traffic", "Total", "Ratio");
	for (int i = 0; i < 24; i++) {
		sumValid += arrValid[i];
		sumTotal += arrTotal[i];
	}
	for (int i = 0; i < 24; i++) {
		printf("| %4d | %12d | ", i, arrValid[i], arrTotal[i]);
		ratio = arrValid[i] * 20 / sumValid;
		if (arrValid[i] * 20 % sumValid != 0) {
			ratio++;
		}
		int j = 0;
		while (j < ratio) {
			cout << '|';
			j++;
		}
		while(j < 20) {
			cout << ' ';
			j++;
		}
		printf(" | %12d | %5s%0.3f %% |\n", arrTotal[i], "", (float)arrValid[i] / arrTotal[i]);
	}
	printf("| %-4s | %12d | %20s | %12d | %5s%0.3f %% |\n", "Sum", sumValid, "||||||||||||||||||||", sumTotal, "", (float)sumValid / sumTotal);
}

void Console::showProgress(const unsigned short int &ratio) const {
#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	printf(" progress bar\n");
	printf(" [ ");
	int i = 0;
	while (i < ratio / 2) {
		printf("|");
		i++;
	}
	while (i < 50) {
		printf(" ");
		i++;
	}
	printf(" ] %3d %%\n", ratio);
}

Console::Console() {

}
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
	int sumValid = 0, sumTotal = 0, maxValid = 0;
	int ratio;
	
	printf("| %-4s | %-11s | %-32s | %-8s | %-7s |\n", "Hour","Conditional", "Traffic", "Total", "Ratio");
	for (int i = 0; i < 24; i++) {
		if (arrValid[i] > maxValid) {
			maxValid = arrValid[i];
		}
		sumValid += arrValid[i];
		sumTotal += arrTotal[i];
	}
	for (int i = 0; i < 24; i++) {
		printf("| %4d | %11d | ", i, arrValid[i], arrTotal[i]);
		ratio = arrValid[i] * 32 / maxValid;
		if (arrValid[i] * 32 % maxValid != 0) {
			ratio++;
		}
		int j = 0;
		while (j < ratio) {
			cout << '|';
			j++;
		}
		while(j < 32) {
			cout << ' ';
			j++;
		}
		printf(" | %8d | %0.3f %% |\n", arrTotal[i], (float)arrValid[i] / arrTotal[i]);
	}
	printf("| %-4s | %11d | %32s | %8d | %0.3f %% |\n", "Sum", sumValid, "", sumTotal, (float)sumValid / sumTotal);
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
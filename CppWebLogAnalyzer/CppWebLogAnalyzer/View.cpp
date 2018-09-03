#include "View.h"
#include <cstdio>
#include <cstdlib>
#define WINDOWS

View::View() {}

View::~View() {}

int View::showMenu(void) {
	int select;

	printf("Web Log Analyzer\n\n");
	printf("1. Filter delayed API (in specific time period)\n");
	printf("2. Sort dynamic API (in specific time period)\n");
	printf("3. Count HTTP status (by time interval)\n");
	printf("4. List most called API (in specific time period)\n");
	printf("5. Classify Client-Agent (by time interval)\n");
	printf("\nSelect: ");
	scanf("%d", &select);
	
	return select;
}

DataInput *View::function1(void) {
	DataInput *data = new DataInput();
	char strBuffer[9];
	int nDelay;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	printf("Filter Delayed API\n\n");
	printf("date(YYYYMMDD): ");
	scanf_s("%s", strBuffer, 9);
	data->getDate(strBuffer);
	printf("start time(HHMMSS): ");
	scanf_s("%s", strBuffer, 7);
	data->getTimeStart(strBuffer);
	printf("end time(HHMMSS): ");
	scanf_s("%s", strBuffer, 7);
	data->getTimeEnd(strBuffer);
	printf("delay time: ");
	scanf_s("%d", &nDelay, 4);
	data->getDelay(nDelay);

	return data;
}
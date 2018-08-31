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

InputData *View::function1(void) {
	InputData *data = new InputData();

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	printf("Filter Delayed API\n\n");
	printf("date(YYYYMMDD): ");
	scanf("%s", data->DATE);
	printf("start time(HHMMSS): ");
	scanf("%s", data->TIME_START);
	printf("end time(HHMMSS): ");
	scanf("%s", data->TIME_END);
	printf("delay time: ");
	scanf("%d", &data->delay);

	return data;
}
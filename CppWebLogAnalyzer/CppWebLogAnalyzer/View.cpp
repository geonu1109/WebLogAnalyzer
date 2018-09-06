#include "View.h"
#include <iostream>
#include <string>
using namespace std;
#define WINDOWS

View::View() {}

View::~View() {}

const int View::showMenu(void) {
	int select;

	printf("Web Log Analyzer\n\n");
	printf("1. Filter delayed API (in specific time period)\n");
	printf("2. Sort dynamic API (in specific time period)\n");
	printf("3. Count HTTP status (by time interval)\n");
	printf("4. List most called API (in specific time period)\n");
	printf("5. Classify Client-Agent (by time interval)\n");
	printf("\nSelect: ");
	scanf("%d", &select);
	printf("\n");

	return select;
}

const void View::showMenu1(void) {
	string strBuffer;
	int nDelayLimit;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "Filter Delayed API" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	DataInput::getInstance().setDate(strBuffer);

	cout << "start time(HHMMSS): ";
	cin >> strBuffer;
	DataInput::getInstance().setTimeStart(strBuffer);

	cout << "end time(HHMMSS): ";
	cin >> strBuffer;
	DataInput::getInstance().setTimeEnd(strBuffer);

	cout << "delay limit(second): ";
	cin >> nDelayLimit;
	DataInput::getInstance().setDelayLimit(nDelayLimit);

	cout << endl;
}

const void View::showMenu2(void) {
	string strBuffer;
	int nBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "Sort dynamic API" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	DataInput::getInstance().setDate(strBuffer);

	cout << "start time(HHMMSS): ";
	cin >> strBuffer;
	DataInput::getInstance().setTimeStart(strBuffer);

	cout << "end time(HHMMSS): ";
	cin >> strBuffer;
	DataInput::getInstance().setTimeEnd(strBuffer);

	cout << "HTTP Status Code: ";
	cin >> nBuffer;
	DataInput::getInstance().setHttpStatusCode(nBuffer);

	cout << "HTTP Request Method: ";
	cin >> strBuffer;
	DataInput::getInstance().setHttpRequestMethod(strBuffer);

	cout << endl;
}

const void View::showMenu3(void) {
	string strBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "Count HTTP status" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	DataInput::getInstance().setDate(strBuffer);
	
	cout << endl;
}

const void View::showMenu4(void) {
	string strBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "List most called API" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	DataInput::getInstance().setDate(strBuffer);

	cout << "start time(HHMMSS): ";
	cin >> strBuffer;
	DataInput::getInstance().setTimeStart(strBuffer);

	cout << "end time(HHMMSS): ";
	cin >> strBuffer;
	DataInput::getInstance().setTimeEnd(strBuffer);

	cout << endl;
}

const void View::showMenu5(void) {
	string strBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "Classify Client-Agent" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	DataInput::getInstance().setDate(strBuffer);

	cout << endl;
}
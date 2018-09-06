#include "View.h"
#include <iostream>
#include <string>
using namespace std;
#define WINDOWS

View::View() {}

View::~View() {}

const int View::showMenu(void) const {
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

const DataInput View::showMenu1(void) const {
	DataInput dataInput;
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
	dataInput.setDate(strBuffer);

	cout << "start time(HHMMSS): ";
	cin >> strBuffer;
	dataInput.setTimeStart(strBuffer);

	cout << "end time(HHMMSS): ";
	cin >> strBuffer;
	dataInput.setTimeEnd(strBuffer);

	cout << "delay limit(second): ";
	cin >> nDelayLimit;
	dataInput.setDelayLimit(nDelayLimit);

	cout << endl;

	return dataInput;
}

const DataInput View::showMenu2(void) const {
	DataInput dataInput;
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
	dataInput.setDate(strBuffer);

	cout << "start time(HHMMSS): ";
	cin >> strBuffer;
	dataInput.setTimeStart(strBuffer);

	cout << "end time(HHMMSS): ";
	cin >> strBuffer;
	dataInput.setTimeEnd(strBuffer);

	cout << "HTTP Status Code: ";
	cin >> nBuffer;
	dataInput.setHttpStatusCode(nBuffer);

	cout << "HTTP Request Method: ";
	cin >> strBuffer;
	dataInput.setHttpRequestMethod(strBuffer);

	cout << endl;

	return dataInput;
}

const DataInput View::showMenu3(void) const {
	DataInput dataInput;
	string strBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "Count HTTP status" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	dataInput.setDate(strBuffer);
	
	cout << endl;

	return dataInput;
}

const DataInput View::showMenu4(void) const {
	DataInput dataInput;
	string strBuffer;
	int nBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "List most called API" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	dataInput.setDate(strBuffer);

	cout << "start time(HHMMSS): ";
	cin >> strBuffer;
	dataInput.setTimeStart(strBuffer);

	cout << "end time(HHMMSS): ";
	cin >> strBuffer;
	dataInput.setTimeEnd(strBuffer);

	cout << endl;

	return dataInput;
}

const DataInput View::showMenu5(void) const {
	DataInput dataInput;
	string strBuffer;

#ifdef WINDOWS
	system("cls");
#else
	system("clear");
#endif
	cout << "Classify Client-Agent" << endl << endl;

	cout << "date(YYYYMMDD): ";
	cin >> strBuffer;
	dataInput.setDate(strBuffer);

	cout << endl;

	return dataInput;
}
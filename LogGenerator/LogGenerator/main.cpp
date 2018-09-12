#include <iostream>
#include <fstream>
#include <string>
#include <thread>
using namespace std;

int main(void) {
	ifstream ifFile("C:/Users/user/Desktop/logdata/20180824/ap1.daouoffice.com_access_2018-08-24.txt");
	ofstream ofFile;
	string strBuffer;
	int count = 1;
	streampos pos;

	srand(time(nullptr));

	while (true) {
		this_thread::sleep_for(chrono::seconds(1));

		ofFile.open("C:/Users/user/Desktop/logdata/20180912/ap1.daouoffice.com_access_2018-09-12.txt", ios::app);
		pos = rand() * 100;
		cout << "pos: " << pos << endl;
		ifFile.seekg(pos);
		getline(ifFile, strBuffer); // 불완전한 로그 제거
		getline(ifFile, strBuffer);
		ofFile << strBuffer << endl;

		ofFile.close();
	}
}
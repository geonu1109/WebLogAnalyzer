#ifndef __VIEW_H__
#define __VIEW_H__

#include "Data/DataInput.h"

class View // Singleton
{
public:
	static View instance;

public:
	~View();
	const int showMenu(void);
	void showMenu1(void);
	void showMenu2(void);
	void showMenu3(void);
	void showMenu4(void);
	void showMenu5(void);
	static View &getInstance(void);

private:
	View();
};

#endif
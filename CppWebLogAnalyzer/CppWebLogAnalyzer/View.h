#ifndef __VIEW_H__
#define __VIEW_H__

#include "Data/DataInput.h"

class View {
public:
	~View();
	static const int showMenu(void);
	static const void showMenu1(void);
	static const void showMenu2(void);
	static const void showMenu3(void);
	static const void showMenu4(void);
	static const void showMenu5(void);

private:
	View();
};

#endif
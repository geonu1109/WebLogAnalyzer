#ifndef __VIEW_H__
#define __VIEW_H__

#include "InputData.h"

class View {
public:
	View();
	~View();
	static int showMenu(void);
	static InputData *function1(void);
};

#endif
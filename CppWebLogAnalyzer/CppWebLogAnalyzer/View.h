#ifndef __VIEW_H__
#define __VIEW_H__

#include "DataInput.h"

class View {
public:
	View();
	~View();
	static int showMenu(void);
	static DataInput *function1(void);
};

#endif
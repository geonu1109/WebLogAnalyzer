#ifndef __VIEW_H__
#define __VIEW_H__

#include "Data/DataInput.h"

class View {
public:
	View();
	~View();
	const int showMenu(void) const;
	const DataInput showMenu1(void) const;
	const DataInput showMenu2(void) const;
	const DataInput showMenu3(void) const;
	const DataInput showMenu4(void) const;
	const DataInput showMenu5(void) const;
};

#endif
#include "View.h"
#include <iostream>


View::View() {

}

void View::printErr(string strErrMsg) const {
	cout << "[error] " << strErrMsg << endl;
}

#include "Controller.h"
#include "DataConfig.h"
#include "View.h"
#include <string>
using namespace std;

Controller::Controller() {

}

void Controller::process(void) const {
	View console;
	try {
	}
	catch (string strErrMsg) {
		console.printErr(strErrMsg);
		exit(1);
	}
}

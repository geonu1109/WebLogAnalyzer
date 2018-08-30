//
//  main.cpp
//  WebLogAnalyzer
//
//  Created by 전건우 on 2018. 8. 29..
//  Copyright C 2018년 전건우. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "utility.h"
#include "filter.h"

int main(void) {
	int select;

	loadConfig();
	showMenu();
	scanf("%d", &select);
	switch (select) {
	case 1:
		filterDelayedAPI();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		;
	}
	system("pause");
	return 0;
}
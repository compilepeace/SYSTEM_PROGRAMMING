#include <stdio.h>

extern int func1();
extern int func2();

int main () {

	if (func1() == 7) {
		printf ("func1 returned: 7\n");
	}	
	if (func2() == 8) {
		printf ("func2 returned: 8\n");
	}
	else printf ("returned: 0");
}

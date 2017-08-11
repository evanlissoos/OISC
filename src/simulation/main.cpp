#include "oisc.h"

#include <iostream>
#include <string>

int main()
{
	interactive_oisc * test_oisc = new interactive_oisc();
	test_oisc->run();

	free(test_oisc);
	return 0;
}

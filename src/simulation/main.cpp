#include "lib/interactive_oisc.h"
#include <iostream>
#include <string>
#include <thread>
using namespace std;

int main()
{
	interactive_oisc * test_oisc = new interactive_oisc();
	test_oisc->run();

	delete test_oisc;
	return 0;
}

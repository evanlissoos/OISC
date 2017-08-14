#include "main_lib.hpp"

/*
* main
*
* description: Main function of exection
* arguments  : None
* returns    : Exit status
*/
int main()
{
#if INTERACTIVE_MODE
	run_interactive();
#else
	run_oisc(FILENAME);
#endif
	return 0;
}

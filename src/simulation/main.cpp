#include "lib/interactive_oisc.h"
#include <iostream>
#include <string>
using namespace std;

#include <termios.h>
class BufferToggle
{
	 private:
	     struct termios t;

	 public:

	     /*
	      * Disables buffered input
	      */

	     void off(void)
	     {
	         tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
	         t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
	         tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
	     }


	     /*
	      * Enables buffered input
	      */

	     void on(void)
	     {
	         tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
	         t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
	         tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
	     }
};

int main()
{
	char test;
	BufferToggle bt;
	test = getchar(); //waits for you to press enter before proceeding to the next instruction
	cout << test << endl;
	bt.off();
	test = getchar(); //processes next instruction as soon as you type a character (no enter)
	cout << test << endl;
	bt.on();
	test = getchar(); //waits for you to press enter before proceeding to the next instruction
	cout << test << endl;

	interactive_oisc * test_oisc = new interactive_oisc();
	test_oisc->run();

	delete test_oisc;
	return 0;
}

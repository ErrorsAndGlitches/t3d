#include "NetworkInterface.h"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
	NetworkInterface ni;
	ni.joinGame();

	ni.endGame();
	return 0;
}

#include <stdlib.h>
#include <time.h>
#include "Homework.h"

int main()
{
	unsigned int Seed = (unsigned int)time(0);
	// Seed = 0 // For debugging
	srand(Seed);

	//Homework02_Run();
	//Homework03_Run();
	//Homework04_Run();
	Homework05_Run();
}

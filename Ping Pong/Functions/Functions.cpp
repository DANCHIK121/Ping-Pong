// Standart libraries
#include <random>
#include <iostream>

// Project files
#include "Functions.h"

namespace ProjectFunctions
{
	int Functions::RandomFunction(int minValue, int maxValue)
	{
		int resultNumber;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(minValue, maxValue);
		resultNumber = dist6(rng);

		return resultNumber;
	}
}
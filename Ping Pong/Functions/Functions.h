#pragma once

// Standart libraries
#include <iostream>

namespace ProjectFunctions
{
	class Functions
	{
	public:
		int RandomFunction(int minValue, int maxValue);
		int ResetGameData(int& currentLevel, int& firstPlayerPointsCount, int& secondPlayerPointsCount, int& ballRadius, float& ballSpeed, 
						  int& halfSquareSpeed);
	};
}
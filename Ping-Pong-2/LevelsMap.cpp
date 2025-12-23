// Standart libraries
#include <map>
#include <iostream>

namespace GameLevels
{
	// { LevelNumber, MaxValueForLevelUp }
	inline static std::map<unsigned int, unsigned int> LevelsMap
	{
		std::pair<unsigned int, unsigned int> { 1,  1000 },
		std::pair<unsigned int, unsigned int> { 2,  2000 },
		std::pair<unsigned int, unsigned int> { 3,  4000 },
		std::pair<unsigned int, unsigned int> { 4,  8000 },
		std::pair<unsigned int, unsigned int> { 5,  12000 },
		std::pair<unsigned int, unsigned int> { 6,  20000 },
		std::pair<unsigned int, unsigned int> { 7,  25000 },
		std::pair<unsigned int, unsigned int> { 8,  30000 },
		std::pair<unsigned int, unsigned int> { 9,  45000 },
		std::pair<unsigned int, unsigned int> { 10, 50000 },
	};
}
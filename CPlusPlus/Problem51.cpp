#include <algorithm>
#include <iostream>
#include <bitset>
#include <array>
#include "ProblemMap.h"
#include "Utils.h"


/*
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers,
yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime
with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
*/

int generatePatternNum(const std::bitset<6> &pattern, int num, bool antiPattern)
{
	// antipattern indicates that 1 should be used instead of 0s

	int retval = 0;

	for (int i = 0; i < 6; ++i)
	{
		if (!(pattern[i] ^ antiPattern))
		{
			retval += (num % 10) * pow(10, i);
			num /= 10;
		}
	}

	return retval;
}

void ProblemMap::Problem51()
{
	int const MAX = 1000000;
	int const GOAL_SERIES_LENGTH = 8;

	Utils::Seive seive(MAX);

	// 0 indicates a repeat digit index
	std::array<int, 10> patterns = {
		0b110001,
		0b101001,
		0b100101,
		0b100011,
		0b011001,
		0b010101,
		0b010011,
		0b001101,
		0b001011,
		0b000111,
	};

	std::bitset<6> pattern;

	int curNum = 0;
	int repeatNum = 0;
	int cyclePatternedNum = 0;
	int repeatPatternedNum = 0;
	int familySize = 0;

	for (int i = 0; i < patterns.size(); ++i)
	{
		pattern = patterns[i];

		for (int j = 0; j < 1000; ++j)
		{
			repeatNum = 0;
			familySize = 0;
			cyclePatternedNum = generatePatternNum(pattern, j, true);

			while (repeatNum < 1000)
			{
				repeatPatternedNum = generatePatternNum(pattern, repeatNum, false);

				curNum = cyclePatternedNum + repeatPatternedNum;

				if (seive.IsPrime(curNum))
					++familySize;

				repeatNum += 111;
			}

			if (familySize == GOAL_SERIES_LENGTH)
			{
				std::cout << cyclePatternedNum << std::endl;
				return;
			}
		}
	}
}
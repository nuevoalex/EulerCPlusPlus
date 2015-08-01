#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×12
15 = 7 + 2×22
21 = 3 + 2×32
25 = 7 + 2×32
27 = 19 + 2×22
33 = 31 + 2×12

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square ?
*/

void ProblemMap::Problem46()
{
	const int MAX_NUM = 1000000;

	using namespace Utils;

	Seive seive = Seive(MAX_NUM);

	std::vector<int> twoSquares = std::vector<int>();

	for (int tsi = 0; tsi < MAX_NUM; ++tsi)
		twoSquares.push_back(2 * pow(tsi, 2));

	for (int i = 33; i < MAX_NUM; i+=2)
	{
		bool found = false;
		for (int ti = 0; ti < MAX_NUM; ++ti)
		{
			int tsNum = twoSquares[ti];

			if (tsNum >= i)
				break;

			if (seive.IsPrime(i - tsNum))
			{
				found = true;
				break;
			}
		}
		if (found)
			continue;

		std::cout << "NUMBER IS: " << i << std::endl;
		return;
	}
}
#include <algorithm>
#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 5C3 = 10.

In general,

nCr =
n!
--------
r!(n?r)!

where r ? n, n! = n×(n?1)×...×3×2×1, and 0! = 1.
It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

How many, not necessarily distinct, values of  nCr, for 1 ? n ? 100, are greater than one-million?

23
10,11,12,13

24
9,10,11,12,13,14,15

*/

void ProblemMap::Problem53()
{
	const int LIMIT = 100;
	const int MILLION = 1000000;

	int counter = 0;

	for (int i = 23; i <= LIMIT; ++i)
	{
		for (int j = 1; j <= i/2; ++j)
		{
			if ((Utils::nCr(i, j) > MILLION))
			{
				counter += (i/2 - j + 1) * 2;

				if ((i % 2) == 0)
					counter--;

				break;
			}
		}
	}

	std::cout << counter << std::endl;
}
#include <algorithm>
#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?
*/

void ProblemMap::Problem50()
{
	const int LIMIT = 1000000;

	Utils::Seive seive(LIMIT);

	int longestLength = 0;
	int sum = 0;
	int curLength = 0;
	int topPrime = 0;

	for (int p : seive.PrimeGenerator(2))
	{
		curLength = 1;
		sum = p;

		for (int innerP : seive.PrimeGenerator(p+1))
		{
			sum += innerP;
				 
			if (sum >= LIMIT)
				break;

			curLength++;

			if (curLength > longestLength && seive.IsPrime(sum))
			{
				longestLength = curLength;
				topPrime = sum;
			}
		}
	}

	std::cout << topPrime << std::endl;
}
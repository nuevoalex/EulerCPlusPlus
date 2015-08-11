#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include "ProblemMap.h"
#include "Utils.h"

/*
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways:
  (i) each of the three terms are prime
  (ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1, 2, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?
*/

void ProblemMap::Problem49()
{
	Utils::Seive seive = Utils::Seive(10000);

	std::map<std::string, int_vector> permutationCollector = std::map<std::string, int_vector>();

	// Collect the potential sequences
	for (int prime : seive.PrimeGenerator(1000)) {

		std::string numString = std::to_string(prime);
		std::sort(numString.begin(), numString.end());
		std::reverse(numString.begin(), numString.end());

		if (permutationCollector.find(numString) == permutationCollector.end())
			permutationCollector[numString] = int_vector();

		permutationCollector[numString].push_back(prime);
	}

	// Find one thats actually a sequence
	for (auto const &item : permutationCollector)
	{
		int_vector values = item.second;
		for (int idx = values.size()-1; idx >= 2; --idx)
		{
			int first = values[idx];
			for (int secondIdx = idx - 1; secondIdx >= 0; --secondIdx)
			{
				int second = values[secondIdx];
				for (int thirdIdx = secondIdx - 1; thirdIdx >= 0; --thirdIdx)
				{
					int third = values[thirdIdx];
					if ((first - second) == (second - third))
						std::cout << third << second << first << std::endl;
				}
			}
		}
	}
}
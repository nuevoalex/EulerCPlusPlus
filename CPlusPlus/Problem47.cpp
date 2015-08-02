#include <iostream>
#include <vector>
#include <algorithm>
#include "ProblemMap.h"
#include "Utils.h"
#include "PrettyPrint.h"

/*
The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

ANSWER: 134043

Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?
*/

void ProblemMap::Problem47()
{
	int const MAX_NUM = 1000000;

	Utils::Factorizer factorizer;

	int_vector history[3];
	history[0] = int_vector();
	history[1] = int_vector();
	history[2] = int_vector();

	for (int i = 3; i < MAX_NUM; ++i)
	{
		int_vector curFactors = factorizer.GetFactors(i);

		int_vector curPoweredFactors;
		// make powered up
		if (curFactors.size() != 0)
		{
			int curNum = curFactors[0];
			int curVal = curFactors[0];
			for (int j = 0; j < curFactors.size(); ++j)
			{
				if (curFactors[j] == curNum)
				{
					curVal *= curNum;
				}
				else
				{
					curPoweredFactors.push_back(curVal);
					curNum = curFactors[j];
					curVal = curFactors[j];
				}
			}
			curPoweredFactors.push_back(curVal);
		}

		bool failed = false;

		if (curPoweredFactors.size() != 4)
			failed = true;
		else
		{
			int_vector seenFactors(curPoweredFactors);
			for (int k = 0; k < 3; ++k)
			{
				int_vector curHistoryFactors = history[k];
				if (curHistoryFactors.size() != 4)
				{
					failed = true;
					break;
				}
				for (int z = 0; z < curHistoryFactors.size(); ++z)
				{
					int factor = curHistoryFactors[z];
					if (std::find(seenFactors.begin(), seenFactors.end(), factor) != seenFactors.end())
					{
						failed = true;
						break;
					}
					seenFactors.push_back(factor);
				}
			}
		}

		if (!failed)
		{
			std::cout << "MADE IT: " << i << std::endl;
			break;
		}

		history[i % 3] = curPoweredFactors;
	}
}
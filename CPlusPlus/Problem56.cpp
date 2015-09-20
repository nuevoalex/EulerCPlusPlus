#include <algorithm>
#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large:
one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/


void ProblemMap::Problem56()
{
	int biggest = 0;
	Utils::BigNum num(0);

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			num.Init(i);
			num.Exp(j);
			int digSum = num.DigitSum();
			if (digSum > biggest)
				biggest = digSum;
		}
	}

	std::cout << biggest << std::endl;
}
#include <algorithm>
#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
It is possible to show that the square root of two can be expressed as an infinite continued fraction.

? 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...

By expanding this for the first four iterations, we get:

1 + 1/2 = 3/2 = 1.5
1 + 1/(2 + 1/2) = 7/5 = 1.4
1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

1/2
2/5
5/12
12/29
29/70
70/169

3-7-17-41-99

x1/y1 = 3/2
x2/y2 = 7/5 = x1+2y1/x1+y1
x3/y3 = 17/12 = x2+2y2/x2+y2
x4/y4 = 41/29 = x3+2y3/x3+y3

The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, is the first
example where the number of digits in the numerator exceeds the number of digits in the denominator.

In the first one-thousand expansions, how many fractions contain a numerator with more digits than denominator?
*/

typedef std::experimental::generator<std::pair<Utils::BigNum, Utils::BigNum>> bignum_pair_generator;

namespace Problem57
{
	bignum_pair_generator SqrTwoExpansions()
	{
		Utils::BigNum num = 3;
		Utils::BigNum den = 2;
		while (true) {
			__yield_value std::pair<Utils::BigNum, Utils::BigNum>(num, den);
			Utils::BigNum tempDen(den);
			den.Add(num);
			tempDen.Mult(2);
			num.Add(tempDen);
		}
	}
}

void ProblemMap::Problem57()
{
	const int LIMIT = 1000;

	int fractionCount = 0;

	int counter = 0;

	for (std::pair<Utils::BigNum, Utils::BigNum> fraction : Problem57::SqrTwoExpansions()) {

		if (fraction.first.NumDigits() > fraction.second.NumDigits())
			++fractionCount;
		
		++counter;

		if (counter >= LIMIT)
			break;
	}

	std::cout << fractionCount << std::endl;
}
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
	using namespace Utils;
	for (int v : Utils::Fib()) {
		if (v > 50)
			break;
		std::cout << v << std::endl;
	}
}
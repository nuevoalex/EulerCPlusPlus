#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

Answer: 9110846700
*/

// Can't use this :[
long long fastPowMod(int b, int e, long long m)
{
	if (e == 0)
	{
		return 1;
	}
	else if (e % 2 == 0)
	{
		long long squareRoot = fastPowMod(b, e / 2, m);
		// Still overflows :[
		return (squareRoot * squareRoot) % m;
	}
	else
	{
		return (fastPowMod(b, e - 1, m) * b) % m;
	}
}

long long slowPowMod(int b, int e, long long m)
{
	long long retval = b;
	while (e > 1)
	{
		retval = (retval * b) % m;
		e--;
	}

	return retval;
}

void ProblemMap::Problem48()
{
	const long long MAX_VALUE = 10000000000;

	long long value = 0;
	int increment = 1;

	while (increment <= 1000)
	{
		long long power = slowPowMod(increment, increment, MAX_VALUE);

		value += power;			

		++increment;
	}

	value = value % MAX_VALUE;

	std::cout << value << std::endl;
}
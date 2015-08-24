#include <algorithm>
#include <iostream>
#include <vector>
#include "ProblemMap.h"
#include "Utils.h"

/*
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/

namespace Problem52
{
	// Sort a numbers digits ignoring 0
	int DigitSort(int num)
	{
		int mult = 1;
		int retval = 0;

		int innerNum = num;

		for (int digit = 1; digit < 10; ++digit)
		{
			innerNum = num;
			while (innerNum > 0)
			{
				if (innerNum % 10 == digit)
				{
					retval += digit * mult;
					mult *= 10;
				}

				innerNum /= 10;
			}
		}

		return retval;
	}

	// Sum of digits matches?
	bool DigitTest(int num1, int num2)
	{
		return DigitSort(num1) == DigitSort(num2);
	}
}

void ProblemMap::Problem52()
{
	int init = 1;
	bool success = false;

	while (!success) {

		init *= 10;

		for (int i = init; i < init * 10/6; ++i) {

			success = true;

			for (int j = 2; j <= 6; j++) {
				if (!Problem52::DigitTest(i, j * i)) {
					success = false;
					break;
				}
			}

			if (success) {
				std::cout << i << std::endl;
				break;
			}
		}
	}
}
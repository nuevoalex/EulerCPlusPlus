#include <stdlib.h>
#include <vector>
#include <iostream>
#include <experimental/generator>
#include "Utils.h"

namespace Utils
{
	Seive::Seive(int n)
	{
		NumSet = std::vector<bool>(n, true);

		for (int i = 2; i < n; ++i)
		{
			if (NumSet[i])
			{
				for (int j = 2*i; j < n; j += i)
				{
					NumSet[j] = false;
				}
			}
		}
	}

	bool Seive::IsPrime(int n)
	{
		return NumSet[n];
	}

	int_generator Seive::PrimeGenerator()
	{
		unsigned int index = 0;
		while (index < NumSet.size()) {
			__yield_value NumSet[index];
			++index;
		}
	}

	int_generator Fib()
	{
		int a = 0;
		int b = 1;
		for (;;) {
			__yield_value a;
			auto next = a + b;
			a = b;
			b = next;
		}
	}
}

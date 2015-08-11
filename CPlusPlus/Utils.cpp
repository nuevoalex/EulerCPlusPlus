#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>
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

	int_generator Seive::PrimeGenerator(int index)
	{
		while (index < NumSet.size()) {
			if (NumSet[index])
				__yield_value index;
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

	Factorizer::Factorizer()
	{
		NumSet = std::map<int, int_vector>();
		NumSet[1] = int_vector();
		NumSet[2] = int_vector();
		NumSet[2].push_back(2);
	}

	int_vector Factorizer::GetFactors(int n)
	{
		int_vector retval;

		if (NumSet.find(n) == NumSet.end())
		{
			int sq = (int)sqrt(n);

			bool isPrime = true;
			for (int i = 2; i <= sq; ++i)
			{
				int div = n / i;
				int mod = n % i;
				if (mod == 0)
				{
					isPrime = false;

					int_vector divFactors = GetFactors(div);
					int_vector iFactors = GetFactors(i);

					retval.insert(retval.end(), divFactors.begin(), divFactors.end());
					retval.insert(retval.end(), iFactors.begin(), iFactors.end());
					break;
				}
			}

			if (isPrime)
			{
				retval.push_back(n);
			}

			NumSet[n] = retval;
		}
		else
		{
			retval = NumSet[n];
		}

		return retval;
	}
}

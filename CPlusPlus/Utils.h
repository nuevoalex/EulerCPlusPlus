#ifndef UTILS
#define UTILS

// Forward Delcarations

// Includes
#include <iterator>
#include <vector>
#include <map>
#include <unordered_set>
#include <experimental/generator>

typedef std::vector<int> int_vector;
typedef std::experimental::generator<int> int_generator;
typedef std::unordered_set<int> int_set;

namespace Utils
{
	class Seive
	{
		private:
			std::vector<bool> NumSet;

		public:
			Seive(int max);

			bool IsPrime(int n);

			int_generator PrimeGenerator(int start = 0);
	};

	class Factorizer
	{
	private:
		std::map<int, int_vector> NumSet;

	public:
		Factorizer();

		int_vector GetFactors(int n);
	};

	int_generator Fib();

	long long FibN(int n);

	bool IsPowerOfTwo(int n);

	int_generator Collatz(int n);

	long long Factorial(int n, int min = 1);

	long nCr(int n, int r);
}

#endif // UTILS 
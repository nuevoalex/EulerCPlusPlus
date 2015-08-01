#ifndef UTILS
#define UTILS

// Forward Delcarations

// Includes
#include <iterator>
#include <vector>
#include <experimental/generator>

namespace Utils
{
	typedef std::experimental::generator<int> int_generator;

	class Seive
	{
		private:
			std::vector<bool> NumSet;
		public:
			Seive(int n);
			bool IsPrime(int n);
			int_generator PrimeGenerator();
	};

	int_generator Fib();
}

#endif // UTILS 
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
typedef std::vector<std::string> string_vector;
typedef std::vector<char> char_vector;

namespace Utils
{
	class Seive
	{
		private:
			std::vector<bool> NumSet;

		public:
			Seive(long max);

			bool IsPrime(long n);

			int_generator PrimeGenerator(long start = 0);
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

	string_vector split(std::string str, char delimiter);

	class BigNum
	{
	private:
		int m_original;
		int_vector m_digits;
	public:
		BigNum(int orig);
		BigNum(const BigNum& other);
		void Init(int orig);
		void Add(const BigNum& other);
		void Mult(int n);
		void Exp(int n);
		int DigitSum();
		int NumDigits();
		friend std::ostream& operator<<(std::ostream& os, const BigNum& bigNum);
	};
}

#endif // UTILS 
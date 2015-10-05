#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <experimental/generator>
#include "Utils.h"

namespace Utils
{
	Seive::Seive(long n)
	{
		NumSet = std::vector<bool>(n, true);

		for (long i = 2; i < n; ++i)
		{
			if (NumSet[i])
			{
				for (long j = 2*i; j < n; j += i)
				{
					NumSet[j] = false;
				}
			}
		}
	}

	bool Seive::IsPrime(long n)
	{
		return NumSet[n];
	}

	int_generator Seive::PrimeGenerator(long index)
	{
		while (index < NumSet.size()) {
			if (NumSet[index])
				__yield_value index;
			++index;
		}
	}

	bool Utils::IsPowerOfTwo(int x)
	{
		return ((x != 0) && !(x & (x - 1)));
	}

	int_generator Utils::Collatz(int n)
	{
		for (;;)
		{
			if (IsPowerOfTwo(n))
				break;
			__yield_value n;
			n = (n % 2 == 0) ? n / 2 : (3 * n) + 1;
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

	long long FibN(int n)
	{
		long long retval = 0;
		while (n > 0)
		{
			for (int i : Fib())
			{
				retval = i;
				n--;
			}
		}

		return retval;
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

	long long Factorial(int num, int min)
	{
		if (num <= min)
			return 1;

		return Factorial(num - 1, min) * num;
	}

	long nCr(int n, int r)
	{
		long long retval = 0;

		long long numerator = Utils::Factorial(n, n - r);

		long long denom = Utils::Factorial(r);

		retval = numerator / denom;

		return retval;
	}

	string_vector split(std::string str, char delimiter)
	{
		string_vector internal;
		std::stringstream ss(str);
		std::string tok;

		while (getline(ss, tok, delimiter)) {
			internal.push_back(tok);
		}

		return internal;
	}

	BigNum::BigNum(int orig)
	{
		Init(orig);
	}

	BigNum::BigNum(const BigNum& other)
	{
		m_original = other.m_original;
		m_digits = other.m_digits;
	}

	void BigNum::Init(int orig)
	{
		m_original = orig;
		int digitValue = m_original;
		m_digits.clear();
		while (digitValue > 0)
		{
			m_digits.push_back(digitValue % 10);
			digitValue /= 10;
		}
	}

	void BigNum::Add(const BigNum& other)
	{
		for (int i = 0; i < other.m_digits.size(); ++i)
		{
			if (i >= m_digits.size())
				m_digits.push_back(0);

			m_digits[i] += other.m_digits[i];
		}

		for (int j = 0; j < m_digits.size(); ++j)
		{
			if (m_digits[j] >= 10)
			{
				if (j + 1 == m_digits.size())
					m_digits.push_back(1);
				else
					m_digits[j + 1] += 1;

				m_digits[j] %= 10;
			}
		}
	}

	void BigNum::Mult(int n)
	{
		BigNum orig(*this);
		for (int i = 1; i < n; ++i)
		{
			Add(orig);
		}
	}

	void BigNum::Exp(int n)
	{
		for (int i = 1; i < n; ++i)
		{
			Mult(m_original);
		}
	}

	int BigNum::DigitSum()
	{
		int retval = 0;
		for (int i = 0; i < m_digits.size(); ++i)
		{
			retval += m_digits[i];
		}
		return retval;
	}

	int BigNum::NumDigits()
	{
		return m_digits.size();
	}

	std::ostream& operator<<(std::ostream& os, const BigNum& bigNum)
	{
		for (int i = bigNum.m_digits.size() - 1; i >= 0; --i)
		{
			os << bigNum.m_digits[i];
		}
		return os;
	}
}

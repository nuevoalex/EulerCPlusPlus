#include <algorithm>
#include <iostream>
#include "ProblemMap.h"
#include "Utils.h"

/*
A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large:
one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum?
*/

namespace Problem56
{
	class BigNum
	{
	private:
		int m_original;
		int_vector m_digits;
	public:

		BigNum(int orig)
		{
			Init(orig);
		}

		BigNum(const BigNum& other)
		{
			m_original = other.m_original;
			m_digits = other.m_digits;
		}

		void Init(int orig)
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

		void Add(const BigNum& other)
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

		void Mult(int n)
		{
			BigNum orig(*this);
			for (int i = 1; i < n; ++i)
			{
				Add(orig);
			}
		}

		void Exp(int n)
		{
			for (int i = 1; i < n; ++i)
			{
				Mult(m_original);
			}
		}

		int DigitSum()
		{
			int retval = 0;
			for (int i = 0; i < m_digits.size(); ++i)
			{
				retval += m_digits[i];
			}
			return retval;
		}

		friend std::ostream& operator<<(std::ostream& os, const BigNum& bigNum);
	};

	std::ostream& operator<<(std::ostream& os, const Problem56::BigNum& bigNum)
	{
		for (int i = bigNum.m_digits.size() - 1; i >= 0; --i)
		{
			os << bigNum.m_digits[i];
		}
		return os;
	}
}

void ProblemMap::Problem56()
{
	int biggest = 0;
	Problem56::BigNum num(0);

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			num.Init(i);
			num.Exp(j);
			int digSum = num.DigitSum();
			if (digSum > biggest)
				biggest = digSum;
		}
	}

	std::cout << biggest << std::endl;
}
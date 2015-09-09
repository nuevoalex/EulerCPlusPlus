#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include "ProblemMap.h"
#include "Utils.h"

/*
If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.

Not all numbers produce palindromes so quickly. For example,

349 + 943 = 1292,
1292 + 2921 = 4213
4213 + 3124 = 7337

That is, 349 took three iterations to arrive at a palindrome.

Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome.
A number that never forms a palindrome through the reverse and add process is called a Lychrel number.
Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that
a number is Lychrel until proven otherwise. In addition you are given that for every number below ten-thousand,
it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power
that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require
over fifty iterations before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).

Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.

How many Lychrel numbers are there below ten-thousand?

NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.
*/

namespace Problem55
{

	bool IsPalindrome(unsigned long long n)
	{
		std::vector<int> stack;

		while (n > 0)
		{
			stack.push_back(n % 10);
			n /= 10;
		}

		for (int i = 0; i < stack.size() / 2; ++i)
		{
			if (stack[i] != stack[stack.size() - i - 1])
				return false;
		}

		return true;
	}

	unsigned long long Reversed(unsigned long long n)
	{
		unsigned long long retval = 0;
		std::vector<int> stack;

		while (n > 0)
		{
			stack.push_back(n % 10);
			n /= 10;
		}

		for (int i = 0; i < stack.size(); ++i)
			retval += stack[i] * pow(10, stack.size() - i - 1);

		return retval;
	}

	unsigned long long ProduceNext(unsigned long long n)
	{
		return n + Reversed(n);
	}

}

void ProblemMap::Problem55()
{
	const int MAX_NUM = 10000;
	const int MAX_ITERATIONS = 50;

	std::unordered_set<unsigned long long> fail = std::unordered_set<unsigned long long>();

	int counter = 0;

	for (int i = 0; i < MAX_NUM; ++i)
	{
		int loops = 1;
		unsigned long long num = Problem55::ProduceNext(i);
		unsigned long long lastNum = 0;

		while (!Problem55::IsPalindrome(num) && loops < MAX_ITERATIONS)
		{
			lastNum = num;
			num = Problem55::ProduceNext(num);

			++loops;
		}

		if (loops == MAX_ITERATIONS)
			++counter;
	}

	std::cout << counter << std::endl;
}
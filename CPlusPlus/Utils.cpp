#include <stdlib.h>
#include <vector>
#include <iostream>
#include <experimental/generator>
#include "Utils.h"

namespace Utils
{
	/*
	Input: an integer n > 1

	Let A be an array of Boolean values, indexed by integers 2 to n,
	initially all set to true.

	for i = 2, 3, 4, ..., not exceeding √n:
	if A[i] is true:
	for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n :
	A[j] := false

	Output: all i such that A[i] is true.
	*/
	int_generator Seive()
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

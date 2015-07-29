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

	int_generator Fib();
}

#endif // UTILS 
#include <iostream>
#include <string>

#include "ProblemMap.h"

void DoCurrentProblem()
{
	ProblemMap::Problem45();
}

int main()
{
	DoCurrentProblem();
	std::cout << "Press any key to exit..." << std::endl;
	std::string input;
	std::getline(std::cin, input);
	return 0;
}
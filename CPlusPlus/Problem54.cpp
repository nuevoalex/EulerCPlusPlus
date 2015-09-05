#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "ProblemMap.h"
#include "Poker.h"
#include "Utils.h"

/*
https://projecteuler.net/problem=54
*/

void ProblemMap::Problem54()
{
	std::ifstream myfile("Resources/p054_poker.txt");
	std::string data;

	Poker::Hand player1 = Poker::Hand();
	Poker::Hand player2 = Poker::Hand();

	int player1WinCount = 0;

	int lineNo = 1;

	while (!myfile.eof()) {
		
		getline(myfile, data);

		if (!data.length())
			break;
		
		for (int cIndex = 0; cIndex < data.length(); cIndex += 3)
		{
			Poker::Card card = Poker::Card(data[cIndex], data[cIndex + 1]);
			if (cIndex < 15)
				player1.AddCard(card);
			else
				player2.AddCard(card);
		}

		player1.Evaluate();
		player2.Evaluate();

		if (player1.Beats(player2))
			++player1WinCount;

		++lineNo;
	}

	std::cout << player1WinCount << std::endl;
}
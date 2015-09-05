#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include "Poker.h"
#include "Utils.h"

Poker::Card::Card()
{
}

Poker::Card::Card(char value, char suite)
{
	// TODO if value Ten, Jack, Queen, King, A
	switch (value)
	{
		case ('T') :
			m_value = 10;
			break;
		case ('J') :
			m_value = 11;
			break;
		case ('Q') :
			m_value = 12;
			break;
		case ('K') :
			m_value = 13;
			break;
		case ('A') :
			m_value = 14;
			break;
		default:
			m_value = value - '0';
	}

	switch (suite)
	{
		case ('C'):
			m_suite = Poker::Suite::C;
			break;
		case ('D'):
			m_suite = Poker::Suite::D;
			break;
		case ('H'):
			m_suite = Poker::Suite::H;
			break;
		case ('S'):
			m_suite = Poker::Suite::S;
			break;
		default:
			throw "Invalid suite " + suite;
	}
}

Poker::Hand::Hand()
{
}

void Poker::Hand::AddCard(Card card)
{
	m_cards[m_slotIndex] = card;
	++m_slotIndex;
}

void Poker::Hand::Reset()
{
	m_slotIndex = 0;
	std::fill_n(m_valueCount, 14, 0);
	std::fill_n(m_suiteCount, 4, 0);

	Flush = true;
	Straight = true;

	TwoPair[0] = -1;
	TwoPair[1] = -1;

	FullHouse[0] = -1;
	FullHouse[1] = -1;

	Pair = -1;
	ThreeKind = -1;
	FourKind = -1;
}

bool SortByValue(Poker::Card &lhs, Poker::Card &rhs) { return lhs.GetValue() < rhs.GetValue(); }

// Determine what rank this hand has and fill in the appropriate values
void Poker::Hand::Evaluate()
{
	Reset();

	// Sort Cards by value
	std::sort(std::begin(m_cards), std::end(m_cards), SortByValue);

	for (int handIndex = 0; handIndex < HAND_SIZE; ++handIndex)
	{
		Card card = m_cards[handIndex];
		m_valueCount[card.GetValue() - 1]++;
		if (handIndex != 0 && m_cards[handIndex - 1].GetValue() != card.GetValue() - 1)
			Straight = false;

		m_suiteCount[card.GetSuite()]++;
	}

	// Check if we have a flush
	for (int suiteIndex = 0; suiteIndex < 4; ++suiteIndex)
	{
		if (m_suiteCount[suiteIndex] < HAND_SIZE && m_suiteCount[suiteIndex] > 0)
		{
			Flush = false;
			break;
		}
	}

	// Check for pairs if we dont have a flush
	if (!Flush)
	{
		for (int i = 1; i < 14; ++i)
		{
			if (m_valueCount[i] == 4)
				FourKind = i;
			else if (m_valueCount[i] == 3)
			{
				ThreeKind = i;
				FullHouse[1] = i;
			}
			else if (m_valueCount[i] == 2)
			{
				Pair = i;
				FullHouse[0] = i;
				if (TwoPair[0] == -1)
				{
					TwoPair[0] = i;
				}
				else
					TwoPair[1] = i;
			}
		}
	}
}


// Determine if One hand beats another
bool Poker::Hand::Beats(Hand otherHand)
{
	// Straight Flush : All cards are consecutive values of same suit. Royal ties in automatically
	bool player1SF = Flush && Straight;
	bool player2SF = otherHand.Straight && otherHand.Flush;

	if (player1SF != player2SF)
		return player1SF;

	// Four of a Kind : Four cards of the same value.
	if (FourKind != otherHand.FourKind)
		return FourKind > otherHand.FourKind;

	// Full House : Three of a kind and a pair.
	bool player1FH = FullHouse[1] != -1 && FullHouse[0] != -1;
	bool player2FH = otherHand.FullHouse[1] != -1 && otherHand.FullHouse[0] != -1;

	if (player1FH || player2FH)
	{
		if (player1FH && player2FH)
		{
			if (FullHouse[1] == otherHand.FullHouse[1])
			{
				if (FullHouse[0] != otherHand.FullHouse[0])
					return FullHouse[0] > otherHand.FullHouse[0];
			}
			else
				return FullHouse[1] > otherHand.FullHouse[1];
		}
		else
			return player1FH;
	}

	// Flush : All cards of the same suit.
	if (Flush != otherHand.Flush)
		return Flush;

	// Straight : All cards are consecutive values.
	if (Straight != otherHand.Straight)
		return Straight;

	// Three of a Kind : Three cards of the same value.
	if (ThreeKind != otherHand.ThreeKind)
		return ThreeKind > otherHand.ThreeKind;

	// Two Pairs : Two different pairs.
	if (TwoPair[1] != -1 || otherHand.TwoPair[1] != -1)
	{
		if (TwoPair[1] == otherHand.TwoPair[1])
		{
			if (TwoPair[0] != otherHand.TwoPair[0])
				return TwoPair[0] > otherHand.TwoPair[0];
		}
		else
			return TwoPair[1] > otherHand.TwoPair[1];
	}
	else if (Pair != otherHand.Pair) 	// One Pair : Two cards of the same value.
		return Pair > otherHand.Pair;

	// High Card : Highest value card.
	int highCardIndex = HAND_SIZE - 1;
	int player1Highest = 0;
	int player2Highest = 0;

	while (highCardIndex >= 0)
	{
		player1Highest = m_cards[highCardIndex].GetValue();
		player2Highest = otherHand.m_cards[highCardIndex].GetValue();

		if (player1Highest == player2Highest)
		{
			--highCardIndex;
			continue;
		}
		else
			return player1Highest > player2Highest;
	}

	throw "Failed to determine winner!";

	return false;
}
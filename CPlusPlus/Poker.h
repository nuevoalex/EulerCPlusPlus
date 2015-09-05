#ifndef POKER
#define POKER

namespace Poker
{
	enum Suite
	{
		H,
		D,
		S,
		C,
	};

	class Card
	{
		private:
			int m_value;
			Suite m_suite;
		public:
			const int GetValue() { return m_value; };
			const Suite GetSuite() { return m_suite; };
			Card();
			Card(char value, char suite);
	};

	class Hand
	{
		private:
			static const int HAND_SIZE = 5;

			int m_slotIndex = 0;
			Card m_cards[HAND_SIZE];

			bool Flush = false;
			bool Straight = false;

			void Reset();

			int FourKind = -1;
			int FullHouse[2] = { -1, -1 };
			int ThreeKind = -1;
			int TwoPair[2] = {-1, -1};
			int Pair = -1;

			int m_valueCount[14];
			int m_suiteCount[4];

		public:
			Hand();
			void AddCard(Card card);
			void Evaluate();
			bool Beats(Hand opponent);
	};
}

#endif // POKER 
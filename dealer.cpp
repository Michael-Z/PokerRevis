#include <algorithm>

#include "vars.h"

Dealer::Dealer()
{
	FillDeck();
	deckPos = deck.size() - 1;
}

Dealer::~Dealer()
{
}

void Dealer::FillDeck()
{
	deck.clear();

	deck.push_back("A-H");
	deck.push_back("A-S");
	deck.push_back("A-C");
	deck.push_back("A-D");

	deck.push_back("2-H");
	deck.push_back("2-S");
	deck.push_back("2-C");
	deck.push_back("2-D");

	deck.push_back("3-H");
	deck.push_back("3-S");
	deck.push_back("3-C");
	deck.push_back("3-D");

	deck.push_back("4-H");
	deck.push_back("4-S");
	deck.push_back("4-C");
	deck.push_back("4-D");

	deck.push_back("5-H");
	deck.push_back("5-S");
	deck.push_back("5-C");
	deck.push_back("5-D");

	deck.push_back("6-H");
	deck.push_back("6-S");
	deck.push_back("6-C");
	deck.push_back("6-D");

	deck.push_back("7-H");
	deck.push_back("7-S");
	deck.push_back("7-C");
	deck.push_back("7-D");

	deck.push_back("8-H");
	deck.push_back("8-S");
	deck.push_back("8-C");
	deck.push_back("8-D");

	deck.push_back("9-H");
	deck.push_back("9-S");
	deck.push_back("9-C");
	deck.push_back("9-D");

	deck.push_back("10-H");
	deck.push_back("10-S");
	deck.push_back("10-C");
	deck.push_back("10-D");

	deck.push_back("J-H");
	deck.push_back("J-S");
	deck.push_back("J-C");
	deck.push_back("J-D");

	deck.push_back("Q-H");
	deck.push_back("Q-S");
	deck.push_back("Q-C");
	deck.push_back("Q-D");

	deck.push_back("K-H");
	deck.push_back("K-S");
	deck.push_back("K-C");
	deck.push_back("K-D");

	if (deckPos < 51)
	{
		deckPos = deck.size() - 1;
	}
}

void Dealer::Shuffle()
{
	srand(time(NULL));
	random_shuffle(deck.begin(), deck.end());
}

void Dealer::Deal()
{
	// If we haven't had the flop, check for
	// current player and deal their hand.
	if (!game.IsFlop())
	{
		while (game.GetCurrentPlayer() != FINISHED)
		{
			switch (game.GetCurrentPlayer())
			{
			case FRESH:
			case PLAYER:
				DealToPlayer();
				game.ChangeCurrentPlayer(CPU1);
				break;

			case CPU1:
				DealToAI(game.ReturnAIObject(CPU1));
				game.ChangeCurrentPlayer(CPU2);
				break;

			case CPU2:
				DealToAI(game.ReturnAIObject(CPU2));
				game.ChangeCurrentPlayer(CPU3);
				break;

			case CPU3:
				DealToAI(game.ReturnAIObject(CPU3));
				game.ChangeCurrentPlayer(CPU4);
				break;

			case CPU4:
				DealToAI(game.ReturnAIObject(CPU4));
				game.ChangeCurrentPlayer(FINISHED);
				break;
			}
		}
	}
	else if (!game.IsBettingRound())
	{
		DealToCommunity();
	}
}

void Dealer::DealToPlayer()
{
	for (int handPos = 0; handPos < HOLE_CARDS; handPos++)
	{	
		string card = deck.at(deckPos);
		game.ReturnPlayerObject()->SetHand(card, handPos);
		deck.pop_back();
		deckPos--;
	}
}

void Dealer::DealToAI(AI* ai)
{
	for (int handPos = 0; handPos < HOLE_CARDS; handPos++)
	{	
		string card = deck.at(deckPos);
		ai->SetHand(card, handPos);
		deck.pop_back();
		deckPos--;
	}
}

void Dealer::DealToCommunity()
{
	string card = " ";

	if (!game.IsFlop())
	{
		for (int i = 0; i < FLOP_SIZE; i++)
		{
			card = deck.at(deckPos);
			communityDeck.push_back(card);
			deck.pop_back();
			deckPos--;
		}
		
		game.SetFlop(true);
	}
	else if (game.IsFlop() && !game.IsTurn())
	{
		card = deck.at(deckPos);
		communityDeck.push_back(card);
		deck.pop_back();
		deckPos--;

		game.SetTurn(true);
	}
	else if (game.IsFlop() && game.IsTurn() && !game.IsRiver())
	{
		card = deck.at(deckPos);
		communityDeck.push_back(card);
		deck.pop_back();
		deckPos--;

		game.SetRiver(true);
	}

	cin.get();
}

int Dealer::GetDeckPos(void)
{
	return deckPos;
}

string Dealer::GetCommunityCard(int communityDeckPos)
{
	if (game.IsFlop())
	{
		switch (communityDeckPos)
		{
		case 1:
			return communityDeck.at(0);
			break;

		case 2:
			return communityDeck.at(1);
			break;

		case 3:
			return communityDeck.at(2);
			break;

		case 4:
			if (game.IsTurn())
			{
				return communityDeck.at(3);
			}
			break;

		case 5:
			if(game.IsRiver())
			{
				return communityDeck.at(4);
			}
			break;
		}
	}
}

vector<string>& Dealer::GetCommunityDeck()
{
	return communityDeck;
}

void Dealer::ShowCommunityCards()
{
	if (communityDeck.size() == 0)
	{	
		cout << "--- --- --- --- ---";
		return;
	}

	if (game.IsFlop())
	{
		cout << communityDeck.at(0) << " " << communityDeck.at(1) << " " << communityDeck.at(2) << " --- ---";
	}
	else if (game.IsFlop() && !game.IsTurn())
	{
		cout << communityDeck.at(0) << " " << communityDeck.at(1) << " " << communityDeck.at(2) << " " << communityDeck.at(3) << " ---";
	}
	else if (game.IsFlop() && game.IsTurn() && !game.IsRiver())
	{
		cout << communityDeck.at(0) << " " << communityDeck.at(1) << " " << communityDeck.at(2) << " " << communityDeck.at(3) << " " << communityDeck.at(4);
	}
}
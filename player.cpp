#include "vars.h"

/**********************
 * PLAYER DEFINITIONS *
 **********************/

Player::Player()
{
	playState  = true;
	playerName = " ";
	money		 = 500;

	playerHand.push_back(" ");
	playerHand.push_back(" ");
}

Player::~Player()
{
}

bool Player::IsTurn()
{
	return turnState;
}

void Player::SetTurn(bool state)
{
	turnState = state;
}

void Player::SetHand(string card, int handPos)
{
	playerHand.at(handPos) = card;
}

void Player::ShowHand()
{
	for (int i = 0; i < HOLE_CARDS; i++)
	{
		cout << playerHand.at(i) << " ";
	}
}

string Player::GetCard(int handPos)
{
	return playerHand.at(handPos);
}

void Player::SetName(string name)
{
	playerName = name;
}

string Player::ShowName()
{
	return playerName;
}

void Player::ShowMoney()
{
	if (money >= 0 && money < 10)
	{
		cout << "      Money: ";
		cout << money << "     |";
	}
	else if (money >= 10 && money < 100)
	{
		cout << "	      Money: ";
		cout << money << "    |";
	}
	else if (money >= 100 && money < 1000)
	{
		cout << "	      Money: ";
		cout << money << "   |";
	}
	else if (money >= 1000 && money < 10000)
	{
		cout << "	      Money: ";
		cout << money << "  |";
	}
	else if (money >= 10000 && money < 100000)
	{
		cout << "	      Money: ";
		cout << money << " |";
	}
	else if (money >= 100000 && money < 1000000)
	{
		cout << "	     Money: ";
		cout << money << " |";
	}
	else if (money >= 1000000 && money < 10000000)
	{
		cout << "	    Money: ";
		cout << money << " |";
	}
}

void Player::ShowMoney(int cpu)
{
	if (cpu != CPU1)
	{
		if (cpu == CPU4)
		{
			if (money >= 0 && money < 10)
			{
				cout << "  Money: ";
				cout << money << "      ";
			}
			else if (money >= 10 && money < 100)
			{
				cout << "  Money: ";
				cout << money << "     ";
			}
			else if (money >= 100 && money < 1000)
			{
				cout << "  Money: ";
				cout << money << "    ";
			}
			else if (money >= 1000 && money < 10000)
			{
				cout << "  Money: ";
				cout << money << "   ";
			}
			else if (money >= 10000 && money < 100000)
			{
				cout << "  Money: ";
				cout << money << "  ";
			}
			else if (money >= 100000 && money < 1000000)
			{
				cout << "  Money: ";
				cout << money << " ";
			}
			else if (money >= 1000000 && money < 10000000)
			{
				cout << " Money: ";
				cout << money << " ";
			}
		}
		else
		{
			if (money >= 0 && money < 10)
			{
				cout << "  Money: ";
				cout << money << "      |";
			}
			else if (money >= 10 && money < 100)
			{
				cout << "  Money: ";
				cout << money << "     |";
			}
			else if (money >= 100 && money < 1000)
			{
				cout << "  Money: ";
				cout << money << "    |";
			}
			else if (money >= 1000 && money < 10000)
			{
				cout << "  Money: ";
				cout << money << "   |";
			}
			else if (money >= 10000 && money < 100000)
			{
				cout << "  Money: ";
				cout << money << "  |";
			}
			else if (money >= 100000 && money < 1000000)
			{
				cout << "  Money: ";
				cout << money << " |";
			}
			else if (money >= 1000000 && money < 10000000)
			{
				cout << " Money: ";
				cout << money << " |";
			}
		}
	}
}

void Player::SetMoney(int amount)
{
	money = amount;
}

int Player::GetInputFromPlayer()
{
	int choice;

	cout << "1 - CHECK" << endl;
	cout << "2 - CALL"  << endl;
	cout << "3 - BET"   << endl;
	cout << "4 - RAISE" << endl;
	cout << "5 - FOLD"  << endl;
	cin  >> choice;
	cin.ignore();

	return choice;
}

void Player::TurnAction()
{
	while (IsTurn())
	{
		switch(GetInputFromPlayer())
		{
		case CHECK:
			Check();
			break;

		case CALL:
			Call();
			break;

		case BET:
			Bet();
			break;

		case RAISE:
			Raise();
			break;

		case FOLD:
			Fold();
			break;
		}
	}
}

void Player::Check()
{
	if ( game.GetLastAction() == CALL ||
		 game.GetLastAction() == BET  ||
		 game.GetLastAction() == RAISE )
	{
		return;
	}
	else
	{
		game.SetLastAction(CHECK);
		SetTurn(false);
	}
}

void Player::Call()
{
	if (game.GetLastAction() == CHECK)
	{
		return;
	}
	else
	{
		if (money <= game.GetCurrentBet())
		{
			game.SetCurrentPot(game.GetCurrentBet() + money);
			money = 0;
			SetTurn(false);
		}
		else
		{
			game.SetCurrentPot(game.GetCurrentBet() + game.GetCurrentBet());
			money -= game.GetCurrentBet();
			SetTurn(false);
		}
	}
}

void Player::Bet()
{
	if ( game.GetLastAction() == CALL ||
		 game.GetLastAction() == BET  ||
		 game.GetLastAction() == RAISE )
	{
		return;
	}
	else
	{
		int amount = 0;
		cout << "Amount to bet: ";
		cin  >> amount;

		game.SetCurrentBet(amount);
		game.SetCurrentPot(amount);
		game.SetLastAction(BET);

		money -= amount;

		SetTurn(false);
	}
}

void Player::Raise()
{
	if (game.GetLastAction() == CHECK)
	{
		return;
	}
	else
	{
		int amount = 0;
		cout << "Amount to raise: ";
		cin  >> amount;

		money -= game.GetCurrentBet() + amount;
		game.SetCurrentBet(game.GetCurrentBet() + amount);
		game.SetLastAction(RAISE);

		SetTurn(false);
	}
}

void Player::Fold()
{
	for (int i = 0; i < HOLE_CARDS; i++)
	{
		playerHand.at(i) = " ";
	}
	
	SetTurn(false);
	playState = false;

	game.SetLastAction(FOLD);
}

/*******************
 *	AI DEFINITIONS *
 *******************/

AI::AI()
{
	playerHand.push_back(" ");
	playerHand.push_back(" ");

	playerName = " ";
	playState  = true;
	risky	   = false;

	currentRiskFactor = 100.0;
}

AI::~AI()
{
}

void AI::AI_ShowCardsHidden()
{
	for (int i = 0; i < HOLE_CARDS; ++i)
	{
		cout << "- ";
	}
}

void AI::Compare()
{
	highCard = FindHighCard();

	if (!game.IsFlop())
	{
		if (numsInHand.at(0) == numsInHand.at(1) && suitsInHand.at(0) == suitsInHand.at(1))
		{
			currentRiskFactor -= (numberMatchBonus + suitMatchBonus) + highCard;
		}
		else if (numsInHand.at(0) == numsInHand.at(1))
		{
			currentRiskFactor -= numberMatchBonus + highCard;
		}
		else if (suitsInHand.at(0) == suitsInHand.at(1))
		{
			currentRiskFactor -= suitMatchBonus + highCard;
		}
		else
		{
			if (highCard > 0 && highCard <= 5)
			{
				if (numsInHand.at(0) == --numsInHand.at(1) ||
					numsInHand.at(1) == --numsInHand.at(0))
				{
					currentRiskFactor -= 2;
				}
				else
				{
					currentRiskFactor -= 1;
				}
			}
			else if (highCard > 5 && highCard <= 7)
			{
				if (numsInHand.at(0) == --numsInHand.at(1) ||
					numsInHand.at(1) == --numsInHand.at(0))
				{
					currentRiskFactor -= 4;
				}
				else
				{
					currentRiskFactor -= 3;
				}
			}
			else if (highCard > 7 && highCard <= 10)
			{
				if (numsInHand.at(0) == --numsInHand.at(1) ||
					numsInHand.at(1) == --numsInHand.at(0))
				{
					currentRiskFactor -= 6;
				}
				else
				{
					currentRiskFactor -= 5;
				}
			}
			else
			{
				if (numsInHand.at(0) == --numsInHand.at(1) ||
					numsInHand.at(1) == --numsInHand.at(0))
				{
					currentRiskFactor -= 6;
				}
				currentRiskFactor -= 7;
			}
		}
	}
}

void AI::ExtractCardData(vector<string>& communityDeck)
{
	char c = ' ';
	int  cardNumber = 0;

	if (!game.IsFlop())
	{
		for (int i = 0; i < HOLE_CARDS; i++)
		{
			suitsInHand.push_back(playerHand.at(i).at(2));
			c = playerHand.at(i).at(0);

			cardNumber = game.ConvertCharToInt(c);
			numsInHand.push_back(cardNumber);
		}
	}
	else if (game.IsFlop() && !game.IsTurn())
	{
		for (int i = 0; i < FLOP_SIZE; i++)
		{
			suitsInCommunity.push_back(communityDeck.at(i).at(2));
			c = communityDeck.at(i).at(0);

			cardNumber = game.ConvertCharToInt(c);
			numsInCommunity.push_back(cardNumber);
		}
	}
	else if (game.IsTurn() && !game.IsRiver())
	{
		suitsInCommunity.push_back(communityDeck.at(3).at(2));
		c = communityDeck.at(3).at(0);

		cardNumber = game.ConvertCharToInt(c);
		this->numsInCommunity.push_back(cardNumber);
	}
	else
	{
		suitsInCommunity.push_back(communityDeck.at(4).at(2));
		c = communityDeck.at(4).at(0);

		cardNumber = game.ConvertCharToInt(c);
		numsInCommunity.push_back(cardNumber);
	}
}

int AI::FindHighCard()
{
	int highCard = 0;

	if (numsInCommunity.size() == 0)
	{
		if (numsInHand.at(0) >= numsInHand.at(1))
		{
			highCard = numsInHand.at(0);
		}
		else
		{
			highCard = numsInHand.at(1);
		}
	}
	else if (numsInCommunity.size() > 0)
	{
		for (int i = 0; i < numsInHand.size(); i++)
		{
			for (int j = 0; j < numsInCommunity.size(); j++)
			{
				if (numsInHand.at(i) >= numsInCommunity.at(j))
				{
					highCard = numsInHand.at(i);
				}
				else
				{
					for (int k = 0; k < numsInCommunity.size(); k++)
					{
						if (numsInCommunity.at(k) > highCard)
						{
							highCard = numsInCommunity.at(k);
						}
					}
				}
			}
		}

		return highCard;
	}
}

void AI::Determine()
{
	srand(time(NULL));

	if ((int)currentRiskFactor % 2 != 0)
	{
		if (highCard >= 7)
		{
			if (highCard % 2 != 0)
			{
				risky = true;
			}
		}
	}

	int	howRisky = rand() % 25; //Used for risky moves

	// double decisionFactor = 0.0;

	if (!game.IsFlop())
	{
		if (risky)
		{
			if (game.GetLastAction() == CALL  ||
				game.GetLastAction() == BET   ||
				game.GetLastAction() == RAISE || 
				game.GetLastAction() == FOLD)
			{
				if (howRisky >= 12)
				{
					AI_Raise();
					return;
				}
				else
				{
					AI_Call();
					return;
				}
			}
			else if (game.GetLastAction() == CHECK)
			{
				AI_Bet();
				return;
			}
		}
		else
		{
			if (currentRiskFactor >= 98)
			{
				if (game.GetLastAction() != CHECK && highCard <= 5)
				{
					if (howRisky <= 12)
					{
						AI_Fold();
						return;
					}
					else if (game.GetLastAction() == CALL  ||
							 game.GetLastAction() == BET   ||
							 game.GetLastAction() == RAISE &&
						     game.GetCurrentBet() != money * 0.75f)
					{
						AI_Call();
						return;
					}
				}
				else
				{
					AI_Check();
					return;
				}
			}
			else if (currentRiskFactor >= 90 && currentRiskFactor < 98)
			{
				if (game.GetLastAction() == CALL  ||
					game.GetLastAction() == RAISE ||
					game.GetLastAction() == FOLD  ||
					game.GetLastAction() == BET)
				{
					if (howRisky < 12 && highCard <= 5)
					{
						if (game.GetCurrentBet() > money * 0.75f)
						{
							AI_Fold();
							return;
						}
					}
					else
					{
						if (game.GetCurrentBet() > money || (highCard < 10 && howRisky <= 12))
						{
							AI_Fold();
							return;
						}
						else
						{
							AI_Call();
							return;
						}
					}
				}
				else if (game.GetLastAction() == CHECK)
				{
						AI_Check();
						return;
				}
			}
			else if (currentRiskFactor < 90)
			{
				if (currentRiskFactor > 80)
				{
					if (game.GetLastAction() == CALL  ||
						game.GetLastAction() == RAISE ||
						game.GetLastAction() == FOLD  ||
						game.GetLastAction() == BET)
					{
						AI_Call();
						return;
					}
					else
					{
						AI_Check();
						return;
					}
				}
				else
				{
					if (game.GetLastAction() == CHECK && howRisky >= 12)
					{
						AI_Bet();
						return;
					}
					else if (currentRiskFactor <= 80 && howRisky >= 12)
					{
						AI_Raise();
						return;
					}
					else
					{
						AI_Call();
						return;
					}
				}
			}
		}
	}
}

void AI::AI_TurnAction()
{
	ExtractCardData(game.ReturnDealerObject()->GetCommunityDeck());
	Compare();
	Determine();

	cout << "Current Hand: " << playerHand.at(0) << " " << playerHand.at(1) << endl;
	cout << "Current High Card: " << highCard << endl;
	cout << "Current Risk Factor: " << currentRiskFactor << endl;
	cout << "Felt risky?: ";

	if (risky)
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}

	cout << endl;
	cout << "Current Pot: " << game.GetCurrentPot() << endl;

	cin.ignore();
	cin.get();
}

void AI::AI_Check()
{
	cout << playerName << " checks!" << endl;
	game.SetLastAction(CHECK);
}

void AI::AI_Call()
{
	cout << playerName << " calls!" << endl;

	if (game.GetCurrentBet() >= money)
	{
		cout << playerName << " goes all in!" << endl;
		game.SetCurrentPot(game.GetCurrentBet() + money);
		money = 0;
		playState = false;
	}
	else
	{
		game.SetCurrentPot(game.GetCurrentBet() + game.GetCurrentBet());
		money -= game.GetCurrentBet();

		game.SetLastAction(CALL);
	}
}

void AI::AI_Bet()
{
	cout << playerName << " bets!" << endl;
	game.SetLastAction(BET);
}

void AI::AI_Raise()
{
	cout << playerName << " raises!" << endl;
	game.SetLastAction(RAISE);
}

void AI::AI_Fold()
{
	cout << playerName << " folds!" << endl;
	game.SetLastAction(FOLD);
}


#include "vars.h"

Game::Game()
{
	player	 = new Player;
	dealer	 = new Dealer;
	cpu1	 = new AI;
	cpu2	 = new AI;
	cpu3	 = new AI;
	cpu4	 = new AI;

	Init();
}

Game::~Game(void)
{
	delete player;
	delete dealer;
	delete cpu1;
	delete cpu2;
	delete cpu3;
	delete cpu4;
}

void Game::CleanUp()
{
	delete player;
	delete dealer;
	delete cpu1;
	delete cpu2;
	delete cpu3;
	delete cpu4;
}

void Game::Init()
{
	endOfRound		= false;
	endOfGame		= false;
	flop			= false;
	turn			= false;
	river			= false;
	bettingRound	= true;
	lastAction		= 0;
	currentPlayer	= FRESH;
	currentBet		= 35;
	currentPot		= 0;
	playersLeft		= 5;

	cpu.clear();

	cpu.push_back(cpu1);
	cpu.push_back(cpu2);
	cpu.push_back(cpu3);
	cpu.push_back(cpu4);

	cpu1->SetName("Mandy");
	cpu2->SetName("Joe");
	cpu3->SetName("George");
	cpu4->SetName("Mustaffa!");

	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << "                          Enter your player name: ";
	
	string nameInput;
	cin  >> nameInput;
	player->SetName(nameInput);
	system("cls");

	dealer->Shuffle();
	dealer->Deal();
	Interface();
}

void Game::Interface()
{
	system("cls");

	cout << endl << endl << endl << endl;
	if (game.GetCurrentPlayer() == CPU1)
	{
		cout << "	-" << cpu1->ShowName() << "-" << "    |     *" << cpu2->ShowName() << "*" << "      |    *" << cpu3->ShowName() << "*" << "    |    *" << cpu4->ShowName() << "*" << endl;
	}
	else if (game.GetCurrentPlayer() == CPU2)
	{
		cout << "	*" << cpu1->ShowName() << "*" << "    |     -" << cpu2->ShowName() << "-" << "      |    *" << cpu3->ShowName() << "*" << "    |    *" << cpu4->ShowName() << "*" << endl;
	}
	else if (game.GetCurrentPlayer() == CPU3)
	{
		cout << "	*" << cpu1->ShowName() << "*" << "    |     *" << cpu2->ShowName() << "*" << "      |    -" << cpu3->ShowName() << "-" << "    |    *" << cpu4->ShowName() << "*" << endl;
	}
	else if (game.GetCurrentPlayer() == CPU4)
	{
		cout << "	*" << cpu1->ShowName() << "*" << "    |     *" << cpu2->ShowName() << "*" << "      |    *" << cpu3->ShowName() << "*" << "    |    -" << cpu4->ShowName() << "-" << endl;
	}
	else
	{
		cout << "	*" << cpu1->ShowName() << "*" << "    |     *" << cpu2->ShowName() << "*" << "      |    *" << cpu3->ShowName() << "*" << "    |    *" << cpu4->ShowName() << "*" << endl;
	}
	cout << "       Hand: "; cpu1->AI_ShowCardsHidden(); cout << "  |   Hand: "; cpu2->AI_ShowCardsHidden(); cout << "   |   Hand: "; cpu3->AI_ShowCardsHidden(); cout << "   |   Hand: "; cpu4->AI_ShowCardsHidden(); cout << endl;
	cpu1->ShowMoney(); cpu2->ShowMoney(CPU2);  cpu3->ShowMoney(CPU3); cpu4->ShowMoney(CPU4); cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "                            "; dealer->ShowCommunityCards();
	cout << endl;
	cout << endl;
	cout << "                              "; ShowLastAction(GetCurrentPlayer());
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "   [1] - Check";
	if (game.GetCurrentPlayer() == PLAYER)
	{
		cout << "                || -" << player->ShowName() << "- ||" << endl;
	}
	else
	{
		cout << "                || *" << player->ShowName() << "* ||" << endl;
	}

	cout << "   [2] - Call";
	cout << "                 Hand: "; player->ShowHand(); cout << endl;

	cout << "   [3] - Bet                ";
	player->ShowPlayerMoney(); cout << endl;

	cout << "   [4] - Raise" << endl;
	cout << "   [5] - Fold" << endl;
}

void Game::UpdateInterface()
{
}

int Game::GetCurrentPlayer()
{
	return currentPlayer;
}

int Game::GetLastAction()
{
	return lastAction;
}

void Game::SetLastAction(int action)
{
	lastAction = action;
}

long Game::GetCurrentBet()
{
	return currentBet;
}

void Game::SetCurrentBet(int amount)
{
	currentBet = amount;
}

long Game::GetCurrentPot()
{
	return currentPot;
}

void Game::SetCurrentPot(int amount)
{
	currentPot += amount;
}

bool Game::IsFlop(void)
{
	return flop;
}

bool Game::IsTurn()
{
	return turn;
}

bool Game::IsRiver()
{
	return river;
}

bool Game::IsBettingRound()
{
	return bettingRound;
}

void Game::ShowLastAction(int player)
{
	if (player == FRESH)
	{
		cout << " ";
	}
	else if (player == PLAYER)
	{
		if (GetLastAction() == CHECK)
		{
			cout << this->player->ShowName() << " checks!";
		}
		else if (GetLastAction() == CALL)
		{
			cout << this->player->ShowName() << " calls!";
		}
		else if (GetLastAction() == BET)
		{
			if (!invalidCheck)
			{
				cout << this->player->ShowName() << " bets $" << GetCurrentBet();
			}
		}
		else if (GetLastAction() == RAISE)
		{
			cout << this->player->ShowName() << " raises $" << GetCurrentBet();
		}
		else if (GetLastAction() == FOLD)
		{
			cout << this->player->ShowName() << " folds!";
		}
		else if (GetLastAction() == ALL_IN)
		{
			cout << this->player->ShowName() << " goes all in!";
		}
	}
	
	else if (player == CPU1)
	{
		if (GetLastAction() == CHECK)
		{
			cout << this->cpu1->ShowName() << " checks!";
		}
		else if (GetLastAction() == CALL)
		{
			cout << this->cpu1->ShowName() << " calls!";
		}
		else if (GetLastAction() == BET)
		{
			cout << this->cpu1->ShowName() << " bets $" << GetCurrentBet();
		}
		else if (GetLastAction() == RAISE)
		{
			cout << this->cpu1->ShowName() << " raises $" << GetCurrentBet();
		}
		else if (GetLastAction() == FOLD)
		{
			cout << this->cpu1->ShowName() << " folds!";
		}
		else if (GetLastAction() == ALL_IN)
		{
			cout << this->cpu1->ShowName() << " goes all in!";
		}
	}

	else if (player == CPU2)
	{
		if (GetLastAction() == CHECK)
		{
			cout << this->cpu2->ShowName() << " checks!";
		}
		else if (GetLastAction() == CALL)
		{
			cout << this->cpu2->ShowName() << " calls!";
		}
		else if (GetLastAction() == BET)
		{
			cout << this->cpu2->ShowName() << " bets $" << GetCurrentBet();
		}
		else if (GetLastAction() == RAISE)
		{
			cout << this->cpu2->ShowName() << " raises $" << GetCurrentBet();
		}
		else if (GetLastAction() == FOLD)
		{
			cout << this->cpu2->ShowName() << " folds!";
		}
		else if (GetLastAction() == ALL_IN)
		{
			cout << this->cpu2->ShowName() << " goes all in!";
		}
	}

	else if (player == CPU3)
	{
		if (GetLastAction() == CHECK)
		{
			cout << this->cpu3->ShowName() << " checks!";
		}
		else if (GetLastAction() == CALL)
		{
			cout << this->cpu3->ShowName() << " calls!";
		}
		else if (GetLastAction() == BET)
		{
			cout << this->cpu3->ShowName() << " bets $" << GetCurrentBet();
		}
		else if (GetLastAction() == RAISE)
		{
			cout << this->cpu3->ShowName() << " raises $" << GetCurrentBet();
		}
		else if (GetLastAction() == FOLD)
		{
			cout << this->cpu3->ShowName() << " folds!";
		}
		else if (GetLastAction() == ALL_IN)
		{
			cout << this->cpu3->ShowName() << " goes all in!";
		}
	}

	else if (player == CPU4)
	{
		if (GetLastAction() == CHECK)
		{
			cout << this->cpu4->ShowName() << " checks!";
		}
		else if (GetLastAction() == CALL)
		{
			cout << this->cpu4->ShowName() << " calls!";
		}
		else if (GetLastAction() == BET)
		{
			cout << this->cpu4->ShowName() << " bets $" << GetCurrentBet();
		}
		else if (GetLastAction() == RAISE)
		{
			cout << this->cpu4->ShowName() << " raises $" << GetCurrentBet();
		}
		else if (GetLastAction() == FOLD)
		{
			cout << this->cpu4->ShowName() << " folds!";
		}
		else if (GetLastAction() == ALL_IN)
		{
			cout << this->cpu4->ShowName() << " goes all in!";
		}
	}
}

void Game::SetFlop(bool isFlop)
{
	flop = isFlop;
}

void Game::SetTurn(bool isTurn)
{
	turn = isTurn;
}

void Game::SetRiver(bool isRiver)
{
	river = isRiver;
}

void Game::SetBettingRound(bool isBettingRound)
{
	bettingRound = isBettingRound;
}

bool Game::InvalidCheck()
{
	return invalidCheck;
}

void Game::SetInvalidCheck(bool state)
{
	invalidCheck = state;
}

void Game::Start( )
{
	// While it is not the end of the round check 
	// currentPlayer to determine who has the next move.
	game.ChangeCurrentPlayer(PLAYER);

	while (!endOfGame)
	{
		while (!endOfRound)
		{
			switch (currentPlayer)
			{
			case PLAYER:
				player->TurnAction();
				game.Interface();
				game.ChangeCurrentPlayer(CPU1);
				break;

			case CPU1:
				cpu1->AI_TurnAction();
				game.Interface();
				game.ChangeCurrentPlayer(CPU2);
				break;

			case CPU2:
				cpu2->AI_TurnAction();
				game.Interface();
				game.ChangeCurrentPlayer(CPU3);
				break;

			case CPU3:
				cpu3->AI_TurnAction();
				game.Interface();
				game.ChangeCurrentPlayer(CPU4);
				break;

			case CPU4:
				cpu4->AI_TurnAction();
				game.Interface();
				game.ChangeCurrentPlayer(FINISHED);
				break;
			}

			if ( game.IsBettingRound() )
			{
				game.SetBettingRound(false);
			}

			if ( game.GetCurrentPlayer() == FINISHED )
			{
				endOfRound	  = true;
				currentPlayer = FRESH;
			}
		}

		dealer->FillDeck();
		dealer->Shuffle();
		dealer->Deal(); 
		game.SetBettingRound(true);
	}
}

void Game::End()
{
}

void Game::ChangeCurrentPlayer(unsigned short nextPlayer)
{
	currentPlayer = nextPlayer;
}

Player* Game::ReturnPlayerObject()
{
	return player;
}

Dealer* Game::ReturnDealerObject()
{
	return dealer;
}

AI* Game::ReturnAIObject(int cpuNum)
{
	// Ensure cpuNum does not exceed the amount of cpu objects
	if (cpuNum < FINISHED)
	{
		switch (cpuNum)
		{
		case CPU1:
			return cpu1;
			break;

		case CPU2:
			return cpu2;
			break;

		case CPU3:
			return cpu3;
			break;

		case CPU4:
			return cpu4;
			break;
		}
	}
	else
	{
		cout << " cpuNum is an invalid integer. Values 1 - 4 only." << endl;
		cout << "               Game::ReturnAIObject( )          ";
		cin.get();
	}
}

int Game::ConvertCharToInt(char c)
{
	if (c == 'A' || c == 'J' || c == 'Q' || c == 'K')
	{
		switch (c)
		{
		case 'A':
			return ACE;

		case 'J':
			return JACK;

		case 'Q':
			return QUEEN;

		case 'K':
			return KING;
		}
	}
	else
	{
		int j = 1;

		for (char i = '1'; i <= '9'; i++, j++)
		{
			if (c == i)
			{
				if (c == '1')
				{
					return 10;
				}
				else
				{
					return j;
				}
			}
		}
	}

	return -1;
}
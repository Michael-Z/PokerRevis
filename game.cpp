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
	currentPlayer	= PLAYER;
	lastAction		= 0;
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

	cout << "Enter your player name: ";
	
	string nameInput;
	cin  >> nameInput;
	player->SetName(nameInput);
	system("cls");
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

void Game::Start( )
{

	dealer->Shuffle();
	dealer->Deal();

	// While it is not the end of the round check 
	// currentPlayer to determine who has the next move.

	game.ChangeCurrentPlayer(PLAYER);
	Interface();

	while (!endOfGame)
	{
		while (!endOfRound)
		{
			Interface();

			switch (currentPlayer)
			{
			case PLAYER:
				player->TurnAction();
				game.ChangeCurrentPlayer(CPU1);
				break;

			case CPU1:
				cpu1->AI_TurnAction();
				game.ChangeCurrentPlayer(CPU2);
				break;

			case CPU2:
				cpu2->AI_TurnAction();
				game.ChangeCurrentPlayer(CPU3);
				break;

			case CPU3:
				cpu3->AI_TurnAction();
				game.ChangeCurrentPlayer(CPU4);
				break;

			case CPU4:
				cpu4->AI_TurnAction();
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
				currentPlayer = PLAYER;
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
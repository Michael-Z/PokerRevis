#include "vars.h"

Game::Game( )
{
	this->player = new Player;
	this->dealer = new Dealer;
	this->cpu1	 = new AI;
	this->cpu2	 = new AI;
	this->cpu3	 = new AI;
	this->cpu4	 = new AI;

	this->Init( );
}

Game::~Game( void )
{
	delete player;
	delete dealer;
	delete cpu1;
	delete cpu2;
	delete cpu3;
	delete cpu4;
}

void Game::CleanUp( )
{
	delete player;
	delete dealer;
	delete cpu1;
	delete cpu2;
	delete cpu3;
	delete cpu4;
}

void Game::Init( void )
{
	this->endOfRound	= false;
	this->endOfGame		= false;
	this->flop			= false;
	this->turn			= false;
	this->river			= false;
	this->bettingRound  = true;
	this->currentPlayer = PLAYER;
	this->lastAction	= 0;
	this->playersLeft   = 5;

	this->cpu.clear( );

	this->cpu.push_back( this->cpu1 );
	this->cpu.push_back( this->cpu2 );
	this->cpu.push_back( this->cpu3 );
	this->cpu.push_back( this->cpu4 );

	this->ReturnAIObject( CPU1 )->SetPlayerName( "Mandy" );
	this->ReturnAIObject( CPU2 )->SetPlayerName( "Joe" );
	this->ReturnAIObject( CPU3 )->SetPlayerName( "George" );
	this->ReturnAIObject( CPU4 )->SetPlayerName( "Mustaffa!" );

	cout << "Enter your player name: ";
	
	string nameInput;
	cin  >> nameInput;
	this->ReturnPlayerObject( )->SetPlayerName( nameInput );
}

void Game::Interface( )
{
}

void Game::UpdateInterface( )
{
}

int Game::GetCurrentPlayer( void )
{
	return this->currentPlayer;
}

int Game::GetLastAction( )
{
	return this->lastAction;
}

void Game::SetLastAction( int action )
{
	this->lastAction = action;
}

long Game::GetCurrentBet( )
{
	return this->currentBet;
}

void Game::SetCurrentBet( int amount )
{
	this->currentBet = amount;
}

long Game::GetCurrentPot( )
{
	return this->currentPot;
}

void Game::SetCurrentPot( int amount )
{
	this->currentPot += amount;
}

bool Game::IsFlop( void )
{
	return this->flop;
}

bool Game::IsTurn( )
{
	return this->turn;
}

bool Game::IsRiver( )
{
	return this->river;
}

bool Game::IsBettingRound( )
{
	return this->bettingRound;
}

void Game::SetFlop( bool isFlop )
{
	this->flop = isFlop;
}

void Game::SetTurn( bool isTurn )
{
	this->turn = isTurn;
}

void Game::SetRiver( bool isRiver )
{
	this->river = isRiver;
}

void Game::SetBettingRound( bool isBettingRound )
{
	this->bettingRound = isBettingRound;
}

void Game::Start( )
{

	this->ReturnDealerObject( )->Shuffle( );
	this->ReturnDealerObject( )->Deal( );

	// While it is not the end of the round check 
	// currentPlayer to determine who has the next move.

	game.ChangeCurrentPlayer( PLAYER );

	while (!endOfGame)
	{
		while (!endOfRound)
		{
			switch (this->currentPlayer)
			{
			case PLAYER:
				this->ReturnPlayerObject( )->TurnAction( );
				game.ChangeCurrentPlayer( CPU1 );
				break;

			case CPU1:
				this->ReturnAIObject( CPU1 )->AI_TurnAction( );
				game.ChangeCurrentPlayer( CPU2 );
				break;

			case CPU2:
				this->ReturnAIObject( CPU2 )->AI_TurnAction( );
				game.ChangeCurrentPlayer( CPU3 );
				break;

			case CPU3:
				this->ReturnAIObject( CPU3 )->AI_TurnAction( );
				game.ChangeCurrentPlayer( CPU4 );
				break;

			case CPU4:
				this->ReturnAIObject( CPU4 )->AI_TurnAction( );
				game.ChangeCurrentPlayer( FINISHED );
				break;
			}

			if ( game.IsBettingRound() )
			{
				game.SetBettingRound( false );
			}

			if ( game.GetCurrentPlayer() == FINISHED )
			{
				this->endOfRound = true;
				this->currentPlayer = PLAYER;
			}
		}

		this->dealer->FillDeck( );
		this->dealer->Shuffle( );
		this->dealer->Deal( ); 
		game.SetBettingRound( true );
	}
}

void Game::End( void )
{
}

void Game::ChangeCurrentPlayer( unsigned short nextPlayer )
{
	this->currentPlayer = nextPlayer;
}

Player* Game::ReturnPlayerObject( )
{
	return this->player;
}

Dealer* Game::ReturnDealerObject( )
{
	return this->dealer;
}

AI* Game::ReturnAIObject( int cpuNum )
{
	// Ensure cpuNum does not exceed the amount of cpu objects
	if (cpuNum < FINISHED)
	{
		switch (cpuNum)
		{
		case CPU1:
			return this->cpu1;
			break;

		case CPU2:
			return this->cpu2;
			break;

		case CPU3:
			return this->cpu3;
			break;

		case CPU4:
			return this->cpu4;
			break;
		}
	}
	else
	{
		cout << " cpuNum is an invalid integer. Values 1 - 4 only." << endl;
		cout << "               Game::ReturnAIObject( )          ";
		cin.get( );
	}
}

int Game::ConvertCharToInt( char c )
{
	if (c == 'A' || c == 'J' || c == 'Q' || c == 'K')
	{
		switch ( c )
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
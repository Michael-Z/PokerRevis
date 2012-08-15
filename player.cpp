#include "vars.h"

/**********************
 * PLAYER DEFINITIONS *
 **********************/

Player::Player( void )
{
	this->playState  = true;
	this->playerName = " ";
	this->money		 = 500;

	this->playerHand.push_back( " " );
	this->playerHand.push_back( " " );
}

Player::~Player( void )
{
}

bool Player::IsTurn( )
{
	return this->turnState;
}

void Player::SetTurn( bool turnState )
{
	this->turnState = turnState;
}

void Player::SetPlayerHand( string card, int handPos )
{
	this->playerHand.at( handPos ) = card;
}

void Player::ShowPlayerHand( )
{
	for (int i = 0; i < HOLE_CARDS; i++)
	{
		cout << this->playerHand.at( i ) << " ";
	}
}

string Player::GetPlayerCard( int handPos )
{
	return this->playerHand.at( handPos );
}

void Player::SetPlayerName( string playerName )
{
	this->playerName = playerName;
}

string Player::GetPlayerName( )
{
	return this->playerName;
}

int Player::GetPlayerMoney( )
{
	return this->money;
}

int Player::GetInputFromPlayer( )
{
	int choice;

	cout << "1 - CHECK" << endl;
	cout << "2 - CALL"  << endl;
	cout << "3 - BET"   << endl;
	cout << "4 - RAISE" << endl;
	cout << "5 - FOLD"  << endl;
	cin  >> choice;
	cin.ignore( );

	return choice;
}

void Player::TurnAction( void )
{
	while ( this->IsTurn() )
	{
		switch( this->GetInputFromPlayer() )
		{
		case CHECK:
			this->Check( );
			break;

		case CALL:
			this->Call( );
			break;

		case BET:
			this->Bet( );
			break;

		case RAISE:
			this->Raise( );
			break;

		case FOLD:
			this->Fold( );
			break;
		}
	}
}

void Player::Check( )
{
	if ( game.GetLastAction() == CALL ||
		 game.GetLastAction() == BET  ||
		 game.GetLastAction() == RAISE )
	{
		return;
	}
	else
	{
		game.SetLastAction( CHECK );
		this->SetTurn( false );
	}
}

void Player::Call( )
{
	if ( game.GetLastAction() == CHECK )
	{
		return;
	}
	else
	{
		if ( this->money <= game.GetCurrentBet() )
		{
			game.SetCurrentPot( game.GetCurrentBet( ) + this->money );
			this->money = 0;
			this->SetTurn( false );
		}
		else
		{
			game.SetCurrentPot( game.GetCurrentBet( ) + game.GetCurrentBet( ) );
			this->money -= game.GetCurrentBet( );
			this->SetTurn( false );
		}
	}
}

void Player::Bet( )
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

		game.SetCurrentBet( amount );
		game.SetCurrentPot( amount );
		game.SetLastAction( BET );

		this->money -= amount;

		this->SetTurn( false );
	}
}

void Player::Raise( )
{
	if ( game.GetLastAction() == CHECK )
	{
		return;
	}
	else
	{
		int amount = 0;
		cout << "Amount to raise: ";
		cin  >> amount;

		this->money -= game.GetCurrentBet( ) + amount;
		game.SetCurrentBet( game.GetCurrentBet() + amount );
		game.SetLastAction( RAISE );

		this->SetTurn( false );
	}
}

void Player::Fold( )
{
	for (int i = 0; i < HOLE_CARDS; i++)
	{
		this->playerHand.at( i ) = " ";
	}
	
	this->SetTurn( false );
	this->playState = false;

	game.SetLastAction( FOLD );
}

/*******************
 *	AI DEFINITIONS *
 *******************/

AI::AI( void )
{
	this->playerHand.push_back( " " );
	this->playerHand.push_back( " " );

	this->playerName = " ";
	this->playState  = true;
	this->risky	 = false;

	this->currentRiskFactor = 100.0;
}

AI::~AI( void )
{
}

void AI::Compare( )
{
	int highCard = this->FindHighCard( );

	if ( !game.IsFlop() )
	{
		if ( this->numsInHand.at(0) == this->numsInHand.at(1) && this->suitsInHand.at(0) == this->suitsInHand.at(1) )
		{
			this->currentRiskFactor -= (numberMatchBonus + suitMatchBonus / 2) + highCard;
		}
		else if ( this->numsInHand.at(0) == this->numsInHand.at(1) )
		{
			this->currentRiskFactor -= (numberMatchBonus / 2) + highCard;
		}
		else if ( this->suitsInHand.at(0) == this->suitsInHand.at(1) )
		{
			this->currentRiskFactor -= (suitMatchBonus / 2) + highCard;
		}
		else
		{
			if (highCard > 0 && highCard <= 5)
			{
				this->currentRiskFactor -= 1;
			}
			else if (highCard > 5 && highCard <= 10)
			{
				this->currentRiskFactor -= 2;
			}
			else
			{
				this->currentRiskFactor -= 3;
			}
		}
	}
}

void AI::ExtractCardData( vector<string>& communityDeck )
{
	char c = ' ';
	int  cardNumber = 0;

	if ( !game.IsFlop() )
	{
		for (int i = 0; i < HOLE_CARDS; i++)
		{
			this->suitsInHand.push_back( this->playerHand.at(i).at(2) );
			c = this->playerHand.at( i ).at( 0 );

			cardNumber = game.ConvertCharToInt( c );
			this->numsInHand.push_back( cardNumber );
		}
	}
	else if ( game.IsFlop() && !game.IsTurn() )
	{
		for (int i = 0; i < FLOP_SIZE; i++)
		{
			this->suitsInCommunity.push_back( communityDeck.at(i).at(2) );
			c = communityDeck.at( i ).at( 0 );

			cardNumber = game.ConvertCharToInt( c );
			this->numsInCommunity.push_back( cardNumber );
		}
	}
	else if ( game.IsTurn() && !game.IsRiver() )
	{
		this->suitsInCommunity.push_back( communityDeck.at(3).at(2) );
		c = communityDeck.at( 3 ).at( 0 );

		cardNumber = game.ConvertCharToInt( c );
		this->numsInCommunity.push_back( cardNumber );
	}
	else
	{
		this->suitsInCommunity.push_back( communityDeck.at(4).at(2) );
		c = communityDeck.at( 4 ).at( 0 );

		cardNumber = game.ConvertCharToInt( c );
		this->numsInCommunity.push_back( cardNumber );
	}
}

int AI::FindHighCard( )
{
	int highCard = 0;

	if ( this->numsInCommunity.size() == 0 )
	{
		if ( this->numsInHand.at(0) >= this->numsInHand.at(1) )
		{
			highCard = this->numsInHand.at(0);
		}
		else
		{
			highCard = this->numsInHand.at(1);
		}
	}
	else if ( this->numsInCommunity.size() > 0 )
	{
		for ( int i = 0; i < this->numsInHand.size(); i++)
		{
			for ( int j = 0; j < this->numsInCommunity.size(); j++)
			{
				if ( this->numsInHand.at(i) >= this->numsInCommunity.at(j) )
				{
					highCard = this->numsInHand.at(i);
				}
				else
				{
					for (int k = 0; k < this->numsInCommunity.size(); k++)
					{
						if ( this->numsInCommunity.at(k) > highCard )
						{
							highCard = this->numsInCommunity.at(k);
						}
					}
				}
			}
		}

		return highCard;
	}
}

void AI::Determine( )
{
	srand( time(NULL) );

	if ( (int)this->currentRiskFactor % 2 != 0 )
	{
		this->risky = true;
	}

	int	howRisky = rand( ) % 25; //Used for risky moves

	// double decisionFactor = 0.0;

	if ( !game.IsFlop() )
	{
		if (this->risky)
		{
			if ( game.GetLastAction( ) == CALL  ||
				 game.GetLastAction( ) == BET   ||
				 game.GetLastAction( ) == RAISE || 
				 game.GetLastAction( ) == FOLD )
			{
				if (howRisky >= 12)
				{
					this->AI_Raise( );
					return;
				}
				else
				{
					this->AI_Call( );
					return;
				}
			}
			else if ( game.GetLastAction( ) == CHECK )
			{
				this->AI_Bet( );
				return;
			}
		}
		else
		{
			if (currentRiskFactor >= 98)
			{
				if ( game.GetLastAction( ) != CHECK )
				{
					this->AI_Fold( );
					return;
				}
				else
				{
					this->AI_Check( );
					return;
				}
			}
			else if (currentRiskFactor >= 90)
			{
				if ( game.GetLastAction( ) == CALL  ||
					 game.GetLastAction( ) == RAISE ||
					 game.GetLastAction( ) == FOLD  ||
					 game.GetLastAction( ) == BET)
				{
					if ( game.GetCurrentBet( ) > this->money * 0.7f && howRisky < 12 )
					{
						this->AI_Fold( );
						return;
					}
					else
					{
						this->AI_Call( );
						return;
					}
				}
				else if ( game.GetLastAction( ) == CHECK )
				{
						this->AI_Check( );
						return;
				}
			}
			else if (currentRiskFactor < 90)
			{
				if (currentRiskFactor > 80 && game.GetLastAction( ) == CALL  ||
											  game.GetLastAction( ) == RAISE ||
											  game.GetLastAction( ) == FOLD  ||
											  game.GetLastAction( ) == BET )
				{
					this->AI_Call( );
					return;
				}
				else
				{
					if ( game.GetLastAction( ) == CHECK )
					{
						this->AI_Bet( );
						return;
					}
					else
					{
						this->AI_Raise( );
						return;
					}
				}
			}
		}
	}
}

void AI::AI_TurnAction( void )
{
	ExtractCardData( game.ReturnDealerObject()->GetCommunityDeck() );
	Compare( );
	Determine( );

	cout << "Current Hand: " << this->playerHand.at( 0 ) << " " << this->playerHand.at( 1 ) << endl;
	cout << "Current High Card: " << this->FindHighCard( ) << endl;
	cout << "Current Risk Factor: " << this->currentRiskFactor;

	cin.ignore( );
	cin.get( );
}

void AI::AI_Check( )
{
	game.SetLastAction( CHECK );
	return;
}

void AI::AI_Call( )
{
	cout << this->playerName << " calls!" << endl;
	game.SetLastAction( CALL );
}

void AI::AI_Bet( )
{
	cout << this->playerName << " bets!" << endl;
	game.SetLastAction( BET );
}

void AI::AI_Raise( )
{
	cout << this->playerName << " raises!" << endl;
	game.SetLastAction( RAISE );
}

void AI::AI_Fold( )
{
	cout << this->playerName << " folds!" << endl;
	game.SetLastAction( FOLD );
}


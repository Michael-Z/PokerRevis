#include <algorithm>

#include "vars.h"

Dealer::Dealer( void )
{
	this->FillDeck( );
	this->deckPos = this->deck.size( ) - 1;
	this->communityDeck.push_back( " " );
	this->communityDeck.push_back( " " );
	this->communityDeck.push_back( " " );
	this->communityDeck.push_back( " " );
	this->communityDeck.push_back( " " );

}

Dealer::~Dealer( void )
{
}

void Dealer::FillDeck( void )
{
	deck.clear( );

	deck.push_back( "A-H" );
	deck.push_back( "A-S" );
	deck.push_back( "A-C" );
	deck.push_back( "A-D" );

	deck.push_back( "2-H" );
	deck.push_back( "2-S" );
	deck.push_back( "2-C" );
	deck.push_back( "2-D" );

	deck.push_back( "3-H" );
	deck.push_back( "3-S" );
	deck.push_back( "3-C" );
	deck.push_back( "3-D" );

	deck.push_back( "4-H" );
	deck.push_back( "4-S" );
	deck.push_back( "4-C" );
	deck.push_back( "4-D" );

	deck.push_back( "5-H" );
	deck.push_back( "5-S" );
	deck.push_back( "5-C" );
	deck.push_back( "5-D" );

	deck.push_back( "6-H" );
	deck.push_back( "6-S" );
	deck.push_back( "6-C" );
	deck.push_back( "6-D" );

	deck.push_back( "7-H" );
	deck.push_back( "7-S" );
	deck.push_back( "7-C" );
	deck.push_back( "7-D" );

	deck.push_back( "8-H" );
	deck.push_back( "8-S" );
	deck.push_back( "8-C" );
	deck.push_back( "8-D" );

	deck.push_back( "9-H" );
	deck.push_back( "9-S" );
	deck.push_back( "9-C" );
	deck.push_back( "9-D" );

	deck.push_back( "10-H" );
	deck.push_back( "10-S" );
	deck.push_back( "10-C" );
	deck.push_back( "10-D" );

	deck.push_back( "J-H" );
	deck.push_back( "J-S" );
	deck.push_back( "J-C" );
	deck.push_back( "J-D" );

	deck.push_back( "Q-H" );
	deck.push_back( "Q-S" );
	deck.push_back( "Q-C" );
	deck.push_back( "Q-D" );

	deck.push_back( "K-H" );
	deck.push_back( "K-S" );
	deck.push_back( "K-C" );
	deck.push_back( "K-D" );
}

void Dealer::Shuffle( void )
{
	srand( time(NULL) );
	random_shuffle( deck.begin( ), deck.end( ) );
}

void Dealer::Deal( void )
{
	// If we haven't had the flop, check for
	// current player and deal their hand.
	if ( !game.IsFlop() )
	{
		while ( game.GetCurrentPlayer() != FINISHED )
		{
			switch ( game.GetCurrentPlayer() )
			{
			case PLAYER:
				this->DealToPlayer( );
				game.ChangeCurrentPlayer( CPU1 );
				break;

			case CPU1:
				this->DealToAI( game.ReturnAIObject(CPU1) );
				game.ChangeCurrentPlayer( CPU2 );
				break;

			case CPU2:
				this->DealToAI( game.ReturnAIObject(CPU2) );
				game.ChangeCurrentPlayer( CPU3 );
				break;

			case CPU3:
				this->DealToAI( game.ReturnAIObject(CPU3) );
				game.ChangeCurrentPlayer( CPU4 );
				break;

			case CPU4:
				this->DealToAI( game.ReturnAIObject(CPU4) );
				game.ChangeCurrentPlayer( FINISHED );
				break;
			}
		}
	}
	else if ( !game.IsBettingRound() )
	{
		this->DealToCommunity( );
	}
}

void Dealer::DealToPlayer( void )
{
	for (int handPos = 0; handPos < HOLE_CARDS; handPos++)
	{	
		string card = this->deck.at( deckPos );
		game.ReturnPlayerObject( )->SetPlayerHand( card, handPos );
		this->deck.pop_back( );
		this->deckPos--;
	}
}

void Dealer::DealToAI( AI* ai )
{
	for (int handPos = 0; handPos < HOLE_CARDS; handPos++)
	{	
		string card = this->deck.at( deckPos );
		ai->SetPlayerHand( card, handPos );
		this->deck.pop_back( );
		this->deckPos--;
	}
}

void Dealer::DealToCommunity( void )
{
	string card = " ";

	if ( !game.IsFlop() )
	{
		for (int comDeckPos = 0; comDeckPos < FLOP_SIZE; comDeckPos++)
		{
			card = this->deck.at( this->deckPos );
			this->communityDeck.at( comDeckPos ) = card;
			this->deck.pop_back( );
			this->deckPos--;
		}
		
		game.SetFlop( true );
	}
	else if ( game.IsFlop() && !game.IsTurn() )
	{
		card = this->deck.at( this->deckPos );
		this->communityDeck.at( 3 ) = card;
		this->deck.pop_back( );
		this->deckPos--;

		game.SetTurn( true );
	}
	else if ( game.IsFlop() && game.IsTurn() && !game.IsRiver() )
	{
		card = this->deck.at( this->deckPos );
		this->communityDeck.at( 4 ) = card;
		this->deck.pop_back( );
		this->deckPos--;

		game.SetRiver( true );
	}

	cin.get( );
}

int Dealer::GetDeckPos( void )
{
	return this->deckPos;
}

string Dealer::GetCommunityCard( int communityDeckPos )
{
	if ( game.IsFlop() )
	{
		switch (communityDeckPos)
		{
		case 1:
			return this->communityDeck.at( 0 );
			break;

		case 2:
			return this->communityDeck.at( 1 );
			break;

		case 3:
			return this->communityDeck.at( 2 );
			break;

		case 4:
			if ( game.IsTurn() )
			{
				return this->communityDeck.at( 3 );
			}
			break;

		case 5:
			if( game.IsRiver() )
			{
				return this->communityDeck.at( 4 );
			}
			break;
		}
	}
}

vector<string>& Dealer::GetCommunityDeck( )
{
	return this->communityDeck;
}
#ifndef DEALER_H_
#define DEALER_H_

class AI;

class Dealer
{
public:
	Dealer( void );
	~Dealer( void );

	void	FillDeck( void );
	void	Shuffle( void );
	void	Deal( void );

	void	DealToPlayer( void );
	void	DealToAI( AI* ai );
	void	DealToCommunity( void );

	int		GetDeckPos( );
	string	GetCommunityCard( int communityDeckPos );
	
	vector<string>&  GetCommunityDeck( );

protected:
private:
	int		deckPos;

	vector<string> deck;
	vector<string> usedDeck;
	vector<string> communityDeck;
};

#endif
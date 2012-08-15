#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	Player( );
	~Player( );

	void	Check( );
	void	Call( );
	void	Bet( );
	void	Raise( );
	void	Fold( );

	void	SetPlayerHand( string card, int handPos );
	string	GetPlayerCard( int handPos );
	void	ShowPlayerHand( );
	void	SetPlayerName( string playerName );
	string  GetPlayerName( );
	int	    GetPlayerMoney( );

	int		GetInputFromPlayer( );

	void	TurnAction( );
	void	SetTurn( bool turnState );
	bool	IsTurn( );

protected:
	vector<string> playerHand;

	bool	playState;
	bool	turnState;
	string	playerName;
	long	money;

private:
};

class AI : public Player
{
public:
	AI( );
	~AI( );

	void	AI_TurnAction( );
	void    Compare( );
	void	Determine( );
	void    ExtractCardData( vector<string>& communityDeck );
	int		FindHighCard( );

	void	AI_Check( );
	void	AI_Call( );
	void	AI_Bet( );
	void	AI_Raise( );
	void	AI_Fold( );

protected:
private:
	vector<char> suitsInHand;
	vector<int>  numsInHand;

	vector<char> suitsInCommunity;
	vector<int>  numsInCommunity;

	double		 currentRiskFactor;
	bool		 risky;
	bool		 bluffing;
};

#endif
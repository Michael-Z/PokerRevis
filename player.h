#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	Player();
	~Player();

	void	Check();
	void	Call();
	void	Bet();
	void	Raise();
	void	Fold();

	void	SetHand(string card, int handPos);
	string	GetCard(int handPos);
	void	ShowHand();
	void	ShowInfo();
	void	SetName(string name);
	string  ShowName();
	void	ShowMoney();
	void	ShowMoney(int cpu);
	void    SetMoney(int amount);

	int		GetInputFromPlayer();

	void	TurnAction();
	void	SetTurn(bool state);
	bool	IsTurn();

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
	AI();
	~AI();

	void	AI_TurnAction();
	void    Compare();
	void	Determine();
	void    ExtractCardData(vector<string>& communityDeck);
	int		FindHighCard();
	void	AI_ShowCardsHidden();

	void	AI_Check();
	void	AI_Call();
	void	AI_Bet();
	void	AI_Raise();
	void	AI_Fold();

protected:
private:
	vector<char> suitsInHand;
	vector<int>  numsInHand;

	vector<char> suitsInCommunity;
	vector<int>  numsInCommunity;

	double		 currentRiskFactor;
	int			 highCard;
	bool		 risky;
	bool		 bluffing;
};

#endif
#ifndef ROUND_H_
#define ROUND_H_

#include "player.h"
#include "dealer.h"

class Game
{
public:
	Game();
	~Game();

	void	CleanUp();

	void	Interface();
	void	UpdateInterface();
	
	Player* ReturnPlayerObject();
	Dealer* ReturnDealerObject();
	AI*	    ReturnAIObject(int cpuNum);

	void	Init();
	void	Start();
	void	End();

	bool	IsFlop();
	bool	IsTurn();
	bool	IsRiver();
	bool    IsBettingRound();
	void	SetFlop(bool isFlop);
	void	SetTurn(bool isTurn);
	void	SetRiver(bool isRiver);
	void    SetBettingRound(bool isBettingRound);

	int		GetCurrentPlayer();
	void	ChangeCurrentPlayer(unsigned short nextPlayer);
	int		GetLastAction();
	void	SetLastAction(int action);
	long	GetCurrentBet();
	void	SetCurrentBet(int amount);
	long	GetCurrentPot();
	void	SetCurrentPot(int amount);

	int		ConvertCharToInt(char c);

protected:
private:
	int			   currentPlayer;
	int			   lastAction;
	int			   playersLeft;
	long		   currentBet;
	long		   currentPot;
	bool		   endOfRound;
	bool		   endOfGame;
	bool		   flop;
	bool		   turn;
	bool		   river;
	bool		   bettingRound;

	Player*		   player;
	Dealer*		   dealer;
	AI*			   cpu1;
	AI*			   cpu2;
	AI*			   cpu3;
	AI*			   cpu4;

	std::vector<AI*> cpu;
};

#endif
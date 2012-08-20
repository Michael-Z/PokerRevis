#ifndef DEALER_H_
#define DEALER_H_

class AI;

class Dealer
{
public:
	Dealer();
	~Dealer();

	void	FillDeck();
	void	Shuffle();
	void	Deal();
	void	ShowCommunityCards();

	void	DealToPlayer();
	void	DealToAI(AI* ai);
	void	DealToCommunity();

	int		GetDeckPos();
	string	GetCommunityCard(int communityDeckPos);
	
	vector<string>&  GetCommunityDeck();

protected:
private:
	int		deckPos;

	vector<string> deck;
	vector<string> usedDeck;
	vector<string> communityDeck;
};

#endif
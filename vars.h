#ifndef VARS_H_
#define VARS_H_

#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

#include "round.h"

extern Game  game;

enum PLAYERS
{
	CPU1,
	CPU2,
	CPU3,
	CPU4,
	PLAYER,
	FINISHED
};

enum PLAY_CHOICES
{
	CHECK = 1,
	CALL,
	BET,
	RAISE,
	FOLD
};

enum HAND_TYPES
{
	HIGH,
	ONE_PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH
};

enum CARD_ROYALTY
{
	JACK = 11,
	QUEEN,
	KING,
	ACE
};

extern const unsigned short HOLE_CARDS;
extern const unsigned short FLOP_SIZE;
	
const double numberMatchBonus = 20.0;
const double suitMatchBonus = 2.0;

#endif
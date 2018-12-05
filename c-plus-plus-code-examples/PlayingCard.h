#ifndef PLAYING_CARD
#define PLAYING_CARD

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "Card.h"


const char CHAR_ACE = 'A';
const char CHAR_JOKER = 'J';
const char CHAR_QUEEN = 'Q';
const char CHAR_KING = 'K';

using namespace std;

class PlayingCard : public Card{

	private:
	
	string itostr (int value);
	
	public:

	// Extraction operator overload
	friend ostream& operator << (ostream& output, 
							     PlayingCard& newPlayingCard);

	
	
	// Default Constructor
	PlayingCard(void);
	
	// Constructor
	PlayingCard(int newNumber, 
				string newSuit);
	
	// Constructor
	PlayingCard(string newNumber,
				string newSuit);

	// Copy Constructor
	PlayingCard(const PlayingCard& newPlayingCard);

	// **** Get Methods ****
	
	int getNumber();
	
	void getNumber(string& newNumber);
	
	string get_card(void);
	
	// **** Set Methods ****
	
	void setNumber(int newNumber);
	
	void setNumber(string newNumber);

	~PlayingCard(void);

};

#endif
 

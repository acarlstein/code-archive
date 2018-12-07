/**
 * Card.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */

#include "Card.h"

//////////////////////////////////////////////////////////////////////////////
//**** OVERLOAD OPERATORS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * operator ==
 * @description: Compare two cards by their number
 * @param: in, Card1, Card2
 * @return: istream&
 */
bool operator == (const Card& Card1, 
				  const Card& Card2){
     return  (Card1.number == Card2.number);
}

/**
 * operator !=
 * @description: Compare two cards by their number
 * @param: in, Card1, Card2
 * @return: istream&
 */
bool operator != (const Card& Card1, 
				  const Card& Card2){
     return  (Card1.number != Card2.number);
}

/**
 * operator <=
 * @description: Compare two cards by their number
 * @param: in, Card
 * @return: istream&
 */
bool operator <= (const Card& Card1,
				  const Card& Card2){
     return  (Card1.number <= Card2.number);
}

/**
 * operator >=
 * @description: Compare two cards by their number
 * @param: in, Card1, Card2
 * @return: istream&
 */
bool operator >= (const Card& Card1, 
				  const Card& Card2){
     return  (Card1.number >= Card2.number);
}

/**
 * operator <
 * @description: Compare two cards by their number
 * @param: in, Card1, Card2
 * @return: istream&
 */
bool operator < (const Card& Card1, 
				 const Card& Card2){
	return (Card1.number < Card2.number);
}

/**
 * operator >
 * @description: Compare two cards by their number.
 * @param: in, Card1, Card2
 * @return: istream&
 */
bool operator > (const Card& Card1, 
				 const Card& Card2){
	return (Card1.number > Card2.number);
}

///////////////////////////////////////////////////////////////////////////////
//**** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//**** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

// Default Constructor
Card::Card(void){
	number = 0;
	suit = "";
}
		
// Constructor
Card::Card(int newNumber, 
			 string newSuit){		 
	number = newNumber;
	suit = newSuit;
}
		
// Copy Constructor
Card::Card(const Card& newCard){
	number = newCard.number;
	suit = newCard.suit;
}

// **** Set Methods ****			 

int Card::getNumber(void){
	return number;
}
		
string Card::getSuit(void){
	return suit;
}
		
void Card::get(int& newNumber, 
			   string& newSuit){
	newNumber = number;
	newSuit = suit;
}
		

// **** Set Methods ****
	
void Card::setNumber(int newNumber){
	number = newNumber;
}
		
void Card::setSuit(string newSuit){
	suit = newSuit;
}
		
void Card::set(int newNumber, 
  			   string newSuit){
	number = newNumber;
	suit = newSuit;
}
		
Card::~Card(void){

}






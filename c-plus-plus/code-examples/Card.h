#ifndef CARD
#define CARD

#include <iostream>
#include <string>

using namespace std;

/**
 * class Card
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */
class Card{

	// Compare two cards by their number
	friend bool operator == (const Card& Card1, 
							 const Card& Card2);	

	// Compare two cards by their number
	friend bool operator != (const Card& Card1, 
							 const Card& Card2);	

	// Compare two cards by their number
	friend bool operator <= (const Card& Card1, 
							 const Card& Card2);	

	// Compare two cards by their number
	friend bool operator >= (const Card& Card1, 
							 const Card& Card2);	

	// Compare two cards by their number
	friend bool operator < (const Card& Card1, 
							const Card& Card2);

	// Compare two cards by their number
	friend bool operator > (const Card& Card1, 
							const Card& Card2);	

	protected:

		int number;
	
		string suit;	
	
	public:
	
		// Default Constructor
		Card(void);
		
		// Constructor
		Card(int newNumber, 
			 string newSuit);
		
		// Copy Constructor
		Card(const Card& newCard);

		// **** Set Methods ****			 

		int getNumber(void);
		
		string getSuit(void);
		
		void get(int& newNumber, string& newSuit);
		

		// **** Set Methods ****
	
		void setNumber(int newNumber);
		
		void setSuit(string newSuit);
		
		void set(int newNumber, 
				 string newSuit);
		
		~Card(void);

};

#endif
 

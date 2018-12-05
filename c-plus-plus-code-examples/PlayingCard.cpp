/**
 * PlayingCard.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */

#include "PlayingCard.h"


//////////////////////////////////////////////////////////////////////////////
//**** OVERLOAD OPERATORS ****
///////////////////////////////////////////////////////////////////////////////
/**
 * operator <<
 * @description: Extraction operator overloaded 
 * @param: out, team
 * @return: ostream&
 */
ostream& operator << (ostream& output, 
					  PlayingCard& newPlayingCard) {		
		
	output << newPlayingCard.get_card();
	
	return output;	
}

///////////////////////////////////////////////////////////////////////////////
//**** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * itostr
 * @description: Convert an integer value to string
 * @param: value
 * @return: string
 */
string PlayingCard::itostr (int value){	
	stringstream ss_tmp;
	
	ss_tmp << value;
	
	return ss_tmp.str();
}

///////////////////////////////////////////////////////////////////////////////
//**** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////
/**
 * PlayingCard
 * @description: Defaul constructor
 */
PlayingCard::PlayingCard(void){

}

/**
 * PlayingCard
 * @description: Constructor
 * @param: newNumber, newSuit
 */
PlayingCard::PlayingCard(int newNumber, 
						 string newSuit):
		  				 Card(newNumber, 
		  				 	  newSuit){
}

/**
 * PlayingCard
 * @description: Constructor
 * @param: newNumber, newSuit
 */
PlayingCard::PlayingCard(string newNumber, 
						 string newSuit){
	setNumber(newNumber);
	suit = newSuit;		 
}

/**
 * PlayingCard
 * @description: Copy Constructor
 * @param: newPlayingCard
 */				
PlayingCard::PlayingCard(const PlayingCard& newPlayingCard):
						Card(newPlayingCard){					
}

// **** Get Methods ****

int PlayingCard::getNumber(){
	return number;
}

void PlayingCard::getNumber(string& newNumber){
	
	switch(number){
		case 14:
			newNumber = CHAR_ACE;
			break;
		case 13:
			newNumber = CHAR_JOKER;
			break;
		case 12:
			newNumber = CHAR_QUEEN;
			break;
		case 11:
			newNumber = CHAR_KING;
			break;
		default:
			newNumber = itostr(number);
	}		

}

string PlayingCard::get_card(void){

	string strNumber = "";

	getNumber(strNumber);
	
	return strNumber + getSuit();

}

// **** Set Methods ****
void PlayingCard::setNumber(int newNumber){
	number = newNumber;
}

void PlayingCard::setNumber(string newNumber){
	
	int tmpNumber;

	char c = (char)newNumber[0];		

	tmpNumber = (int)c;

 	switch(tmpNumber){
	 	case CHAR_ACE:
			number = 14;
			break;
		case CHAR_KING:
			number = 13;
			break;
		case CHAR_QUEEN:
			number = 12;
			break;
		case CHAR_JOKER:
			number = 11;
			break;
		default:			
			number = atoi(newNumber.c_str());
	}

}

/**
 * ~PlayingCard
 * @description: Destructor 
 */
PlayingCard::~PlayingCard(void){

}

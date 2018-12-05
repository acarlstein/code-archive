/**
 * Card.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */

#include "Player.h"

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
					  Player& newPlayer) {		
		
	output << newPlayer.name;
	
	return output;	
}

/**
 * operator =
 * @description: deep copy player
 * @param: newPlayer
 * @return: Player&
 */
Player& Player::operator= (const Player& newPlayer)
{
	
	copy_player(newPlayer);
	
    // return the existing object
    return *this;
}


///////////////////////////////////////////////////////////////////////////////
//**** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * copy_player
 * @description: Deep copyExtraction operator overloaded 
 * @param: newPlayer
 */
void Player::copy_player(const Player& newPlayer){
		
	number_of_battles = newPlayer.number_of_battles;
	
	number_of_wars = newPlayer.number_of_wars;
		
	number_of_battles_won = newPlayer.number_of_battles_won;
		
	number_of_wars_won = newPlayer.number_of_wars_won;
	
	number_of_games = newPlayer.number_of_games;
	
	number_of_games_won = newPlayer.number_of_games_won;
	
	comeback_number = newPlayer.comeback_number;

	name = newPlayer.name;
}

/**
 * init
 * @description: Initialized class private variables
 */
void Player::init(void){
	
	number_of_battles = 0;
		
	number_of_battles_won = 0;
		
	number_of_wars = 0;
		
	number_of_wars_won = 0;
		
	number_of_games_won = 0;
		
	number_of_games = 0;
	
	comeback_number = 0;

	name = "";

}

///////////////////////////////////////////////////////////////////////////////
//**** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * Player
 * @description:  Default constructor
 */
Player::Player(void){
	
	init();
	
}

/**
 * Player
 * @description:  Constructor
 * @param: newName
 */
Player::Player(string newName){
	
	init();

	name = newName;

}
	   		   

/**
 * Player
 * @description:  Copy constructor
 * @param: newPlayer
 */
Player::Player(const Player& newPlayer){
			   	
	copy_player(newPlayer);
		
}


// **** Get Methods ****			 

int Player::get_battles(void){
	return number_of_battles;
}

int Player::get_battles_won(void){
	return number_of_battles_won;
}
		
int Player::get_wars(void){
	return number_of_wars;
}		
int Player::get_wars_won(void){
	return number_of_wars_won;
}
		
int Player::get_games(void){
	return number_of_games;
}

int Player::get_games_won(void){
	return number_of_games_won;
}

int Player::get_comeback(void){
	return comeback_number;
}
			
string Player::get_name(void){
	return name;
}

PlayingCard Player::get_front_card(void){
	return cardDeck.front();	
}

PlayingCard Player::get_back_card(void){	
	return cardDeck.back();
}
	
PlayingCard Player::get_random_card(void){	
	return cardDeck.at(rand() % cardDeck.size());;
}
	
int Player::get_number_cards(void){
	return (int)cardDeck.size();
}
	
bool Player::is_empty(void){
	return (cardDeck.size() < 1);
}		

// **** Set Methods ****			 

void Player::set_battles_won(int number){
	number_of_battles_won = number;
}
		
void Player::set_wars_won(int number){
	number_of_wars_won = number;
}

void Player::set_battles(int number){
	number_of_battles = number;
}

void Player::set_wars(int number){
	number_of_wars = number;
}

void Player::set_games_won(int number){
	number_of_games_won = number;
}
		
void Player::set_games(int number){
	number_of_games = number;
}
	
void Player::set_comeback(int number){
	comeback_number = number;
}
	
// **** Display Methods ****
			 

// **** Methods ****	
		 
void Player::inc_battles_won_by(int number){
	number_of_battles_won += number;
}

void Player::inc_wars_won_by(int number){
	number_of_wars_won += number;
}
		
void Player::inc_battles_by(int number){
	number_of_battles += number;
}

void Player::inc_wars_by(int number){
	number_of_wars += number;
}

void Player::inc_games_won_by(int number){
	number_of_games_won += number;
}

void Player::inc_games_by(int number){
	number_of_games += number;
}

/**
 * push_front_card
 * @description:  Push a new card at the front of the player's deck of cards
 * @param:  newCard
 */
void Player::push_front_card(PlayingCard newCard){
	cardDeck.push_front(newCard);
}

/**
 *  push_back_card
 * @description:  Push new card at the back of the player's deck of cards
 * @param: newCard
 */
void Player::push_back_card(PlayingCard newCard){
	cardDeck.push_back(newCard);
}

/**
 *  push_random_card
 * @description:  push a card in a random position of the player's card deck of cards
 * @param: newCard
 */
void Player::push_random_card(PlayingCard newCard){

	if (cardDeck.empty()){
		
		cardDeck.insert(cardDeck.begin(), newCard);
	
	} else {
		
		int rndPos = rand() % cardDeck.size();
				
		deque<PlayingCard>::iterator it = cardDeck.begin();
	
		it += rndPos;
		
		cardDeck.insert(it, newCard);
	}
}

/**
 * pop_front_card
 * @description:  Pop and return the front card from the player's deck of cards
 * @return: PlayingCard
 */
PlayingCard Player::pop_front_card(void){

	PlayingCard rtnCard = cardDeck.front();
	
	cardDeck.pop_front();
	
	return rtnCard;
	
}
/**
 * pop_back_card
 * @description:  Pop and return the back card from the player's deck of cards
 * @return: PlayingCard
 */
PlayingCard Player::pop_back_card(void){

	PlayingCard rtnCard = cardDeck.back();	
	
	cardDeck.pop_back();
	
	return rtnCard;
}

/**
 * pop_random_card
 * @description:  Pop and return a random card from the player's deck of cards
 * @return: PlayingCard
 */	
PlayingCard Player::pop_random_card(void){

	PlayingCard rtnCard;	

	unsigned int rndPos = rand() % cardDeck.size();
	
	rtnCard = cardDeck.at(rndPos);
		
	cardDeck.erase(cardDeck.begin() + rndPos);
	
	return rtnCard;

}
		
/**
 * shuffle_cards
 * @description:  Shuffle player's deck of cards
 */
void Player::shuffle_cards(void){
	random_shuffle(cardDeck.begin(), cardDeck.end());	
}

/**
 * empty 
 * @description:  remove all card from player's deck of cards
 */
void Player::empty(void){
	cardDeck.clear();
}

/**
 * ~Player
 * @description: Destructor
 */
Player::~Player(void){

}

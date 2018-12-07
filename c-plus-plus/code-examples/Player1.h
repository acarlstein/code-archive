#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

#include "PlayingCard.h"

using namespace std;

/**
 * class Card
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */
class Player{
								 
	private:
	
		deque<PlayingCard> cardDeck;
	
		int number_of_battles;
		
		int number_of_battles_won;
		
		int number_of_wars;
		
		int number_of_wars_won;
		
		int number_of_games;
		
		int number_of_games_won;
		
		int comeback_number;

		string name;
		
		void init(void);
		
		void copy_player(const Player& newPlayer);
	
	public:
	
		// Extraction operator overload
		friend ostream& operator << (ostream& output, 
									 Player& newPlayer);
	
		Player& operator= (const Player &newPlayer);

		// Default Constructor
		Player(void);
	
		// Constructor
		Player(string newName);
				   				   
		// Copy Constructor
		Player(const Player& newPlayer);
	
		// **** Get Methods ****			 

		int get_battles(void);
		
		int get_battles_won(void);

		int get_wars(void);
				
		int get_wars_won(void);
		
		int get_games(void);
		
		int get_games_won(void);
		
		int get_comeback(void);
			
		string get_name(void);
		
		PlayingCard get_front_card(void);
	
		PlayingCard get_back_card(void);
	
		PlayingCard get_random_card(void);	
	
		int get_number_cards(void);

		bool is_empty(void);
					
		// **** Set Methods ****			 
	
		void set_battles(int number);

		void set_battles_won(int number);
		
		void set_wars(int number);

		void set_wars_won(int number);	
			
		void set_games_won(int number);
		
		void set_games(int number);
	
		void set_comeback(int number);
		
		void push_front_card(PlayingCard newCard);
	
		void push_back_card(PlayingCard newCard);
	
		void push_random_card(PlayingCard newCard);

		PlayingCard pop_front_card(void);
	
		PlayingCard pop_back_card(void);
	
		PlayingCard pop_random_card(void);	
		
		void shuffle_cards(void);
	
		void empty(void);

		// **** Display Methods ****
		
		// **** Methods ****
		
		void inc_battles_by(int number);

		void inc_battles_won_by(int number);		

		void inc_wars_by(int number);
		
		void inc_wars_won_by(int number);
		
		void inc_games_by(int number);
		
		void inc_games_won_by(int number);

		// Destructor
		~Player(void);

};


#endif
 

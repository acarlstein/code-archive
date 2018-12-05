#ifndef WAR_MACHINE
#define WAR_MACHINE

#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "Player.h"
#include "PlayingCard.h"

using namespace std;

/**
 * class Card
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */
class WarMachine{

	private:
	
	static const int MAX_CARDS = 52;
	
	int total_number_of_cards;
	
	int tournament_battles;
	
	int tournament_wars;
	
	int tournament_games;
	
	int largest_battles;
	
	deque<Player> players;
	
	Player winner;
	
	Player biggest_comeback;
	
	deque<PlayingCard> get_new_cards(void);
	
	bool deal_cards(deque<Player>& newPlayers);

	void play_war(deque<Player>& newPlayers, 
				  deque<PlayingCard>& newBoard,
				  int& number_wars);
	
	Player recursive_battle(deque<Player> newPlayers);
	
	deque<string> log;
	
	string itostr (int value);
	
	bool is_power_of_two(int value);
	
	void init(void);

	public:
	
		// **** Constructors ****
		WarMachine(void);
		
		// **** Get Methods ****
		string get_log(void);
		
		// **** Set Methods ****
	
		// **** Display Methods ****
		
		void print_log(ofstream& fout);
	
		void print_statistics(ofstream& fout);
	
		// **** Methods ****	
		void add_player(string name);
		
		void remove_player(void);
		
		bool start(void);
		
		// **** Destructor ****
		~WarMachine(void);
		
};



#endif
 

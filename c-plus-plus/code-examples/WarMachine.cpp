/**
 * WarMachine.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */

#include "WarMachine.h"

//////////////////////////////////////////////////////////////////////////////
//**** OVERLOAD OPERATORS ****
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 *  get_new_cards
 * @description: Create cards deck
 * @return: deque<PlayingCard>
 */
deque<PlayingCard> WarMachine::get_new_cards(void){

	deque<PlayingCard> rtnDeck;
	
	string suits[4];
	
	suits[0] = "D";
	suits[1] = "H";
	suits[2] = "C";
	suits[3] = "S";

	// Create deck with 52 cards
	for (int i = 2; i < 15; i++){

		for(int j = 0; j < 4; j++){
		
			PlayingCard playingCard(i, suits[j]);
					
			rtnDeck.push_front(playingCard);
		}
	}
		
	total_number_of_cards = rtnDeck.size();
	
	biggest_comeback.set_comeback(total_number_of_cards);
	
	return rtnDeck;

}

/**
 * deal_cards
 * @description: Deal cards to players.
 *	 	       Return true if there are not enought card for all players
 * @param: newPlayers
 * @return: bool
 */
bool WarMachine::deal_cards(deque<Player>& newPlayers){

	bool bError = false;
	
	deque<PlayingCard> cardDeck;

	cardDeck = get_new_cards();
	
	random_shuffle(cardDeck.begin(), cardDeck.end());
	
	//cout << "Remove players cards..." << endl;
	
	//Remove all players cards
	for (int i = 0; i < newPlayers.size(); i++)
		newPlayers[i].empty();
	
	//cout << "Check if there areenought cards for players..." << endl;
	if (cardDeck.size() / newPlayers.size() > 1){

		bool isEmpty = false;

		while (!isEmpty)
			for (unsigned int i = 0; i < newPlayers.size(); i++)
				if (cardDeck.size() > 0){
					newPlayers[i].push_random_card(cardDeck.front());
					cardDeck.pop_front();
				}else{
					isEmpty = true;
				}
							
	}else{
		
		cerr << "[X] ERROR: Too many Players, not enough Cards!" << endl;
		
		bError = true;
	}
		
	return bError;
}

/**
 * play_war
 * @description: Play war until two cards are different or any player run out of cards
 * @param: newPlayers, newBoard, number_war
 */
void WarMachine::play_war(deque<Player>& newPlayers, 
						  deque<PlayingCard>& newBoard, 
						  int& number_wars){
					 
	bool different_cards = false;
				
	while (!different_cards && 
		   newPlayers.front().get_number_cards() > 0 && 
		   newPlayers.back().get_number_cards() > 0){
								
		number_wars++;

		tournament_wars ++;
				
		newPlayers.front().inc_wars_by(1);
		newPlayers.back().inc_wars_by(1);
					
		//Take four card from each player if possible
		for (int i = 0; i < 4; i++){
			
			if (newPlayers.front().get_number_cards() > 0)
				newBoard.push_front(newPlayers.front().pop_front_card());
							
			if (newPlayers.back().get_number_cards() > 0)
				newBoard.push_back(newPlayers.back().pop_front_card());
					
		}//for (int i = 0; i < 4; i++)
					
		if (newBoard.front() != newBoard.back()) 
			different_cards = true;
				
	} //while (!different_cards && tmpPlayers[0].size() > 0 && tmpPlayers[1].size() > 0)

}


/**
 * recursive_battle
 * @description: Recursive battle of the tournament
 * @param: newPlayer
 * @return: Player
 */
Player WarMachine::recursive_battle(deque<Player> newPlayers){
	
	Player rtnPlayer;

	if (newPlayers.size() < 2){
		
		rtnPlayer = newPlayers.front();
		
		newPlayers.pop_front();
		
	}else{
	
		tournament_games++;
				
		string str_tmp;
		
		stringstream ss_tmp;
				
		int num_battles = 0;
		
		int num_wars = 0;
		
		deque<Player> tmpPlayers;

		// Take player from newPlayer deque to tmpPlayer deque
		tmpPlayers.push_front(newPlayers.back());
		newPlayers.pop_back();

		// Take player from newPlayer deque to tmpPlayer deque
		tmpPlayers.push_back(newPlayers.back());
		newPlayers.pop_back();			
			
		tmpPlayers.front().inc_games_by(1);
		tmpPlayers.back().inc_games_by(1);
		
		// Display name of combatients 
		// ex: Jane VS. John
		str_tmp = tmpPlayers.front().get_name() +
				  " VS " +
				  tmpPlayers.back().get_name();
		
		log.push_back(str_tmp);
	
		// Give new cards to players
		deal_cards(tmpPlayers);
		
		int lowers[2];

		lowers[0] = tmpPlayers.front().get_number_cards();
		lowers[1] = tmpPlayers.back().get_number_cards();
		
		// Create board that will hold the cards used for the battle
		deque<PlayingCard> board;
		
		bool is_war = false;

		// While any of both players still have cards
		// Keep playing
		while (tmpPlayers.front().get_number_cards() > 0 && 
			   tmpPlayers.back().get_number_cards() > 0){
		   
			tmpPlayers.front().inc_battles_by(1);
			tmpPlayers.back().inc_battles_by(1);
		
			board.push_front(tmpPlayers.front().pop_front_card());
			board.push_back(tmpPlayers.back().pop_front_card());
				
			// If both are the same then WAR!
			if (board.front() == board.back()){
				
				is_war = true;

				play_war(tmpPlayers, board, num_wars);
				
			}else{

				num_battles++;
		
				tournament_battles++;
			
			}//if (board.get_front_card() == board.get_back_card())
			
			int winner;
			
			if (board.front() != board.back()){
				
				//winner should be the players with the greater card
				winner = (board.front() > board.back()) ? 0 : 1;
				
			}else{
				
				// In case that after war the two cards are still the same,
				// The winner is the player that still have cards.
				if (tmpPlayers.front().get_number_cards() > 0){
					winner = 0;
				}else if (tmpPlayers.back().get_number_cards() > 0){
					winner = 1;
				}else{
					cerr << "[X} ERROR: One of both players should not have cards" << endl;
				}//if (tmpPlayers[0].size() > 0)
				
			} //if (board.get_front_card() == board.get_back_card())
			
			int looser = (winner < 1) ? 1 : 0;
						
			// Display if was a regular battle or was a war
			// Also, increase the counter of the winner
			if (is_war){
				
				tmpPlayers[winner].inc_wars_won_by(1);

				str_tmp = "  War " + itostr(num_wars);
				
				is_war = false;
			
			}else{
				
				tmpPlayers[winner].inc_battles_won_by(1);
			
				str_tmp = "  Battle " + itostr(num_battles);

			}//if (is_war)
												
			//Display who is the winner
			str_tmp += ": " + 
					   tmpPlayers[winner].get_name() + 
					   " (" +
					   ( (winner < 1) ? board.front().get_card() : board.back().get_card() ) +
					   ") " +
					   "defeated " +
					   tmpPlayers[looser].get_name() +
					   " (" +
					   ( (winner < 1) ? board.back().get_card() : board.front().get_card() ) +
					   ")"; 

			//Randomize board cards
			random_shuffle(board.begin(), board.end());
			
			// Winner take all cards
			while (board.size() > 0){
				//cout << "Take all cards from board to winner" << endl;
				
				tmpPlayers[winner].push_back_card(board.front());
				
				board.pop_front();
				
			}// while (board.size() > 0)
						
			str_tmp += ": " +
					   tmpPlayers.front().get_name() + 
					   " " +
					   itostr(tmpPlayers.front().get_number_cards()) +
					   ", " +
 					   tmpPlayers.back().get_name() + 
					   " " +
					   itostr(tmpPlayers.back().get_number_cards());
						
			log.push_back(str_tmp);

			lowers[0] = (lowers[0] > tmpPlayers.front().get_number_cards()) ? 
						 tmpPlayers.front().get_number_cards() : lowers[0];
							  
			lowers[1] = (lowers[1] > tmpPlayers.back().get_number_cards()) ? 
						 tmpPlayers.back().get_number_cards() : lowers[1];
			
			
		}//while (tmpPlayers[0].size() > 0 && tmpPlayers[1].size() > 0)
		
		tmpPlayers.front().inc_games_by(1);
		tmpPlayers.back().inc_games_by(1);
		
		int winner = (tmpPlayers.front().get_number_cards() > 
					  tmpPlayers.back().get_number_cards()) ? 0 : 1;
		
		int looser = (winner < 1) ? 1 : 0;
		
		tmpPlayers[winner].inc_games_won_by(1);
		
		tmpPlayers[winner].set_comeback(lowers[winner]);
		
		if (biggest_comeback.get_comeback() > tmpPlayers[winner].get_comeback() ){
			biggest_comeback = tmpPlayers[winner];
		}
		
		//Example: Jane (1) DEFEATED John in 120 Battles and 13 Wars
		str_tmp = "\n" + tmpPlayers[winner].get_name() + 
				  " (" +
				  itostr(tmpPlayers[winner].get_games_won()) +
				  ") DEFEATED " +
				  tmpPlayers[looser].get_name() + 
				  " in " +
				  itostr(num_battles) +
				  " battles and " +
				  itostr(num_wars) +
				  " wars \n";			
				
				
		newPlayers.push_front(tmpPlayers[winner]);
		
		log.push_back(str_tmp);
		
		tmpPlayers.pop_front();
		tmpPlayers.pop_back();
		
		largest_battles = (largest_battles < num_battles) ? num_battles : largest_battles;
		
		rtnPlayer = recursive_battle(newPlayers);

	}//if (newPlayers.size() < 2)
			
	return rtnPlayer;
}

/**
 * itostr
 * @description: Convert an integer value to string
 * @param: value
 * @return: string
 */
string WarMachine::itostr (int value){	

	stringstream ss_tmp;
	
	ss_tmp << value;
	
	return ss_tmp.str();
}

/**
 * is_power_of_two
 * @description:  Indicate if the value is power of two
 * @param: value
 * @return: bool
 */
bool WarMachine::is_power_of_two(int value){
	
	return !(value & (value - 1));
}

/**
 * init
 * @description: Initialized private variables
 */
void WarMachine::init(void){

	total_number_of_cards = MAX_CARDS;
	
	tournament_battles = 0;
	
	tournament_wars = 0;
	
	tournament_games = 0;
	
	largest_battles = 0;
}



///////////////////////////////////////////////////////////////////////////////
//**** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

// **** Constructors ****

/**
 * WarMachine
 * @description: Default Constructor
 */
WarMachine::WarMachine(void){
	init();
}	
		
// **** Get Methods ****	


// **** Set Methods ****

// **** Display Methods ****

/**
 *  print_log 
 * @description: Print tournament log
 * @param: fout
 */
void WarMachine::print_log(ofstream& fout){
	if (log.size() > 0){
		for (unsigned int i = 0; i < log.size(); i++){
			fout << log[i] << endl;
		}
	}else{
		cerr << "[X] ERROR: There is not log related with tournament. Please start the game" << endl;
	}
}


/**
 * print_statistics
 * @description: Print tournament statistics
 * @param: fout
 */
void WarMachine::print_statistics(ofstream& fout){

	fout << "The Winner of the Tournament is: "<< winner.get_name() << endl << endl;
	
	fout << "Number of Players in the tournament: " << players.size() << endl << endl;
	
	fout << "The average number of battles per matchup: " 
		 << ((double)tournament_battles / (double)tournament_games) 
		 << endl << endl;
		
	fout << "The largest number of battles in any one matchup: " << largest_battles << endl << endl;

	fout << "The biggest comeback: " << biggest_comeback.get_name() << endl;
	
	fout << "    Lowest number of cards: " << biggest_comeback.get_comeback() << endl << endl;
	
	fout << "Total number of battles: " << tournament_battles << endl << endl;
	
	fout << "Total number of wars: " << tournament_wars << endl << endl;
	
	fout << "Total number of games: " << tournament_games << endl << endl;

}

// **** Methods ****

/**
 * add_player
 * @description: Add player to the tournament
 * @param: name
 */
void WarMachine::add_player(string name){
	Player player(name);
	players.push_back(player);
}

/**
 * remove_player
 * @description: Remove player from the tournament
 */
 void WarMachine::remove_player(void){
	players.pop_back();
 }
 
/**
 * start
 * @description: Start the game.
 *		        Return true if there are not power of two players for the tournament
 * @return: bool
 */
bool WarMachine::start(void){

	bool rtn_error = false;
		
	if ( is_power_of_two(players.size()) && players.size() > 1){
	
		tournament_battles = 0;
	
		tournament_wars = 0;
	
		tournament_games = 0;

		biggest_comeback.set_comeback(MAX_CARDS);
		
		winner = recursive_battle(players);
			
	}else{
		cerr << "[X] ERROR: Number of players have to be the power of two and more than one player" << endl;
		cerr << " Number of players: " << players.size() << endl;
		rtn_error = true;
	}
	
	return rtn_error;
}


// **** Destructor ****

/**
 *  ~WarMachine
 * @description: Destructor
 */
WarMachine::~WarMachine(void){

}

		
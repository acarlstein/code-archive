/**
 * Hoops.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description: This program will read from files, and store 
 *				 information in memory about all 9 teams in 
 *				 the America East conference, including relevant
 *				 team and player statistics.
 */

#include <iostream>
#include <termios.h>
#include <cstdlib>
#include <string>
#include "Conference.h"
#include "Team.h"
#include "Player.h"
using namespace std;


// Global Variables
enum mainMenu{
	CONFERENCE_MODE,
	PLAYER_MODE,
	TEAM_MODE,
	TEAM_SELECTION_MODE,
	PLAYER_SELECTION_MODE,
	QUIT_PROGRAM,
	RETURN
};		  

//Types

//Prototypes

// Navigate thought modes
int selectMode(int mode, 
			   Conference &conference);

// Display the conference's mode options
void conferenceMode(Conference& conference);

// Display the player's mode options
void playerMode(Conference& conference);

// Display the team's mode options
void teamMode(Conference& conference);

// Display the team selection's mode optinos
void teamSelectionMode(Conference &conference);

// Display the player selection's mode options
void playerSelectionMode(Conference &conference);

// Menu to navigate thought conference mode
int conferenceMenu(Conference &conference);

// Menu to navigate thought player mode
int playerMenu(Conference &conference);

// Menu to navigate thought team mode
int teamMenu(Conference &conference);

// Menu to navigate thought team selection mode
int teamSelectionMenu(Conference &conference);

// Menu to navigate thought player selection mode
int playerSelectionMenu(Conference &conference);

///////////////////////////////////////////////////////////////////////////////

/**
 * Main
 * @description:
 * @param argc, argv
 */
int main(int argc, char* argv[]){
	
	int modeSelected;

	string filename;

	ifstream AmericanEastFile;

	// Create a single Conference Object as AmericaEast
	Conference AmericaEast;

	//Ask for name of file that contains the Conference information
	cout << "Enter file to open: ";

	cin >> filename;

	//Open file for reading
	AmericanEastFile.open(filename.data());	

	if (AmericanEastFile.is_open()){

		// Read all data into America East object 
		// (data is contained Teams Array and each of their respective 
		//  dynamically allocated) Player arrays
		AmericanEastFile >> AmericaEast;

		// Default mode
		modeSelected = CONFERENCE_MODE;

		// Natigate thought modes
		selectMode(modeSelected, AmericaEast);

	}else{
		cerr << endl
			 << "[X] Error: Error opening [" << filename 
			 << "] or File not found!" 
			 << endl;
	}

	// Close file
	AmericanEastFile.close();
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * selectMode
 * @description: Navigate thought modes
 * @param: mode
 * @return: integer
 */
int selectMode(int mode, 
			   Conference &conference){

	switch(mode){

		case CONFERENCE_MODE:
			mode = conferenceMenu(conference);
			break;
		
		case TEAM_MODE:
			mode = teamMenu(conference);
			break;

		case PLAYER_MODE:
			mode = playerMenu(conference);
			break;

		case TEAM_SELECTION_MODE:
			mode = teamSelectionMenu(conference);
			break;

		case PLAYER_SELECTION_MODE:
			mode = playerSelectionMenu(conference);
			break;		

		default:
			cout << endl 
				 << "[X] WRONG MODE: [" << mode << "]  Bye Bye!" 
			     << endl;
			break;

	};

	return mode;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * conferenceMenu
 * @description: Menu to navigate thought conference mode
 * @param: mode
 * @return: integer
 */
int conferenceMenu(Conference &conference){

	int mode;
	bool exit;
	char keystroke;

	mode = -1;

	exit = false;

	while (!exit){

		// Display menu options
		conferenceMode(conference);

		cin >> keystroke;

		switch(keystroke){

			case 't':
				// Display the names of all nine teams, 
				// one per line, in any order
				conference.displayListTeams(cout, false);
				break;

			case 'T':
				// Display all of the information it has, 
				// neatly formatted, about a particular team,
				// except for player information
				conference.displayListTeams(cout, true);
				break;

			case 's':
				// Display the name of the highest scoring 
				// player in the conference
				conference.selectHighestScoringPlayer();
				conference.showHighestScoringPlayer(cout);
				break;				

			case 'S':
				// Display the highest scoring player in the conference
				// then switch to player mode for that player
				conference.selectHighestScoringPlayer();
				conference.showHighestScoringPlayer(cout);
				mode = selectMode(PLAYER_MODE, conference);
				break;
						
			case 'h':
				// Display the name of the tallest player in the conference
				conference.selectTallestPlayer();
				conference.showTallestPlayer(cout);
				break;
	
			case 'H':
				// Display the name of the tallest player in the conference,
				// then switch to player mode for that player
				conference.selectTallestPlayer();
				conference.showTallestPlayer(cout);
				mode = selectMode(PLAYER_MODE, conference);
				break;

			case 'D':
				// Enter to team selection mode
				mode = selectMode(TEAM_SELECTION_MODE, conference);
				break;
				
			case 'F':
				// Enter to team mode with the team set to the team
				// with the most conference wins
				// (if there is a tie, switch to any teamwith the 
				// most conference wins
				cout << endl
					 << "The first place team is: "
					 << conference.getFirstPlaceTeamName()
					 << " ("
//					 << conference.getFirstPlaceTeamConferenceWins()
					 << conference.getFirstPlaceTeamOverallWins()
					 << " wins)"
					 << endl;

				conference.selectFirstPlaceTeam();

				mode = selectMode(TEAM_MODE, conference);
				break;

			case 'Q':
				// Quit program;

				cout << endl
					 << "Go Bearcats!"
					 << endl;

				exit = true;

				break;

			default:
				cout << endl 
					 << "[X] Invalid input, please select from"
					 << "the menu options." 
					 << endl;
				break;
		};
	};

	return mode;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * playerMenu
 * @description: Menu to navigate thought player mode
 * @param: mode
 * @return: integer
 */
int playerMenu(Conference &conference){

	int mode;
	bool exit;
	char keystroke;

	mode = -1;

	exit = false;

	while (!exit){

		// Display menu options
		playerMode(conference);

		cin >> keystroke;

		switch(keystroke){

			case 'I':
				// Display all the information it has about this player								
				conference.displaySelectedPlayerInformation(cout, 
						  	 								SHOW_PLAYER_ALL_DETAILS, 
							 								'\t');
				break;

			case 'S':
				// Print this player's scoring average				
				cout << "Scoring Average: ";				
				conference.displaySelectedPlayerInformation(cout, 
						  	 								SHOW_PLAYER_PPG,
							 								' ');
				break;
							
			case 'R':
				cout << "Rebounding Average: ";
				// Display this player's rebounding average
				conference.displaySelectedPlayerInformation(cout, 
						  	 								SHOW_PLAYER_RPG,
							 								' ');
				break;

			case 'H':
				cout << "Height: ";
				// Display the player's height (in feet-inches format)
				conference.displaySelectedPlayerInformation(cout, 
						  	 								SHOW_PLAYER_HEIGHT,
							 								' ');
				break;

			case 'Q':
				mode = RETURN;

				exit = true;

				break;

			default:
				cout << endl 
					 << "[X] Invalid input, please select from the menu options." 
					 << endl;
				break;
		};
	};

	return mode;
	
}

///////////////////////////////////////////////////////////////////////////////

/**
 * teamMenu
 * @description: Menu to navigate thought team mode
 * @param: mode
 * @return: integer
 */
int teamMenu(Conference &conference){

	int mode;
	bool exit;
	char keystroke;

	mode = -1;

	exit = false;

	while (!exit){

		// Display menu options
		teamMode(conference);

		cin >> keystroke;

		switch(keystroke){

			case 'I':
				// Display all the information it has about this team
				conference.displaySelectedTeam(cout, 
											   SHOW_TEAM_SCHOOL_NAME + 
											   SHOW_TEAM_DETAILS);
										   
				break;

			case 'p':
				// Display the name (only) of all players on this team
				// one per line
				conference.displaySelectedTeam(cout,
											   SHOW_TEAM_PLAYERS_NAME);
				break;

			case 'P':
				// Display all the information the program has,
				// about each player on this team,
				// neatly formatted, one player per line
				conference.displaySelectedTeam(cout,
											   SHOW_TEAM_PLAYERS);
											   					
				break;

			case 'D':
				// Drill down to display information about a 
				// particular player by  entering Player Selection Mode
				mode = selectMode(PLAYER_SELECTION_MODE, conference);

			case 'S':
				// Display all the information it has, neatly formatted,
				// about the highest scoring player on the team
				conference.showHighestScoringPlayer(cout);
				break;

			case 'H':
				// Display all the information it has, neatly formatted,
				// about the tallest player on the team
				conference.showTallestPlayer(cout);
				break;
							
			case 'Q':
				mode = RETURN;
				exit = true;
				break;

			default:
				cout << endl 
					 << "[X] Invalid input, please select from the menu options." 
					 << endl;
				break;
		};
	};

	return mode;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * teamSelectionMenu
 * @description: Menu to navigate thought team selection mode
 * @param: mode
 * @return: integer
 */
int teamSelectionMenu(Conference &conference){

	int mode;
	bool exit;
	char keystroke;
	int ikey;

	mode = -1;

	exit = false;

	while (!exit){

		// Display menu options
		teamSelectionMode(conference);

		cin >> keystroke;
		
		ikey = keystroke - '0';
		
		if (ikey != 0){

			if (ikey > -1 && ikey <= conference.getNumberOfTeams()){

				conference.selectTeamBy(ikey);
		
				mode = selectMode(TEAM_MODE, conference);
			}else{
				cout << endl 
					 << "[X] Invalid input, please select from the menu options." 
					 << endl;			
			}
		}else{
				mode = RETURN;
				exit = true;
		}
	};

	return mode;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * playerSelectionMenu
 * @description: Menu to navigate thought player selection mode
 * @param: mode
 * @return: integer
 */
int playerSelectionMenu(Conference &conference){	

	int mode;
	bool exit;
	int select;
	string str;

	mode = -1;

	exit = false;

	while (!exit){

		// Display menu options
		playerSelectionMode(conference);

		cin >> str;

		// In C++, the keyword switch work with integer values
		select = atoi(str.c_str());

		if (select != 0){
			if (select > -1 && 
				select <= conference.getNumberOfPlayersInSelectedTeam()){

				conference.selectPlayerBy(select);

				mode = selectMode(PLAYER_MODE, conference);

			}else{
				cout << endl 
					 << "[X] Invalid input, please select from the menu options." 
					 << endl;			
			}
		}else{
				mode = RETURN;
				exit = true;
		}


	};

	return mode;
}

///////////////////////////////////////////////////////////////////////////////

/**
 * conferenceMode
 * @description:
 */
void conferenceMode(Conference& conference){

	//TODO
	cout << endl << "[CONFERENCE MENU]" << endl;	

	cout << endl
		 << "t:\t List teams - Names only" << endl	
		 << "T:\t List teams - Detailed view" << endl	
		 << "s:\t Show the name of the highest scoring player in "
		 << "the conference" << endl	
		 << "S:\t Show the name of the highest scoring player in "
		 << "the conference, " << endl
		 << "\t and switch to enter queries about that player" << endl	
		 << "h:\t Show the name of the tallest player in "
		 << "the conference" << endl	
		 << "H:\t Show the name of the tallest player in "
		 << "the conference" << endl	
		 << "\t and switch to enter queries about that player" << endl	
		 << "D:\t Drill down to select and enter queries about " << endl	
		 << "\t a particular team" << endl	
		 << "F:\t Enter queries about the first place team" << endl	
		 << "Q:\t Quit this program " << endl
		 << endl
		 << "Enter the letter corresponding to your choice: ";
}

///////////////////////////////////////////////////////////////////////////////

/**
 * playerMode
 * @description:
 */
void playerMode(Conference& conference){

	//TODO
	cout << endl << "[PLAYER MENU]" << endl;

	cout <<  endl
		 << "I:\t Display detailed player information" << endl
		 << "S:\t Show this player's scoring average" << endl
		 << "R:\t Show this player's rebounding average" << endl
		 << "H:\t Show this player's height" << endl
		 << "Q:\t Quit and return to the previous menu" << endl
		 << endl
	     << "Enter the letter corresponding to your choice: ";
}

/**
 * teamMode
 * @description:
 */
void teamMode(Conference& conference){

	//TODO
	cout << endl << "[TEAM MENU]" << endl;

	cout << endl
		 << "I:\t Display detailed team information" << endl
		 << "p:\t List players - Names only" << endl
		 << "P:\t List players - Detailed view" << endl
		 << "D:\t Drill down to display information about a particular player" 
		 << endl
		 << "S:\t Show the name of the highest scoring player on the team" 
		 << endl
		 << "H:\t Show the name of the tallest player on the team" << endl
		 << "Q:\t Quit and return to the previous menu" << endl 
		 << endl
		 << "Enter the letter corresponding to your choice: ";
}

///////////////////////////////////////////////////////////////////////////////
		
/**
 * teamSelectionMode
 * @description:
 */			
void teamSelectionMode(Conference &conference){

	//TODO
	cout << endl << "[TEAM SELECTION MENU]" << endl;
	
	conference.displayListTeams(cout, false);	

	cout << "0: Quit and return to the previous menu" << endl;
	
	cout << "Enter the letter corresponding to your choice: ";
}

///////////////////////////////////////////////////////////////////////////////

/**
 * playerSelectionMode
 * @description:
 */
void playerSelectionMode(Conference &conference){

	//TODO
	cout << endl << "[PLAYER SELECTION MENU]" << endl;

	conference.displayListPlayersOfSelectedTeam(cout);

	cout << "0: Quit and return to the previous menu" << endl;

	cout << "Enter the letter corresponding to your choice: ";

}


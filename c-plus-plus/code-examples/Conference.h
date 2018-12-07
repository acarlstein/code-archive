#ifndef CONFERENCE_H
#define CONFERENCE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Team.h"

using namespace std;

// Enum  used for method 
enum player_detail{
	SHOW_PLAYER_NAME = 256,
	SHOW_PLAYER_POSITION = 128,
	SHOW_PLAYER_HEIGHT = 64,
	SHOW_PLAYER_WEIGHT = 32,
	SHOW_PLAYER_YEAR = 16,
	SHOW_PLAYER_PPG = 8,
	SHOW_PLAYER_RPG = 4,
	SHOW_PLAYER_APG = 2,
	SHOW_PLAYER_TOPG = 1,
	SHOW_PLAYER_ALL_DETAILS = 512
};

// Enum used for method
enum team_detail{
	SHOW_TEAM_SCHOOL_NAME = 8,
	SHOW_TEAM_DETAILS = 4,
	SHOW_TEAM_PLAYERS_NAME = 2,
	SHOW_TEAM_PLAYERS = 1,
	SHOW_TEAM_ALL = 8
};

/**
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */
class Conference{

	// Insertion operator overloaded
	friend istream& operator >>(istream& in, Conference& conf);

private:
	// Maximum number of teams allowed
	static const int MAX_TEAMS = 9;
	
	// Teams
	Team teams[MAX_TEAMS];
	
	Team *firstPlaceTeam;

	Team *selectTeam;

	Team *teamWithTallestPlayer;
	
	Team *teamWithHighestScoringPlayer;
	
	int	numberOfTeams;

	int firstPlaceTeamNumber;

	int teamWithTallestPlayerNumber;

	int teamWithHighestScoringPlayerNumber;

	// This method will process the file
	void processFile(istream& in);

 	//Set the initial values to the private data members
	void init(void);

public:
	
	// Default Constructor
	Conference(void);

	// Constructor using filename
	Conference(string filename);

	// Copy Constructor
	Conference(const Conference& conference);
	
	// *** Get Methods ***

	// Get the number of teams in the conference
	int getNumberOfTeams();

	// Get the number of players in the selected team
	int getNumberOfPlayersInSelectedTeam();

	// Get the first place team's name in the conference 
	string getFirstPlaceTeamName();

	// Get the first place team's conference wins
	int getFirstPlaceTeamConferenceWins();

	// Get the first place team's overall wins
	int getFirstPlaceTeamOverallWins();

	// Get the first place team's number
	int getFirstPlaceTeamNumber();

	// Get the number of the team with the tallest player
	int getTeamWithTallestPlayerNumber();
	
	// Get the number of the team with the highest scoring player
	int getTeamWithHighestScoringPlayerNumber();

	//*** Show / Display / Print Methods ***

	// Display the names of all teams
	void displayListTeams(ostream& cout, 
						  bool detailed);

	// Display the list of all player that belong to the selected team
	void displayListPlayersOfSelectedTeam(ostream& cout);

	// Show the name of the highest scoring player in the conference
	void showHighestScoringPlayer(ostream& cout);

	// Show the name of the tallest player in the conference
	void showTallestPlayer(ostream& cout);

	// Display selected team
	void displaySelectedTeam(ostream& cout,
							 int detailed);

	// Display information about selected player
	void displaySelectedPlayerInformation(ostream& cout, 
						  	 		 	  int flags, 
							 		 	  char separator);	
	//*** Methods ***/
	
	// Select the tallest player in the conference as the target
	void selectTallestPlayer(void);

	// Select the highest scoring player in the conference as the targer
	void selectHighestScoringPlayer(void);

	// Select the first place team
	void selectFirstPlaceTeam(void);		

	// Select a team by its number
	void selectTeamBy(int number);

	// Select the player by its number
	void selectPlayerBy(int number);

	//Destructor
	~Conference(void);
};

#endif

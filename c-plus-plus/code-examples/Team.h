#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Team.h"
#include "Player.h"

using namespace std;

/**
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */
class Team{
	
	// Insertion operator overload
	friend istream& operator >> (istream& in, 
								 Team& team);

	// Compare two teams by their conference wins
	friend bool operator == (const Team& team1, 
							 const Team& team2);	

	// Compare two teams by their conference wins
	friend bool operator != (const Team& team1, 
							 const Team& team2);	

	// Compare two teams by their conference wins
	friend bool operator <= (const Team& team1, 
							 const Team& team2);	

	// Compare two teams by their conference wins
	friend bool operator >= (const Team& team1, 
							 const Team& team2);	

	// Compare two teams by their conference wins
	friend bool operator < (const Team& team1, 
							const Team& team2);

	// Compare two teams by their conference wins
	friend bool operator > (const Team& team1, 
							const Team& team2);	

private:

	Player *players;
	Player *ply;
	Player *selectPlayer;
	Player *tallestPlayer;
	Player *highestScoringPlayer;


	string schoolName;
	string mascotName;

	int tallestPlayerNumber;
	int highestScoringPlayerNumber;
	int confWins;
	int confLosses;
	int overWins; 
	int overLosses;
	int numPlayers;

 	// Set the initial values to the private data members
	void init(void);

public:

	// Default constructor
	Team(void);

	// Constructor using filename
	Team(string filename);

	// Copy constructor
	Team(const Team& team);

	// *** Get Methods ***
	string getSchoolName();

	string getMascotName();
	
	int getConferenceWins();

	int getConferenceLosses();

	int getOverallWins();

	int getOverallLosses();

	int getNumberPlayers();
	
	string getPlayerName(void);	

	string getPlayerName(int playerNumber);

	int getPlayerPosition(void);

	int getPlayerPosition(int playerNumber);

	void getPlayerPosition(char& position);

	// Get player position using a character that represent that position
	void getPlayerPosition(int playerNumber, 
						   char& position);

	int getPlayerHeight(void);	
	
	int getPlayerHeight(int playerNumber);	

	void getPlayerHeight(int& feet, 
						 int& inches);

	// Get player height in feet and inches
	void getPlayerHeight(int playerNumber, 
						 int& feet, 
						 int& inches);	

	int getPlayerWeight(void);

	int getPlayerWeight(int playerNumber);

	int getPlayerYearNumber(void);	

	int getPlayerYearNumber(int playerNumber);

	string getPlayerYear(void);

	string getPlayerYear(int playerNumber);

	int getPlayerGames(void);

	int getPlayerGames(int playerNumber);

	double getPlayerPpg(void);

	double getPlayerPpg(int playerNumber);

	double getPlayerRpg(void);

	double getPlayerRpg(int playerNumber);

	double getPlayerApg(void);

	double getPlayerApg(int playerNumber);

	double getPlayerTopg(void);

	double getPlayerTopg(int playerNumber);	
	
	int getTallestPlayerNumber();

	int getHighestScoringPlayerNumber();

	// *** Set Methods ***

	void setSchoolName(string newName);

	void setMascotName(string newName);

	void setConferenceWins(int newWins);

	void setConferenceLosses(int newLosses);

	void setOverallWins(int newWins);

	void setOverallLosses(int newLosses);

	void setNumberPlayers(int newNumber);

	// *** Show / Display / Print Methods ***

	// Show the team information	
	void displayInformation(ostream& cout);

	// Show a team's player information using the player number
	void displayPlayerInformation(ostream& cout, 
								  int playerNumber);

	// Show all players in the team
	void displayAllPlayersInformation(ostream& cout, 
									  bool detailed);

	// Show who is the tallest player in the team
	void showTallestPlayer(ostream& cout);

	// Show who is the highest scoring player in the team
	void showhighestScoringPlayer(ostream& cout);

	// *** Methods ***
	void selectTallestPlayer();

	void selectHighestScoringPlayer();

	void selectPlayerByNumber(int playerNumber);

	// Destructor;
	~Team(void);

};

#endif

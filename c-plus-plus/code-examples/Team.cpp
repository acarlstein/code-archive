/**
 * Team.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */

#include "Team.h"

///////////////////////////////////////////////////////////////////////////////
//**** OVERLOAD OPERATORS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * operator >>
 * @description: Insertion operator overloaded 
 * @param: in, team
 * @return: istream&
 */
istream& operator >> (istream& in, Team& team) {	

	team.tallestPlayer = new Player;

	team.highestScoringPlayer = new Player;

	team.ply = team.players;

	for (int numPlay = 0;
		 numPlay < team.numPlayers;
		 numPlay++, team.ply++){

		in >> *team.ply;
	

		if (team.tallestPlayer->getHeight() < team.ply->getHeight()){
			team.tallestPlayer = team.ply;
			team.tallestPlayerNumber = numPlay;
 		}

		if (*team.highestScoringPlayer < *team.ply){
/*			cout << endl 
				 <<"[TEAM>>][SCHOOL NAME: " << team.getSchoolName() << "]"
				 << endl
			 	 << "[team.ply->getName(): "
				 << team.ply->getName()
				 << " - team.ply->getPpg(): "
				 << team.ply->getPpg()
				 << "]"
				 << endl
				 << "[highestScoringPlayerNumber: " << numPlay << "]" << endl;
*/
			team.highestScoringPlayer = team.ply;
			team.highestScoringPlayerNumber = numPlay;
		}		

	} 
	
	return in;
}

/**
 * operator ==
 * @description: Compare two teams by their conference wins
 * @param: in, team1, team2
 * @return: istream&
 */
bool operator == (const Team& team1, 
				  const Team& team2){
     return  (team1.overWins == team2.overWins);
}

/**
 * operator !=
 * @description: Compare two teams by their conference wins
 * @param: in, team1, team2
 * @return: istream&
 */
bool operator != (const Team& team1, 
				  const Team& team2){
     return  (team1.overWins != team2.overWins);
}

/**
 * operator <=
 * @description: Compare two teams by their overall wins
 * @param: in, team
 * @return: istream&
 */
bool operator <= (const Team& team1,
				  const Team& team2){
     return  (team1.overWins <= team2.overWins);
}

/**
 * operator >=
 * @description: Compare two teams by their overall wins
 * @param: in, team1, team2
 * @return: istream&
 */
bool operator >= (const Team& team1, 
				  const Team& team2){
     return  (team1.overWins >= team2.overWins);
}

/**
 * operator <
 * @description: Compare two teams by their overall wins.
 * 				 If they are a tie then compare two teams 
 *				 by their conference wins.
 * @param: in, team1, team2
 * @return: istream&
 */
bool operator < (const Team& team1, 
				 const Team& team2){
	bool rtn = false;

	if (team1.overWins == team2.overWins)
		rtn = (team1.confWins < team2.confWins);
	else
		rtn = (team1.overWins < team2.overWins);


    return  rtn;
}

/**
 * operator >
 * @description: Compare two teams by their overall wins.
 * 				 If they are a tie then compare two teams 
 *				 by their conference wins.
 * @param: in, team1, team2
 * @return: istream&
 */
bool operator > (const Team& team1, 
				 const Team& team2){
	bool rtn = false;

	if (team1.overWins == team2.overWins)
		rtn = (team1.confWins > team2.confWins);
	else
		rtn = (team1.overWins > team2.overWins);
    return  rtn;
}

///////////////////////////////////////////////////////////////////////////////
//**** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////
/**
 * init
 * @description: Set the initial values to the private data members
 */
void Team::init(void){

	players = NULL;

	ply = NULL;

	selectPlayer = NULL;	

	tallestPlayer = NULL;

	highestScoringPlayer = NULL;

	schoolName = "";

	mascotName = "";

	confWins = 0;

	confLosses = 0;

	overWins = 0;

	overLosses = 0;

	numPlayers = 0;
}

///////////////////////////////////////////////////////////////////////////////
//**** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

/** 
 * Team
 * @description: Default constructor
 */
Team::Team(void){
	init();
}

/** 
 * Team
 * @description: Construction using filename
 * @param: filename
 */
Team::Team(string filename){
	
	init();

	ifstream fin;	

	fin.open(filename.data());	

	if (fin.is_open()){

			getline(fin, schoolName);			

			getline(fin, mascotName);
		
			fin >> confWins
				>> confLosses
				>> overWins
				>> overLosses
				>> numPlayers;

			fin.ignore();				

			// Dynamically allocate the Players array for this team	
			players = new Player[numPlayers];

			// 	Call the overloaded ifstream >> operator on Player
			fin >> *this;

	}else{

		cerr << endl
			 << "[X] Error: Error opening [" << filename 
			 << "] or File not found!" 
			 << endl;

	}
	
	fin.close();
}

/** 
 * Team
 * @description: Copy constructor
 * @param: newPlayer
 */
Team::Team(const Team& newTeam){

	players = newTeam.players;
	ply = newTeam.ply;
	tallestPlayer = newTeam.tallestPlayer;
	highestScoringPlayer = newTeam.highestScoringPlayer;
	selectPlayer = newTeam.selectPlayer;

	schoolName = newTeam.schoolName;
	mascotName = newTeam.mascotName;
	confWins = newTeam.confWins;
	confLosses = newTeam.confLosses;
	overWins = newTeam.overWins;
	overLosses = newTeam.overLosses;
	numPlayers = newTeam.numPlayers;	
}


// *** Get Methods ***
string Team::getSchoolName(){
	return schoolName;
}

string Team::getMascotName(){
	return mascotName;
}

int Team::getConferenceWins(){
	return confWins;
}

int Team::getConferenceLosses(){
	return confLosses;
}

int Team::getOverallWins(){
	return overWins;
}

int Team::getOverallLosses(){
	return overLosses;
}

int Team::getNumberPlayers(){
	return numPlayers;
}

/**
 * getPlayerName
 * @description: get the player's name of the selected player	
 * @return: string
 */
string Team::getPlayerName(void){
	return selectPlayer->getName();
}

/**
 * getPlayerName
 * @description: get the player's name using the player number	
 * @param: playerNumber
 * @return: string
 */
string Team::getPlayerName(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getName();
}

/**
 * getPlayerPosition
 * @description: get the player's position of the selected player	
 * @return: integer
 */
int Team::getPlayerPosition(void){
	return selectPlayer->getPosition();
}

/**
 * getPlayerPosition
 * @description: get the player's position using the player number	
 * @param: playerNumber
 * @return: integer
 */
int Team::getPlayerPosition(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getPosition();
}

/**
 * getPlayerPosition
 * @description: get the player's position of the selected player	
 * @return: char
 */
void Team::getPlayerPosition(char& position){
	return selectPlayer->getPosition(position);
}

/**
 * getPlayerPosition
 * @description: get the player's position character using the player number	
 * @param: playerNumber
 * @return: char
 */
void Team::getPlayerPosition(int playerNumber, 
						   	 char& position){

	ply = players;
	
	ply += playerNumber;

	ply->getPosition(position);

}

/**
 * getPlayerHeight
 * @description: get the player's height of the selected player	
 * @return: integer
 */
int Team::getPlayerHeight(void){
	return selectPlayer->getHeight();
}

/**
 * getPlayerHeight
 * @description: get the player's height in inches using the player number	
 * @param: playerNumber
 * @return: integer
 */
int Team::getPlayerHeight(int playerNumber){

	ply = players;

	ply += playerNumber;

	return ply->getHeight();
}

/**
 * getPlayerHeight
 * @description: get the player's Height of the selected player	
 * @return: integer
 */
void Team::getPlayerHeight(int& feet, 
						   int& inches){
	return selectPlayer->getHeight(feet, inches);
}

/**
 * getPlayerHeight
 * @description: get the player's height in feet and inches 
 *				 using the player number	
 * @param: playerNumber
 * @return: integer, integer
 */
void Team::getPlayerHeight(int playerNumber, int& feet, int& inches){
	ply = players;

	ply += playerNumber;
	
	ply->getHeight(feet, inches);
}

/**
 * getPlayerWeight
 * @description: get the player's weight of the selected player	
 * @return: integer
 */
int Team::getPlayerWeight(void){
	return selectPlayer->getWeight();
}

/**
 * getPlayerWeight
 * @description: get the player's weight using the player number	
 * @param: playerNumber
 * @return: integer
 */
int Team::getPlayerWeight(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getWeight();
}

/**
 * getPlayerYear
 * @description: get the player's year of the selected player	
 * @return: integer
 */
int Team::getPlayerYearNumber(void){
	return selectPlayer->getYear();
}

/**
 * getPlayerYear
 * @description: get the player's representative year number 
 * 				 using the player number	
 * @param: playerNumber
 * @return: integer
 */
int Team::getPlayerYearNumber(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getYear();
}

/**
 * getPlayerYear
 * @description: get the player's year of the selected player	
 * @return: integer
 */
string Team::getPlayerYear(void){
	string str;
	selectPlayer->getYear(str);
	return str;
}

/**
 * getPlayerYear
 * @description: get the player's year in string format using the player number	
 * @param: playerNumber
 * @return: string
 */
string Team::getPlayerYear(int playerNumber){

	string str;

	ply = players;

	ply += playerNumber;

	ply->getYear(str);	

	return str;
}

/**
 * getPlayerGames
 * @description: get the player's games of the selected player	
 * @return: integer
 */
int Team::getPlayerGames(void){
	return selectPlayer->getGames();
}


/**
 * getPlayerGames
 * @description: get the player's games using the player number	
 * @param: playerNumber
 * @return: integer
 */
int Team::getPlayerGames(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getGames();
}

/**
 * getPlayerPpg
 * @description: get the player's ppg of the selected player	
 * @return: double
 */
double Team::getPlayerPpg(void){
	return selectPlayer->getPpg();
}

/**
 * getPlayerPpg
 * @description: get the player's ppg using the player number	
 * @param: playerNumber
 * @return: integer
 */
double Team::getPlayerPpg(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getPpg();
}

/**
 * getPlayerRpg
 * @description: get the player's rpg of the selected player	
 * @return: double
 */
double Team::getPlayerRpg(void){
	return selectPlayer->getRpg();
}

/**
 * getPlayerRpg
 * @description: get the player's rpg using the player number	
 * @param: playerNumber
 * @return: double
 */
double Team::getPlayerRpg(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getRpg();
}

/**
 * getPlayerApg
 * @description: get the player's apg of the selected player	
 * @return: double
 */
double Team::getPlayerApg(void){
	return selectPlayer->getApg();
}

/**
 * getPlayerApg
 * @description: get the player's apg using the player number	
 * @param: playerNumber
 * @return: double
 */
double Team::getPlayerApg(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getApg();
}

/**
 * getPlayerTopg
 * @description: get the player's topg of the selected player	
 * @return: double
 */
double Team::getPlayerTopg(void){
	return selectPlayer->getTopg();
}

/**
 * getPlayerTopg
 * @description: get the player's topg using the player number	
 * @param: playerNumber
 * @return: double
 */
double Team::getPlayerTopg(int playerNumber){
	ply = players;

	ply += playerNumber;

	return ply->getTopg();
}

int Team::getTallestPlayerNumber(){
	return tallestPlayerNumber;
}

int Team::getHighestScoringPlayerNumber(){
	return highestScoringPlayerNumber;
}

// *** Set Methods ***
void Team::setSchoolName(string newName){
	schoolName = newName;
}

void Team::setMascotName(string newName){
	mascotName = newName;
}

void Team::setConferenceWins(int newWins){
	confWins = newWins;
}

void Team::setConferenceLosses(int newLosses){
	confLosses = newLosses;
}

void Team::setOverallWins(int newWins){
	overWins = newWins;
}

void Team::setOverallLosses(int newLosses){
	overLosses = newLosses;
}

void Team::setNumberPlayers(int newNumber){
	numPlayers = newNumber;
	players = new Player[newNumber];
}

//*** Show / Display / Print Methods ***

/**
 * displayInformation
 * @description: Display the team's information
 * @param: cout
 */
void Team::displayInformation(ostream& cout){

	cout << "Team Name" << "\t"
		 << "mascot" << "\t"
		 << "wins" << "\t"
		 << "losses" << "\t"
		 << "all wins" << "\t"
		 << "all losses" << "\t"
		 << "players" << endl;
	
	cout << schoolName << "\t"
		 << mascotName << "\t"
		 << confWins << "\t"
		 << confLosses << "\t"
		 << overWins << "\t"
		 << overLosses << "\t"
		 << numPlayers << endl;
}

/**
 * displayPlayerInformation
 * @description: Display the player's information using the player number
 * @param: cout, playerNumber
 */
void Team::displayPlayerInformation(ostream& cout, 
									int playerNumber){

	int feet;
	int inches;
	
	feet = 0;
	inches = 0;

	ply = players;
	
	ply += playerNumber;
	
	// Display this player's information
	ply->displayAllInformation(cout);

}

/**
 * displayAllPlayersInformation
 * @description: Display all the player's names in the team
 *				 if detailed is true then display also their details
 * @param: cout, detailed
 */ 				 
void Team::displayAllPlayersInformation(ostream& cout,
										bool detailed){
	
	char position = ' ';

	int feet = 0;

	int inches = 0;

	string year = "";

	ply = players;

	if (detailed){

		cout << "Name" << "\t\t"
			 << "Pos" << "\t"
			 << "Height" << "\t"
			 << "Weight" << "\t"
			 << "Year" << "\t"
			 << "Game" << "\t"
			 << "Ppg" << "\t"
			 << "Rpg" << "\t"
			 << "Apg" << "\t"
			 << "Topg"
			 << endl;
	}

	for(int i = 0; i < numPlayers; i++, ply++){

		cout << ply->getName().substr(0,13) << "\t";

		// If detailed is true then display all the information
		if (detailed){

			ply->getPosition(position);

			ply->getHeight(feet, inches);		

			ply->getYear(year);

			cout <<	left << setw(3) << position << "\t"
				 << feet << "-" << inches << "\t"
				 << ply->getWeight() << "\t"
				 << year.substr(0, 7) << "\t"
				 << ply->getGames() << "\t"
				 << setprecision(2)
				 << ply->getPpg() << "\t"
				 << ply->getRpg() << "\t"
				 << ply->getApg() << "\t"
				 << ply->getTopg() << "\t";
		}
		cout << endl;
	}			 

};


// *** Methods ***
void Team::selectTallestPlayer(){
	if (selectPlayer == NULL) selectPlayer = new Player;
	selectPlayer = tallestPlayer;
}

void Team::selectHighestScoringPlayer(){
	if (selectPlayer == NULL) selectPlayer = new Player;
	selectPlayer = highestScoringPlayer;
}

void Team::selectPlayerByNumber(int playerNumber){
	ply = players;
	
	ply += playerNumber;

	selectPlayer = ply;
}


/** 
 * ~Team
 * @description: Destructor
 */
Team::~Team(void){

	delete[] players;

	delete selectPlayer;

	players = NULL;

	selectPlayer = NULL;

	ply = NULL;

	tallestPlayer = NULL;

	highestScoringPlayer = NULL;

}

/**
 * Conference.cpp
 * @author: Alejandro G. Carlstein
 * @course: CS 240
 */

#include "Conference.h"

///////////////////////////////////////////////////////////////////////////////
//**** OVERLOAD OPERATORS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * operator >>
 * @description: Insertion operator overloaded 
 * @param: in, conf
 * @return: istream&
 */
istream& operator >> (istream& in, 
					  Conference& conf) {	

	conf.processFile(in);

	// return the stream by reference
	return in;
}

///////////////////////////////////////////////////////////////////////////////
// **** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * processFile
 * @description: Process the file
 * @param in
 */
void Conference::processFile(istream& in){

	int conferenceWins;
	int conferenceLosses;
	int overallWins;
	int overallLosses;
	int numberPlayers;
	int tallest1;
	int tallest2;
	int highestScoring1;
	int highestScoring2;

	string filename;
	string schoolName;
	string mascotName;

	ifstream finTeam;    
	
	numberOfTeams = 0;
	tallest1 = 0;
	tallest2 = 0;
	highestScoring1 = 0;
	highestScoring2 = 0;

	
	selectTeam = new Team();

	firstPlaceTeam = new Team();

	teamWithTallestPlayer = new Team();

	teamWithHighestScoringPlayer = new Team();

	//[For all nine teams]
	// 1. Read the name of each team's file from the conference file
	while(numberOfTeams < MAX_TEAMS && getline(in, filename)){
	
		// 2. Open the team file
		finTeam.open(filename.data());
	
		if (finTeam.is_open() && !finTeam.fail()){
	
			// 3. Read the team information from 
			//the top of the Team File
			getline(finTeam, schoolName);			

			getline(finTeam, mascotName);
		
			finTeam >> conferenceWins
					>> conferenceLosses
					>> overallWins
					>> overallLosses;
		
			// Set team information
			teams[numberOfTeams].setSchoolName(schoolName);
			teams[numberOfTeams].setMascotName(mascotName);
			teams[numberOfTeams].setConferenceWins(conferenceWins);
			teams[numberOfTeams].setConferenceLosses(conferenceLosses);
			teams[numberOfTeams].setOverallWins(overallWins);
			teams[numberOfTeams].setOverallLosses(overallLosses);
				
			// 4. Read the number of players on this team	
			finTeam >> numberPlayers;

			finTeam.ignore();				

			// 5. Dynamically allocate the Players array for this team	
			teams[numberOfTeams].setNumberPlayers(numberPlayers);
		
			// 	a. Call the overloaded ifstream >> operator on Player
			finTeam >> teams[numberOfTeams];
						

				if(teamWithTallestPlayer->getNumberPlayers() <= 0){
					*teamWithTallestPlayer = teams[0];
				}	

				if(teamWithHighestScoringPlayer->getNumberPlayers() <= 0){
					*teamWithHighestScoringPlayer = teams[0];
				}	


			//	b. Read the player specific information
			//		i. Store who is tallest and highest in the conference
			for (int playerNumber = 0;
				 playerNumber < numberPlayers;
				 playerNumber++){
								
				tallest1 = teams[numberOfTeams].getTallestPlayerNumber();
	
				highestScoring1 = teams[numberOfTeams].getHighestScoringPlayerNumber();


				tallest2 = teamWithTallestPlayer->getTallestPlayerNumber();

				highestScoring2 = teamWithHighestScoringPlayer->getHighestScoringPlayerNumber();

				// If they have the same height then decide by using ppg
				// else choose the player with the highest height
				if (teams[numberOfTeams].getPlayerHeight(tallest1) ==
					teamWithTallestPlayer->getPlayerHeight(tallest2)){

						if (teams[numberOfTeams].getPlayerPpg(tallest1) >
							teamWithTallestPlayer->getPlayerPpg(tallest2)){

							*teamWithTallestPlayer = teams[numberOfTeams];

						}						
				}else{

					if (teams[numberOfTeams].getPlayerHeight(tallest1) >
						teamWithTallestPlayer->getPlayerHeight(tallest2)){
						*teamWithTallestPlayer = teams[numberOfTeams];
					}

				}


				if (teams[numberOfTeams].getPlayerPpg(highestScoring1) >
					teamWithHighestScoringPlayer->getPlayerPpg(highestScoring2)){
					*teamWithHighestScoringPlayer = teams[numberOfTeams];
				}						

			}
		
		}else{
			
			cerr << endl
			 << "[X] Error: Error opening ["
			 << filename 
			 << "] or File not found!" 
			 << endl;

		}
	

		if (*firstPlaceTeam < teams[numberOfTeams]){
			*firstPlaceTeam = teams[numberOfTeams];
		}	

		numberOfTeams++;		

		// 7.	[end for]
		// 8. Close the Team File
		finTeam.close();
	}

}

/**
 * init
 * @description: Set the initial values to the private data members
 */
void Conference::init(void){
	firstPlaceTeam = NULL;

	selectTeam = NULL;

	teamWithTallestPlayer = NULL;
	
	teamWithHighestScoringPlayer = NULL;
	
	numberOfTeams = 0;

	firstPlaceTeamNumber = 0;
	
	teamWithTallestPlayerNumber = 0;

	teamWithHighestScoringPlayerNumber = 0;

}

///////////////////////////////////////////////////////////////////////////////
// **** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

/** 
 * Conference
 * @description: Default constructor
 */
Conference::Conference(void){
	init();
}

/** 
 * Conference
 * @description: Construction using filename
 * @param: filename
 */
Conference::Conference(string filename){
	init();

	ifstream fin;	

	fin.open(filename.data());	

	if (fin.is_open()){

		// Process the stream from the file
		processFile(fin);

	}else{
		cerr << endl
			 << "[X] Error: Error opening [" << filename 
			 << "] or File not found!" 
			 << endl;
	}
	
	fin.close();
}

/** 
 * Conference
 * @description: Copy constructor
 * @param: newConference
 */
Conference::Conference(const Conference& newConference){

	// Copy array Teams
	for (int i = 0; i < numberOfTeams; i++)
		teams[i] = newConference.teams[i];

	firstPlaceTeam = newConference.firstPlaceTeam;

	selectTeam = newConference.selectTeam;

	teamWithTallestPlayer = newConference.teamWithTallestPlayer;
	
	teamWithHighestScoringPlayer = newConference.teamWithHighestScoringPlayer;
	
	numberOfTeams = newConference.numberOfTeams;

	firstPlaceTeamNumber = newConference.firstPlaceTeamNumber;

	teamWithTallestPlayerNumber = newConference.teamWithTallestPlayerNumber;

	teamWithHighestScoringPlayerNumber = newConference.teamWithHighestScoringPlayerNumber;
}
// *** Get Methods ***

/**
 * getNumberOfTeams
 * @description: return the number of teams in the conference
 * @return: integer
 */
int Conference::getNumberOfTeams(){
	return numberOfTeams;
}

/**
 * getNumberOfPlayersInSelectedTeam
 * @description: return the number of players that are in the team selected
 * @return integer
 */
int Conference::getNumberOfPlayersInSelectedTeam(){
	return selectTeam->getNumberPlayers();
}

// Get the first place team's name in the conference 
string Conference::getFirstPlaceTeamName(){
	return firstPlaceTeam->getSchoolName();
}

// Get the first place team's conference wins
int Conference::getFirstPlaceTeamConferenceWins(){
	return firstPlaceTeam->getConferenceWins();
}

// Get the first place team's conference wins
int Conference::getFirstPlaceTeamOverallWins(){
	return firstPlaceTeam->getOverallWins();
}

//
int Conference::getFirstPlaceTeamNumber(){
	return firstPlaceTeamNumber;
}

//
int Conference::getTeamWithTallestPlayerNumber(){
	return teamWithTallestPlayerNumber;
}
	
//
int Conference::getTeamWithHighestScoringPlayerNumber(){
	return teamWithHighestScoringPlayerNumber;
}



//*** Show / Display / Print Methods ***

/**
 * displayListTeams
 * @description: Display the names of all teams
 *				 If detailed is true then this method will display
 *               all the information related with each team
 * @param: cout, detailed
 */
void Conference::displayListTeams(ostream& cout, 
								 bool detailed){
	
	// If detailed is true, then display titles
	if (detailed){

		cout << "Team Name" << "\t"
			 << "mascot" << "\t\t"
			 << "wins" << "\t"
			 << "losses" << "\t"
			 << "all Wins" << "\t"
			 << "all looses" << "\t"
			 << "players" << "\t"
			 << endl;
	}

	// Loop thought all teams in conference
	for (int teamNumber = 0;
		 teamNumber < numberOfTeams;
		 teamNumber++){

		cout << ((detailed) ? teamNumber : (teamNumber + 1))
			 << ":" 
			 << teams[teamNumber].getSchoolName().substr(0, 13) << "\t";
			
		// If detailed is true then display all the information of the team
 		// else only display the team number and the number of the team
		if (detailed){
			cout << left 
				 << setw(16) 
				 << teams[teamNumber].getMascotName();

			cout << teams[teamNumber].getConferenceWins() << "\t"
				 << teams[teamNumber].getConferenceLosses() << "\t"
				 << teams[teamNumber].getOverallWins() << "\t\t"
				 << teams[teamNumber].getOverallLosses() << "\t\t"
				 << teams[teamNumber].getNumberPlayers();
		}
		cout << endl;
	}
}


//
void Conference::displayListPlayersOfSelectedTeam(ostream& cout){
	selectTeam->displayAllPlayersInformation(cout, false);
}

/**
 * showHighestScoringPlayer
 * @description: Show the name of the highest scoring player in the conference
 * @param: cout
 */
void Conference::showHighestScoringPlayer(ostream& cout){

	int highestScoring =  selectTeam->getHighestScoringPlayerNumber();

	cout << selectTeam->getPlayerName(highestScoring)
		 << " ("
		 << selectTeam->getSchoolName()
		 << "): "
		 << selectTeam->getPlayerPpg(highestScoring)
		 << " ppg"
		 << endl;		
}

/**
 * showTallestPlayer
 * @description: Show the name of the tallest player in the conference
 * @param: cout
 */
void Conference::showTallestPlayer(ostream& cout){

	int feet = 0;
	int inches = 0;
	int tallest = selectTeam->getTallestPlayerNumber();

	// Get the height in feet and inches
	selectTeam->getPlayerHeight(tallest, feet, inches);

	// Display the name of the player and his/her height in feet and inches
	cout << selectTeam->getPlayerName(tallest)
		 << " (" << selectTeam->getSchoolName() << ")"
		 << endl
		 << "Height: "
		 << feet << "-" << inches
		 << endl;
}

/**
 * displaySelectedTeam
 * @description: Display selected team.
 *				 The mode of display can be used in conjuntion using '+':
 *               SHOW_TEAM_SCHOOL_NAME: Show the school name (team)
 *			 	 SHOW_TEAM_DETAILS: Show all the team's details
 *				 SHOW_TEAM_PLAYERS_NAME: Show all the names of the players
 *										 in the team
 *				 SHOW_TEAM_PLAYERS: Show all the players' details
 *				 SHOW_TEAM_ALL: Show everything from the school name to
 *							    the players' details
 * @param: cout, flags
 */ 
void Conference::displaySelectedTeam(ostream& cout,
						 			 int flags){

	// Show the School (team) name of the selected team
	if (flags >= SHOW_TEAM_SCHOOL_NAME){

		cout << selectTeam->getSchoolName();

		flags -= SHOW_TEAM_SCHOOL_NAME;
	}

	// Show the team details of the selected team
	if(flags >= SHOW_TEAM_DETAILS){
		cout << "\t" 
			 << selectTeam->getMascotName() << "\t"		
			 << selectTeam->getConferenceWins() << "\t"
			 << selectTeam->getConferenceLosses() << "\t"
			 << selectTeam->getOverallWins() << "\t"
			 << selectTeam->getOverallLosses() << "\t"
			 << selectTeam->getNumberPlayers() 
			 << endl;

		flags -= SHOW_TEAM_DETAILS;
	}
	
	// Show all the players' names of the selected team
	if(flags >= SHOW_TEAM_PLAYERS_NAME){

		selectTeam->displayAllPlayersInformation(cout, false);

		flags -= SHOW_TEAM_PLAYERS_NAME;

	}

	// Show all the player's details of the selected team
	if(flags >= SHOW_TEAM_PLAYERS){

		selectTeam->displayAllPlayersInformation(cout, true);

		flags -= SHOW_TEAM_PLAYERS;
	}
	
}

/**
 * displaySelectedPlayerInformation
 * @description: Display the information of the selected player
 *				 The information can be separated using the separator
 *               The mode of display can be used in conjuntion using '+':
 *				 SHOW_PLAYER_NAME: Show the player's name
 * 				 SHOW_PLAYER_POSITION: Show the player's position
 *				 SHOW_PLAYER_HEIGHT: Show the player's height in feet and inches
 *				 SHOW_PLAYER_WEIGHT: Show the player's weight
 *				 SHOW_PLAYER_YEAR: Show the player's year
 *				 SHOW_PLAYER_PPG: Show the player's points scoring average 
 *				 SHOW_PLAYER_RPG: Show the player's rebouding points average
 *				 SHOW_PLAYER_APG: Show the player's assistance points average
 *				 SHOW_PLAYER_TOPG: Show the player's top points average
 *				 SHOW_PLAYER_ALL_DETAILS: Show all the player's details
 * @param: cout, flags, separator
 */
void Conference::displaySelectedPlayerInformation(ostream& cout, 
										 		  int flags, 
										  		  char separator){
	

	// Show the player's name
	if (flags >= SHOW_PLAYER_NAME){

		cout << selectTeam->getPlayerName()
			 << separator;

		flags -= SHOW_PLAYER_NAME;
	}

	// Show the player's position
	if (flags >= SHOW_PLAYER_POSITION){

		char position;

		selectTeam->getPlayerPosition(position);

		cout << position
			 << separator;

		flags -= SHOW_PLAYER_POSITION;
	}

	// Show the player's height in feet and inches
	if (flags >= SHOW_PLAYER_HEIGHT){

		int feet = 0;
		int inches = 0;

		selectTeam->getPlayerHeight(feet, inches);
		cout << feet << "-" << inches
			 << separator;

		flags -= SHOW_PLAYER_HEIGHT;
	}

	// Show the player's weight
	if (flags >= SHOW_PLAYER_WEIGHT){

		cout << selectTeam->getPlayerWeight()			 
			 << separator;
		flags -= SHOW_PLAYER_WEIGHT;
	}

	// Show the player's year
	if (flags >= SHOW_PLAYER_YEAR){
		int feet = 0;
		int inches = 0;

		selectTeam->getPlayerHeight(feet, inches);
		cout << feet << "-" << inches
			 << separator;

		flags -= SHOW_PLAYER_YEAR;
	}

	// Show the player's ppg
	if (flags >= SHOW_PLAYER_PPG){

		cout << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(1)
			 << selectTeam->getPlayerPpg()
			 << separator;

		flags -= SHOW_PLAYER_PPG;
	}

	// Show the player's rpg
	if (flags >= SHOW_PLAYER_RPG){

		cout << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(1)
			 << selectTeam->getPlayerRpg()
			 << separator;

		flags -= SHOW_PLAYER_RPG;
	}

	// Show the player's apg
	if (flags >= SHOW_PLAYER_APG){

		cout << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(1) 
			 << selectTeam->getPlayerApg()
			 << separator;

		flags -= SHOW_PLAYER_APG;
	}

	// Show the player topg
	if (flags >= SHOW_PLAYER_TOPG){

		cout << setiosflags(ios::fixed | ios::showpoint)
			 << setprecision(1)
			 << selectTeam->getPlayerTopg()
			 << separator;

		flags -= SHOW_PLAYER_TOPG;
	}

}

/*** Methods ***/

/**
 * selectTallesPlayer
 * @description: Make the tallest player in the conference the targer
 */
void Conference::selectTallestPlayer(void){
	selectTeam = teamWithTallestPlayer;
	selectTeam->selectTallestPlayer();
}

/**
 * selectTallesPlayer
 * @description: Make the highest scoring player in the conference 
 * 				 the targer
 */
void Conference::selectHighestScoringPlayer(void){
	selectTeam = teamWithHighestScoringPlayer;
	selectTeam->selectHighestScoringPlayer();
}

// Select the first place team
void Conference::selectFirstPlaceTeam(void){
	selectTeam = firstPlaceTeam;
}


/**
 * selectTeamBy
 * @description: Select a team by the number that represent it
 * @param: number
 */
void Conference::selectTeamBy(int number){
	
	selectTeam = new Team;

	*selectTeam = teams[number - 1];

}

/**
 * selectTeamBy
 * @description: Select a player by the number that represent it
 * @param: number
 */
void Conference::selectPlayerBy(int number){

	selectTeam->selectPlayerByNumber(number - 1);

}

/**
 * ~Conference
 * @description: Destructor
 */
Conference::~Conference(void){
	
	delete selectTeam;

	firstPlaceTeam = NULL;

	selectTeam =  NULL;

	teamWithTallestPlayer = NULL;
	
	teamWithHighestScoringPlayer = NULL;

} 




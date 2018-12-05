/**
 * Player.cpp
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */

#include "Player.h"

//**** OVERLOAD OPERATORS ****

/**
 * operator >>
 * @description: Insertion operator overloaded 
 * @param: in, player
 * @return: istream&
 */
istream& operator >> (istream& in, Player& player) {	

	vector<string> words;
	
	string s;

	string line;

	getline(in, line);

	// Set stringsteam with every line
	stringstream ss(line);

	// Every word that is separated with white spaces push them back
	// In the vector		
	while (ss>>s) words.push_back(s);
	
	// Only process if there exist the minimal information required
	if (words.size() > player.MIN_INFO){	
		
		player.topg = atof(words.back().data());
		words.pop_back();

		player.apg = atof(words.back().data());
		words.pop_back();

		player.rpg = atof(words.back().data());
		words.pop_back();

		player.ppg = atof(words.back().data());
		words.pop_back();

		player.games = atoi(words.back().data());
		words.pop_back();

		player.setYear(words.back());
		words.pop_back();
	
		player.weight = atoi(words.back().data());
		words.pop_back();

		player.height = player.getInches(words.back(), '-');
		words.pop_back();

		player.setPosition((char)*words.back().c_str());
		words.pop_back();

		// Obtain the rest of the string which would be the player's name
		while (!words.empty()){
				
			player.name = words.back() + " " + player.name;

			words.pop_back();
		}

	}else{
		cerr << endl
			 << "[X] Error: Not enough information"
			 << endl;
	}

	return in;
}

/**
 * operator ==
 * @description: Compare two players by their average point scoring (ppg)
 * @param: in, player1, player2
 * @return: istream&
 */
bool operator == (const Player& player1, const Player& player2){
     return  (player1.ppg == player2.ppg);
}

/**
 * operator !=
 * @description: Compare two players by their average point scoring (ppg)
 * @param: in, player1, player2
 * @return: istream&
 */
bool operator != (const Player& player1, const Player& player2){
     return  (player1.ppg != player2.ppg);
}

/**
 * operator <=
 * @description: Compare two players by their average point scoring (ppg)
 * @param: in, player1, player2
 * @return: istream&
 */
bool operator <= (const Player& player1, const Player& player2){
     return  (player1.ppg <= player2.ppg);
}

/**
 * operator >=
 * @description: Compare two players by their average point scoring (ppg)
 * @param: in, player1, player2
 * @return: istream&
 */
bool operator >= (const Player& player1, const Player& player2){
     return  (player1.ppg >= player2.ppg);
}

/**
 * operator <
 * @description: Compare two players by their average point scoring (ppg)
 * @param: in, player1, player2
 * @return: istream&
 */
bool operator < (const Player& player1, const Player& player2){
     return  (player1.ppg < player2.ppg);
}

/**
 * operator >
 * @description: Compare two players by their average point scoring (ppg)
 * @param: in, player1, player2
 * @return: istream&
 */
bool operator > (const Player& player1, const Player& player2){
     return  (player1.ppg > player2.ppg);
}


//**** PRIVATE METHODS ****
void Player::init(void){
	name = "";

	position = 0;
	height = 0;
	weight = 0;
	year = 0;
	games = 0;

	ppg = 0.0;
	rpg = 0.0;
	apg = 0.0;
	topg = 0.0;
}


/**
 * getInches
 * @description: Convert Feets and Inches to inches
 * @param: strHeight, separator
 * @return: integer
 */
int Player::getInches(string strHeight, char separator){
	
	int inches;
	string strFeet;
	string strInches;

	// Get the feet number from the begining until the separator
	strFeet = strHeight.substr(0, strHeight.find(separator));

	// After the separator, the number should be the inches
	strInches = strHeight.substr(strHeight.find(separator) + 1, 
								 strHeight.length());
	
	// Convert each feet to inches
	inches = (atoi(strFeet.data())) * INCHES_PER_FEET;

	// Add the feet's inches to the inches
	inches += atoi(strInches.data());
		
	// Return the height in inches
	return inches;
}

//**** PUBLIC METHODS ****

/** 
 * Player
 * @description: Default constructor
 */
Player::Player(void){
	init();
}

/** 
 * Player
 * @description: Construction using filename
 * @param: filename
 */
Player::Player(string filename){
	init();
	
	ifstream fin;	

	fin.open(filename.data());	

	if (fin.is_open()){

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
 * Player
 * @description: Copy constructor
 * @param: newPlayer
 */
Player::Player(const Player& newPlayer){
	name = newPlayer.name;

	position = newPlayer.position;
	height = newPlayer.height;
	weight = newPlayer.weight;
	year = newPlayer.year;
	games = newPlayer.games;

	ppg = newPlayer.ppg;
	rpg = newPlayer.rpg;
	apg = newPlayer.apg;
	topg = newPlayer.topg;
}

// *** Get Methods ***

string Player::getName(){
	return name;
}
	
int Player::getPosition(){
	return position;
}

/**
 * getPosition
 * @description: get the player's position character
 * @return: char
 */
void Player::getPosition(char& newPosition){
	newPosition = (char)position;
}

int Player::getHeight(){
	return height;
}

/**
 * getHeight
 * @description: get the player's height in feet and inches 
 * @return: integer, integer
 */
void Player::getHeight(int& feet, 
					   int& inches){

	feet = height / INCHES_PER_FEET;

	inches = height % INCHES_PER_FEET;
}

int Player::getWeight(){
	return weight;
}

int Player::getYear(){
	return year;
}

/**
 * getPlayerYear
 * @description: get the player's year in string format
 * @return: string
 */
void Player::getYear(string& newYear){
	switch(year){

		case FRESHMAN:
			newYear = STR_FRESHMAN;
			break;

		case SOPHOMORE:
			newYear = STR_SOPHOMORE;
			break;

		case JUNIOR:
			newYear = STR_JUNIOR;
			break;

		case SENIOR:
			newYear = STR_SENIOR;
			break;

		default:
			cerr << endl
				 << "[X] ERROR: Incorrect year stored! "
				 << "[ " << year << " ]"
				 << endl;
			break;
	}
	newYear = newYear;
}

int Player::getGames(){
	return games;
}

double Player::getPpg(){
	return ppg;
}

double Player::getRpg(){
	return rpg;
}

double Player::getApg(){
	return apg;
}

double Player::getTopg(){
	return topg;
}


// *** Set Methods ***

void Player::setName(string newName){
	name = newName;
}

void Player::setPosition(int newPosition){
	position = newPosition;
}

/**
 * setPosition
 * @description: Set player's position using the character that represent
 * 				 that position
 * @param: newPosition
 */
void Player::setPosition(char newPosition){

			switch((int)newPosition){
				case GUARD:
				case CENTER:
				case FORWARD:
					position = (int)newPosition;
					break;

				default:
					cerr << endl
					 	 << "[X] Error: Position does not exist : "
					 	 << "it was " << (int)newPosition << " and should be"
						 << "[" << GUARD << "], "
						 << "[" << CENTER << "], or "
						 << "[" << FORWARD << "]"
						 << endl;
					break;
			}
}

void Player::setHeight(int newInches){
	height = newInches;
}

/**
 * setHeight
 * @description: Set the player's height using feet and inches
 * @param: newFeet, newInches
 */
void Player::setHeight(int newFeet, int newInches){
	height = (newFeet * INCHES_PER_FEET) + newInches;
}

void Player::setWeight(int newWeight){
	weight = newWeight;
}

void Player::setYear(int newYear){
	year = newYear;
}

/**
 * setYear
 * @description: Set player's year using string
 * @param newyear
 */
void Player::setYear(string newYear){
	
	if (newYear == STR_FRESHMAN){
		year = FRESHMAN;

	}else if(newYear == STR_SOPHOMORE){
		year = SOPHOMORE;

	}else if(newYear == STR_JUNIOR){
		year = JUNIOR;		
	
	}else if(newYear == STR_SENIOR){
		year = SENIOR;		
	
	}else{

		cerr << endl
			 << "[X] Error: Wrong Year information! " 
			 << endl
			 << "newYear is " << newYear << " but it Must be: "
			 << endl
			 << STR_FRESHMAN << ", "
			 << STR_SOPHOMORE << ", "
			 << STR_JUNIOR << ", or "
			 << STR_SENIOR			 
			 << endl;
	}

}

void Player::setGames(int newGames){
	games = newGames;
}

void Player::setPpg(double newPpg){
	ppg = newPpg;
}

void Player::setRpg(double newRpg){
	rpg = newRpg;
}

void Player::setApg(double newApg){
	apg = newApg;
}

void Player::setTopg(double newTopg){
	topg = newTopg;
}

// *** Show / Display / Print Methods ***

/**
 * showPosition
 * @description: Show player's position using a character
 * @param: cout
 */
void Player::showPosition(ostream& cout){
	char position;
	getPosition(position);
	cout << position;
}

/**
 * showHeight
 * @description: Show player's height in feet and inches
 * @param: cout
 */
void Player::showHeight(ostream& cout){
	int feet = 0;
	int inches = 0;

	getHeight(feet, inches);

	cout << feet << "-" << inches;
}

/** 
 * showYear
 * @description: Show the player's year using a string
 * @param: cout
 */
void Player::showYear(ostream& cout){
	string year;
	getYear(year);
	cout << year;
}

/**
 * displayAllInformation
 * @description: Display all the player's information
 */
void Player::displayAllInformation(ostream& cout){
	int feet = 0;
	int inches = 0;
	char position = ' ';
	string year = " ";
		
	getHeight(feet, inches);
	getPosition(position);
	getYear(year);

	cout << name << "\t"
		 << position << "\t"
		 << feet << "-" << inches << "\t"
		 << weight << "\t"
		 << year << "\t"
		 << games << "\t"
		 << ppg << "\t"
		 << rpg << "\t"
		 << apg << "\t"
		 << topg << endl;
}

/** 
 * ~Player
 * @description: Destructor
 */
Player::~Player(void){
}




#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cctype>

using namespace std;

enum player_years{
	FRESHMAN,
	SOPHOMORE,
	JUNIOR,
	SENIOR,
};

enum player_positions{
	GUARD = 71,
	CENTER = 67,
	FORWARD = 70
};

static const string STR_FRESHMAN = "Freshman";
static const string STR_SOPHOMORE = "Sophomore";
static const string	STR_JUNIOR = "Junior";
static const string STR_SENIOR = "Senior";
static const int INCHES_PER_FEET = 12;

/**
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description:
 */
class Player{

	friend istream& operator >> (istream& in, 
								 Player& player);

	friend bool operator == (const Player& player1, 
							 const Player& player2);	

	friend bool operator != (const Player& player1, 
							 const Player& player2);	

	friend bool operator <= (const Player& player1, 
							 const Player& player2);	

	friend bool operator >= (const Player& player1, 
							 const Player& player2);	

	friend bool operator < (const Player& player1, 
							const Player& player2);

	friend bool operator > (const Player& player1, 
							const Player& player2);	
	
private:
	const static unsigned int MIN_INFO = 9;

	string name;

	int position;
	int height;
	int weight;
	int year;
	int games;

	double ppg;
	double rpg;
	double apg;
	double topg;

	void init(void);

	//Convert Feets and Inches to inches
	int getInches(string height, char separator);		

public:
	
	// Default Constructor
	Player(void);

	Player(string filename);

	Player(const Player& newPlayer);

	// *** Get Methods ***

	string getName();
	
	int getPosition();

	void getPosition(char& newPosition);

	int getWeight();

	int getYear();

	void getYear(string& year);

	int getGames();

	double getPpg();

	double getRpg();

	double getApg();

	double getTopg();	

	int getHeight();	

	void getHeight(int& feet, 
				   int& inches);

	// *** Set Methods ***
	void setName(string newName);

	void setPosition(int newPosition);

	void setPosition(char newPosition);

	void setHeight(int newInches);	

	void setHeight(int newFeet, 
				   int newInches);

	void setWeight(int newWeight);

	void setYear(int newYear);

	void setYear(string newYear);
	
	void setGames(int newGames);

	void setPpg(double newPpg);

	void setRpg(double newRpg);

	void setApg(double newApg);

	void setTopg(double newTopg);

	//*** Show / Display / Print Methods ***
	void showPosition(ostream& cout);

	void showHeight(ostream& cout);

	void showYear(ostream& cout);
		
	void displayAllInformation(ostream& cout);

	// Destructor
	~Player(void);

};


#endif

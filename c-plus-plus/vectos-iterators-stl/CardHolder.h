#ifndef CARDSHOLDER
#define CARDSHOLDER

#include <iostream>

using namespace std;

class CardsHolder {

	private:

	public:

	CardsHolder(void);

	insert(int value);

	~CardsHolder(void);
};

CardsHolder::CardsHolder(void){
	cout << endl << "[CARDHOLDER]" << endl;
}

CardsHolder::insert(int value){
}

CardsHolder::~CardsHolder(void){
	cout << endl << "[~CARDHOLDER]" << endl;
}

#endif


/**
  * @Author: Alejandro G. Carlstein
  * @Course: CS240
  */

#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item{
		
	public: 
		
		int frequency;
	
		string data;
		
		//Bonus B. Write a single sort function (but two different comparison
		//		   functions/operators) to produce the two different 
		//		   sorted lists.
		
		// Compare two Items by their number
		friend bool operator == (const Item& Item1, 
								 const Item& Item2);	

		// Compare two Items by their number
		friend bool operator != (const Item& Item1, 
								 const Item& Item2);	

		// Compare two Items by their number
		friend bool operator <= (const Item& Item1, 
								 const Item& Item2);	

		// Compare two Items by their number
		friend bool operator >= (const Item& Item1, 
								 const Item& Item2);	

		// Compare two Items by their number
		friend bool operator < (const Item& Item1, 
								const Item& Item2);

		// Compare two Items by their number
		friend bool operator > (const Item& Item1, 
								const Item& Item2);	
	
		Item(void);		 
		
		Item(const Item& new_item);	
		
		~Item(void);
	
}; 

#endif
 
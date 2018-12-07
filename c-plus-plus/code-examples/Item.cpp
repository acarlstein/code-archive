/**
  * @Author: Alejandro G. Carlstein
  * @Course: CS240
  */

#include "Item.h"

/**
 * operator ==
 * @description: Compare two Items by their number
 * @param: in, Item1, Item2
 * @return: istream&
 */
bool operator == (const Item& Item1, 
				  const Item& Item2){
	 return  (Item1.frequency == Item2.frequency);
}

/**
 * operator !=
 * @description: Compare two Items by their number
 * @param: in, Item1, Item2
 * @return: istream&
 */
bool operator != (const Item& Item1, 
				  const Item& Item2){
     return  (Item1.frequency != Item2.frequency);
}

/**
 * operator <=
 * @description: Compare two Items by their number
 * @param: in, Item
 * @return: istream&
 */
bool operator <= (const Item& Item1,
				  const Item& Item2){

    bool b_rtn = false;
	 
	if (Item1.frequency == Item2.frequency){
	 
		b_rtn = (Item1.data > Item2.data);
	 
	}else{
		b_rtn = (Item1.frequency > Item2.frequency);
	}
	
	return  b_rtn;
	 
}	

/**
 * operator >=
 * @description: Compare two Items by their number
 * @param: in, Item1, Item2
 * @return: istream&
 */
bool operator >= (const Item& Item1, 
				  const Item& Item2){
    
	bool b_rtn = false;
	 
	if (Item1.frequency == Item2.frequency){
	 
		b_rtn = (Item1.data > Item2.data);
	 
	}else{
		b_rtn = (Item1.frequency < Item2.frequency);
	}
	 
	return  b_rtn;
}

/**
 * operator <
 * @description: Compare two Items by their number
 * @param: in, Item1, Item2
 * @return: istream&
 */
bool operator < (const Item& Item1, 
				 const Item& Item2){
	return (Item1.frequency > Item2.frequency);
}

/**
 * operator >
 * @description: Compare two Items by their number.
 * @param: in, Item1, Item2
 * @return: istream&
 */
bool operator > (const Item& Item1, 
				 const Item& Item2){
	return (Item1.frequency < Item2.frequency);
}


Item::Item(void):
	  frequency(0),
	  data(""){
}

Item::Item(const Item& new_item):
	  frequency(new_item.frequency),
	  data(new_item.data){
}

Item::~Item(void){
}
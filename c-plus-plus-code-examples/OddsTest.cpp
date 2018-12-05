#include <iostream>
#include <cstdlib>
#include "List.h"
using namespace std;

int main (int argc, char *argv[]) {
	
   // Initialize the random number generator (to generate random 
   // linked list data elements)
   srand(time(NULL));
	
   // Create list and insert random data into each item 
   // (random numbers between 0 and 9999)
   List *my_list = new List();
   List *list2; 
   List *list3; 

   for(int i=0;i<1000;i++){
//      my_list->insert(rand() % 10000);         // Even and odd values
//      my_list->insert((rand() % 10000) * 2);   // Even values only
      my_list->insert((rand() % 10000) * 2 + 1); // Odd values only
   }
	
   // Print out the list contents
   cout << "--------------------------------------" << endl; 
   cout << "List: " ;
   my_list->show();
   cout << "--------------------------------------" << endl; 
	
   cout << "--------------------------------------" << endl; 
   list2 = my_list->splitOddEven();
   cout << "Even: " ;
   my_list->show();
   cout << "Odd: " ;
   list2->show();
   cout << "--------------------------------------" << endl; 
	
   cout << "--------------------------------------" << endl; 
   list3 = my_list->splitBigSmall();
   cout << "Small Even: " ;
   my_list->show();
   cout << "Big Even: " ;
   list3->show();
   cout << "--------------------------------------" << endl; 

   // Delete all linked lists
   delete(my_list);
   delete(list2);
   delete(list3);
}

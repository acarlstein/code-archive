#include <iostream>
#include <string>
#include "List.cc"

using namespace std;

template <typename T> 
List<T> *reverse(List<T>& list);


int main (int argc, char *argv[]) {

	List<string> my_list;

	List<string> *my_list_2;

	cout << endl << "BUILD ORIGINAL---------------------------" << endl;

	my_list.addtoback("one(1)"); 
	my_list.addtofront("nine(9)");
	my_list.addtoback("eight(8)");

	my_list.show();
	
	cout << endl << "REVERSE ORIGINAL---------------------------" << endl;

	my_list_2 = reverse<string>(my_list);
	
	cout << endl << "New: ";

	my_list_2->show();
	
	delete my_list_2;
	    
	return 0;
}
 
// Write a templated reverse() function 
// (not a member function of your class, but instead 
// a standalone templated function) 
// that operates on a doubly linked list object 
// (that you implemented for Part 1). 
// Your reverse function should take as input a 
// doubly linked list object, 
// and return a copy of the list, 
// but in reverse order. 

// Your function must be recursive, 
// and must use the four functions above.

// A reversed list can be built by taking an element off one side, 
// reversing the list without that element in it, 
// and then putting that element back into the list, 
// on the other side.... use that reasoning to design your recursive 
// reverse function. 

template <typename T> 
List<T> *reverse(List<T>& list){		
		
	if (list.size() < 1){
		
		List<T> *rlist = new List<T>;
				
		return (rlist);

	}else{
	
		Node<T> *node;

		List<T> *rlist = new List<T>;

		node = list.getfirst();
				
		rlist = list.getrest();
														
		
		rlist = reverse<T>(*rlist);

		rlist->addtoback(node->data);		

		delete (node);

		return (rlist);	
	}

}


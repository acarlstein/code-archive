#include <iostream>
using namespace std;

#ifndef LIST
#define LIST

typedef int ElementType;

class Node {
   public:

   // Create a linked list node by setting its data to the input parameter
   // and the next node in the linked list to NULL (0)
   Node(ElementType data_input);

   //The default constructor doesn't initialize the data members
   Node();
				
   // Contains the data of the linked list node
   ElementType data;	

   // Contains a pointer to the next item in the linked list
   Node *next;
};

class List
{
   private:

      // List class's private data member:
      Node *list_head;	// Contains a pointer to the first node in the
                        // linked list (the head of the list)
			
      int num_elements;

      // takes out the node with the smallest data member from this list,
      // and returns a pointer to it.
      Node *extractLargest(); 

   public:
      // Create a Linked list by initializing it's head to NULL (0)
      List();

      // Delete all the elements in the linked list when the list is deleted
      ~List();

      // Add a single element to the head of the linked list
      void insert(ElementType data_input);

      // Remove a single element from the head of the linked list
      void remove();	

      // Print all the elements in the linked list
      void show();

      // This function splits the list in half, adding the those half of
      // the elements with the largest values into a new linked list, and
      // keeping only those half of the elements with the smallest values
      // in the list on which this function is called. The function
      // returns a pointer to the new (heap allocated) list with the 
      // larger elements in it. If the original list contains an odd 
      // number of elements, then the returned list contains one
      // fewer element than the list on which this function is called.
      // If the original list is empty, the function returns a pointer
      // to a new empty List (not a NULL pointer).
      List *splitBigSmall();

      // This function splits the list in two, adding the the elements
      // with odd integer values into a new linked list, and keeping only
      // those elements with even integer values in the list on which
      // this function is called. The function returns a pointer to
      // the new (heap allocated) list with the odd elements in it. If the
      // original list is empty, or if there are no odd elements, the
      // function returns a pointer to a new empty List (not a NULL
      // pointer). 
      List *splitOddEven();
};

#endif

/**
  * @Author: Alejandro G. Carlstein
  * @Course: CS240
  */

#ifndef SORT_CC
#define SORT_CC

#include <iostream>
#include <cstdlib>

//#include "functions.h"

using namespace std;

//////////////////////////////////////////////////////////////////
// TEMPLATE CLASS SORT   /////////////////////////////////////////
//////////////////////////////////////////////////////////////////

template <typename T>
class Sort{

	private:
	
		void swap(T* first, 
				  T* last);
	
		void choose_pivot(T array[],
						  int first, 
						  int last);
		
		void partition(T array[], 
					   int first, 
					   int last, 
					   int& pivotIndex,
					   bool order);
						
	public:
	
		Sort(void);

		void quicksort(T array[], 
					   int first,
					   int last,
					   bool order);
		
		void selection(T array[],
					   int first,
					   int last,
					   bool order);

	    void insertion(T array[],
					   int first,
					   int last,
					   bool order);
							

		void bubble(T array[],
					int first,
					int last,
					bool order);
					   					   
		~Sort(void);
};

///////////////////////////////////////////////////////////////////////////////
//**** OVERLOAD OPERATORS ****
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**** PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Sort<T>::swap(T* first, 
				   T* last){
	T temp;
	temp = *first;
	*first = *last;
	*last = temp;
}

template <typename T>
void Sort<T>::choose_pivot(T array[],
						  int first, 
						  int last){
						  
	int index_pivot = ((first + last) / 2); 
	
	swap (&array[first], &array[index_pivot]);
}
						 
template <typename T>		
void Sort<T>::partition(T array[], 
						int first, 
						int last, 
						int& pivotIndex,
						bool order = false){
	int index_last;
	int index_unknown;
	
	if (!order){
		// Place pivot in array
		choose_pivot(array, first, last);

		// Copy pivot
		T pivot = array[first];

		// Index of last item
		index_last = first;
	
		// Index of next item after the first item
		index_unknown = first + 1;
	
		// Move one item at a time until region is empty
		for (; index_unknown <= last; index_unknown++){					
			
			// Move item from unknown to proper region
			if (array[index_unknown] < pivot){
		
				index_last++;
		
				swap(&array[index_unknown], &array[index_last]);
	
			}// end if
		}// end for
		
		// Place pivot into proper position and indicate its location
		swap(&array[first], &array[index_last]);
		
		pivotIndex = index_last;
		
	}else{
		
	}// end if
	
		


}

		
///////////////////////////////////////////////////////////////////////////////
//**** PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

//**** Constructors ****/

template <typename T>
Sort<T>::Sort(void){
	cout << "[Sort (default)]" << endl;
}

//**** Get Methods ****/

//**** Set Methods ****/

//**** Display Methods ****/

//****  Methods ****/

template <typename T>
void Sort<T>::quicksort(T array[], 
					   int first,
					   int last,
					   bool order = false){
	
	int pivotIndex = 0;
	
	if (!order){
	
		if (first < last){
	
			// Create partition
			partition(array, first, last, pivotIndex, order);
	
			// Sort regions
		
			quicksort(array, first, pivotIndex - 1, order);
		
			quicksort(array, pivotIndex + 1, last, order);
		}
		
	}else{

	}
	
}

template <typename T>
void Sort<T>::selection(T array[],
						int first,
						int last,
						bool order){
							 
	int i, j, min;
	
	i = first;
	
	for (; i < last; i++){
	
		min = i;
		
		for (j = i + 1; j < last; j++){
		
			if (array[j] < array[min]){
			
				min = j;
				
			}// end if
		
		}//end for
	
		swap(array[i], array[min]);
	
	}//end for
					
}


template <typename T>
void Sort<T>::insertion(T array[],
						int first,
						int last,
						bool order){

	int i, j, min;
	
	T tmp_to_insert;
	
	for (i = first + 1; i < last; i++){
	
		tmp_to_insert = array[i];
		
		j = i;
		
		for (; j > first && array[ j - 1] > tmp_to_insert; j--){
		
			array[j] = array[j - 1];
		
		}// end for
	
		array[j] = tmp_to_insert;
	
	}//end for
						
}

template <typename T>
void Sort<T>::bubble(T array[],
					 int first,
					 int last,
					 bool order){

	int i,j,min;
	
	i = last - 1;
	
	j = first + 1;
	
	for (; i>= first; i--){
	
		for (; j <= i; i++){
		
			if (array[j - 1] > array[j]){
			
				swap(array[j - 1], array[j]);
			
			}//end if
		
		}// end for
		
	}//end for
					 
}



//**** Destructor ****/

template <typename T>
Sort<T>::~Sort(void){
	cout << "[~Sort(X)]" << endl;
}


#endif
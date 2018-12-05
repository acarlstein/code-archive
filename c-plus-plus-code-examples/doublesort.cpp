/**
  * @Author: Alejandro G. Carlstein
  * @Course: CS240
  */
#include <iostream>
#include <fstream>
#include <string>

#include "Sort.cc"
#include "Item.h"

using namespace std;

const int MAX_WORDS = 1000;

const string OUTPUT_ALPHA_SORT_FILE = "short.alpha.txt";
const string OUTPUT_FREQ_SORT_FILE = "sort.freq.txt";

template <typename T>
T *resize_array(T *array, 
				 int &num_elements) {
	
	//Bonus C. Program to work for any number of words (subject to memory 
	//		   constraints), by rellocating and copying words into new
	//		   larger arrays, as necessary.
	//	   C1. Never store words in an array that's more than twice as
	//         big as necessary.
	//         (You can mimic how STL containers grow)
	//     C2. Not use a file to hold and then count the words
	//     C3. Not allocate space on the heap separately for 
	//		   each word as it comes in. Put them first into a linked list.
	
	int new_size = num_elements * 2;
	
    T* new_array = new T[new_size];

    //memcpy( new_array, array, num_elements * sizeof(T) );
	for (int i = 0; i < num_elements; i++){

		//new_array[i].data = array[i].data;
		//new_array[i].frequency = array[i].frequency;
		new_array[i] = array[i];

	}

    num_elements = new_size;
	
    delete [] array;
	
    //array = new_array;
	
	//return new_size;
	return new_array;
}


/**
 * main
 * @description: Lab 10
 * @due: November 24, 2009 1:00PM EST
 */
int main(int argc, char *argv[]){
	
	int str_len;
			
	string words[MAX_WORDS];

	Sort<string> str_sort;
	
	ofstream fout;
	
	str_len = -1;
		
	//1. Reads up to 1000 words separated by newline characters   (one at the time)
	for (int i = 0; !cin.fail() && i < MAX_WORDS; i++, str_len++)
		cin >> words[i];
	
	//2. Print out in alphabetical order to file called short.alpha.txt	
	//	2a. one word per line with number of occurences of each word
	//	       listed in parentheses after the word
		
	fout.open(OUTPUT_ALPHA_SORT_FILE.data());	
	
	if (fout.is_open()){
			
		// Bonus A. Use an O(N log N) sorting algorithm, make sure that no 
		//                 pre-processing steps exceed O(N log N)
		str_sort.quicksort(words, 0, str_len - 1);			
		
		for (int i = 0; i < str_len; i++)
			cout << words[i] << endl;

		for (int i = 0; i < str_len; i++)
			fout << words[i] << endl;

	}else{
		cerr << "[X] ERROR: Couldn't open " << OUTPUT_ALPHA_SORT_FILE << endl;
	}	
			
	fout.close();
	
	//3. Print out in frequency order to file caled sort.freq.txt
		
	fout.open(OUTPUT_FREQ_SORT_FILE.data());	
	
	if (fout.is_open()){
				
		int item_size = 2;	
				
		Item* item = new Item[item_size];
		
		Sort<Item> item_sort;
		
		// Record their frequency
		int j = 0;
		
		item[0].frequency = 1;
		item[0].data = words[0];
		
		for (int i = 1; i < str_len; i++){
		
			if (item_size < i){
						
				// resize array
				item = resize_array(item, item_size);
				
			}
				
			if (item[j].data == words[i]){
			
				//Increase frequency
				item[j].frequency++;
							
			}else{
				
				j++;
			 
				item[j].frequency = 1;
				
				item[j].data = words[i];
				
			}
			
		}
		
		//Order words by frequency
		// Bonus A. Use an O(N log N) sorting algorithm, make sure that no 
		//                 pre-processing steps exceed O(N log N)
		item_sort.quicksort(item, 0, str_len);
						
		for (int i = 0; i < str_len; i++)
			if (item[i].frequency > 0) fout << "(" << item[i].frequency << ") " << item[i].data << endl;

	}else{
		cerr << "[X] ERROR: Couldn't open " << OUTPUT_ALPHA_SORT_FILE << endl;
	}	
			
	fout.close();
		
	return 0;

}

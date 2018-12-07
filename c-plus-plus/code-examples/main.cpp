#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include "BSTree.cc"

const int MAX_NUMBERS = 10000;
	
int main(int argc, char *argv[]){

	cout << endl << "{main}" << endl;

	vector<int> numbers;
	vector<int> reverseNumbers;
	vector<int> randomNumbers;

	BST<int> tree;
	BST<int> reverseTree; 
	BST<int> randomTree;

	//Declare at top of main...
	struct timeval initialSimTime, postSimTime;
	
	double totalSimTime;
	
	int findMod = 10000;
	int NTimes = 5000;
	
	cout << "Create Numbers..." << endl;
	
	// Insert the first 10,000 odd numbers, in order, into it.
	for (int i = 1; i < MAX_NUMBERS; i += 2)
			reverseNumbers.push_back(i);
		
	numbers = reverseNumbers;

	reverse(numbers.begin(), numbers.end());

	randomNumbers = numbers;

	random_shuffle(randomNumbers.begin(), randomNumbers.end());

	while(!numbers.empty()){
		tree.insert(numbers.back());
		numbers.pop_back();
	}
	
	while(!reverseNumbers.empty()){
		reverseTree.insert(reverseNumbers.back());
		reverseNumbers.pop_back();
	}
	
	while(!randomNumbers.empty()){
		randomTree.insert(randomNumbers.back());
		randomNumbers.pop_back();
	}
	
	cout << "Search..." << endl;
			
///////////////////////////////////////////////////////////////////////

	// Place before the thing you want to time
	gettimeofday(&initialSimTime, NULL);

	cout << endl << "Values found: ";
	
	for (int i = 1, j = 0; i < MAX_NUMBERS && j < NTimes; i += 2)
		if (i % findMod)
			if (tree.find(i) == i){
				cout << i << " ";
				j++;
			}

	cout << endl;

	//Place after the thing you want to time
	gettimeofday(&postSimTime, NULL);

	totalSimTime = (double)(
				   (double)(postSimTime.tv_sec - initialSimTime.tv_sec) * 1000000 + 
				   (double)(postSimTime.tv_usec - initialSimTime.tv_usec) ) /
				   (double)1000000;
	
	//Report how long it takes your program to run each call to that function
	//Output the time it took to do the stuff you wanted to time
	cout << "Simulation took "<< totalSimTime << " seconds" << endl << endl;
	
////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////

	// Place before the thing you want to time
	gettimeofday(&initialSimTime, NULL);
	
	cout << endl << "Values found: ";

	for (int i = 1, j = 0; i < MAX_NUMBERS && j < NTimes; i += 2)
		if (i % findMod)
			if (reverseTree.find(i) == i){
				cout << i << " ";
				j++;
			}
				
	cout << endl;

	//Place after the thing you want to time
	gettimeofday(&postSimTime, NULL);

	totalSimTime = (double)(
				   (double)(postSimTime.tv_sec - initialSimTime.tv_sec) * 1000000 + 
				   (double)(postSimTime.tv_usec - initialSimTime.tv_usec) ) /
				   (double)1000000;
	
	//Report how long it takes your program to run each call to that function
	//Output the time it took to do the stuff you wanted to time
	cout << "(Reverse) Simulation took " 
	     << totalSimTime << " seconds" << endl << endl;
	
////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////

	// Place before the thing you want to time
	gettimeofday(&initialSimTime, NULL);

	cout << endl << "Values found: ";

	for (int i = 1, j = 0; i < MAX_NUMBERS && j < NTimes; i += 2)
		if (i % findMod)
			if (tree.find(i) == i){
				cout << i << " ";
				j++;
			}

	cout << endl;
	
	//Place after the thing you want to time
	gettimeofday(&postSimTime, NULL);

	totalSimTime = (double)(
				   (double)(postSimTime.tv_sec - initialSimTime.tv_sec) * 1000000 + 
				   (double)(postSimTime.tv_usec - initialSimTime.tv_usec) ) /
				   (double)1000000;
	
	//Report how long it takes your program to run each call to that function
	//Output the time it took to do the stuff you wanted to time
	cout << "(Random) Simulation took " 
	 	 << totalSimTime << " seconds" << endl << endl;
	
////////////////////////////////////////////////////////////////////////













	
/*
	// Search for the first 20 multiples of 1,000
	for (int i = 0; i <= NTimes; i++)
		if (i % findMod == 0)
			if (tree.find(i) == i)
				cout << "Value " << i << " Found!" << endl;



	//Report how long it takes your program to run each call to that function
	//Output the time it took to do the stuff you wanted to time
	cout << "Simulation took "<< totalSimTime << " seconds" << endl;
		
		
	// Start over with a new BST and insert the same odd numbers, 
	// but in reverse order. 
	// Again, search for the first 20 multiples of 1,000 and 
	// report how long each takes	

	// Insert the first 10,000 odd numbers, in order, into it.
	for (int i = MAX_NUMBERS; i >= 0; i--)
		if (i % 2 != 0)
			reverseTree.insert(i);
			
	findMod = 1000;
	NTimes = 20;
	
	// Place before the thing you want to time
	gettimeofday(&initialSimTime, NULL);
	
	// Search for the first 20 multiples of 1,000
	for (int i = 0; i <= NTimes; i++)
		if (i % findMod)
			if (reverseTree.find(i) == i)
				cout << "Value " << i << " Found!" << endl;

	//Place after the thing you want to time
	gettimeofday(&postSimTime, NULL);

	totalSimTime = (double)(
				   (double)(postSimTime.tv_sec - initialSimTime.tv_sec) * 1000000 + 
				   (double)(postSimTime.tv_usec - initialSimTime.tv_usec) ) /
				   (double)1000000;

	//Report how long it takes your program to run each call to that function
	//Output the time it took to do the stuff you wanted to time
	cout << "Simulation (Reverse) took "<< totalSimTime << " seconds" << endl;

	// Insert the first 10,000 odd integers in random order into,
	// yet another BST, and run the same test.

	// Insert the first 10,000 odd numbers, in order, into it.
	
	
	int i;
	srand(time(NULL));
	
	bool bMatch[MAX_NUMBERS];
	
	for (int i = 0; i < MAX_NUMBERS; i++)
		bMatch[i] = false;
	
	int max = MAX_NUMBERS;
	int min = 0;

	int counter = 0;	
	while(randomTree.size() < MAX_NUMBERS){

		i = rand() % (max - 1) + min;
		
		if ((max - 1) == i)
			max--;
			
		if ((min + 1) == i)
			min++;
			
		if (i >= max) 
			i -= min;	

		for (int j = 0; j < MAX_NUMBERS; j++)
			cout << ((bMatch[i])? 1: 0);


		if ( i % 2 != 0 && !bMatch[i]){
			bMatch[i] = true;
			cout << " " << i;	
			randomTree.insert(i);
		}
		cout << endl;
		
	}
	
	cout << endl << "SIZE: " << randomTree.size() << endl;
	
	findMod = 1000;
	NTimes = 20;
	
	// Place before the thing you want to time
	gettimeofday(&initialSimTime, NULL);
	
	// Search for the first 20 multiples of 1,000
	for (int i = 0; i <= NTimes; i++)
		if (i % findMod)
			if (reverseTree.find(i) == i)
				cout << "Value " << i << " Found!" << endl;

	//Place after the thing you want to time
	gettimeofday(&postSimTime, NULL);

	totalSimTime = (double)(
				   (double)(postSimTime.tv_sec - initialSimTime.tv_sec) * 1000000 + 
				   (double)(postSimTime.tv_usec - initialSimTime.tv_usec) ) /
				   (double)1000000;

	//Report how long it takes your program to run each call to that function
	//Output the time it took to do the stuff you wanted to time
	cout << "Simulation (Random) took "<< totalSimTime << " seconds" << endl;
*/
		
	return 0;
}

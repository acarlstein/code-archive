/* Framework for the sorting programs.
 * Program: 02
 * Course: CS333 A0 - Spring 2010
 * Author: Alejandro G. Carlstein
 * Description: This program will read a set of integers from standard 
 * input and sort them by implement a heap sort using the pseudocode 
 * from the book Introduction to Algorithms" by Thomas H. Cormen. 
 * Then print them out in sorted order (smallest to largest).
 */
 
#include <stdio.h>

#define MAX_SIZE 1000000
#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)
#define DIV_BY_2(i) (i >> 1)

void Max_heapify(int array[], int i, int heap_size);
void Build_max_heap(int array[], int heap_size);
void Exchange(int *a, int *b);
void Heapsort(int array[], int length);

int data[MAX_SIZE];
int n;

int main(int argc, char* argv[]){

	int i;
	int heap_size;

	/* Read in the data */
	n = 0;
    while (scanf("%d", &data[n]) == 1)
	    ++n;

	/* Sort the numbers low to high */
	Heapsort(data, n);

	/* Print out the data */
	for (i = 0; i < n; ++i)
	    printf("%d\n", data[i]);
	    
	return 0;
}

/*
 * Max_heapify helps to rebuild the heap region
 */
void Max_heapify(int array[], int i, int heap_size){

	int l, r, temp, largest;
	
	l = LEFT(i);
	
	r = RIGHT(i);	
	
	// Find Largest value
	largest = (l < heap_size && array[l] > array[i]) ? l : i;
		
	if (r < heap_size && array[r] > array[largest]) largest = r;


	if (largest != i){
	
		// Exchange 
		Exchange(&array[i], &array[largest]);
		
		// Rebuild heap region		
		Max_heapify(array, largest, heap_size);	
		
	}// end if	
					
}

/*
 * Build_max_heap helps to build the initial heap
 */
void Build_max_heap(int array[], int heap_size){
	
	int i = DIV_BY_2(heap_size);
	
	for (; i > -1; i--){
	
		Max_heapify(array, i, heap_size);
	
	}//end for

}

/*
 * Exchange swap the values holded by two variables
 */
void Exchange(int *a, int *b){
		
		int temp;

		temp = *a;
		*a = *b;
		*b = temp;
}

/*
 * Heapsort sort an array from the smallest element to the largest
 */
void Heapsort(int array[], int length){

	int i;
	int	heap_size = length ;

	Build_max_heap(data, length);

	for (i = (length - 1) ; i > 0; --i){
	
		// Exchange the largest item in the heap region
		// to the beginning of the sorted region
		Exchange(&data[0], &data[i]);
		
		// Reduce the heap region, increase the sorted region
		heap_size--;
		
		// Rebuild the heap region
		Max_heapify(data, 0, heap_size);
	
	}//end for
	
}

/* Framework for the sorting programs.
 * Program: 03
 * Course: CS333 A0 - Spring 2010
 * Author: Alejandro G. Carlstein
 * Description: This program will read in a formatted set of integers, sort them, 
 *				and then read in another set, and search. It will print 
 *				"yes" or "no" for each number (one word per line).
 *				The input is going to be formatted as follows: 
 *					1. First number, n, will be the number of values to read in
 *					   that will be sorted. 
 *					2. Read a number m, and that will tell you how many 
 * 					   numbers to look for.
 *				Then this program willuse binary search, and print out 
 *              yes or no depending of the value searched and found.
 */
 
#include <stdio.h>

#define MAX_SIZE 1000000
#define YES "yes"
#define NO "no"
#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)
#define DIV_BY_2(i) (i >> 1)
#define DBG 0

void Max_heapify(int array[], int i, int heap_size);
void Build_max_heap(int array[], int heap_size);
void Exchange(int *a, int *b);
void Heapsort(int array[], int length);
void Split_data(int data[], int *num_data, int keys[], int *num_keys);
int Binary_search(int key, int data[], int begin, int data_size);

int data[MAX_SIZE];
int n;

int main(int argc, char* argv[]){

	int i;
	
	int n;
	
	int m = -1;
	
	int heap_size;
	
	int ia_keys[MAX_SIZE];
	
	/* Read in the data */
	n = 0;
    while (scanf("%d", &data[n]) == 1)
	    ++n;
	    
	/* Print out the data */
	if (DBG)
		for (i = 0; i < n; ++i)
		    printf("[%d] %d\n", i, data[i]);
	    
	if (DBG) 
		printf("****************\n");    	    

	Split_data(data, &n, ia_keys, &m);

	/* Sort the numbers low to high */
	Heapsort(data, n);

	if (DBG){
		printf("(%d) Keys:\n", m);
		for (i = 0; i < m; ++i)    
		    printf("[%d] %d\n", i, ia_keys[i]);

		printf("data:\n");
		/* Print out the data */
		for (i = 0; i < n; ++i)
		    printf("[%d] %d\n", i, data[i]);

	}// end if
		
	printf("\n");
	
	// Search each element of ia_keys in the data array
	for (i = 0; i < m; i++){		
		printf("%s\n", (( Binary_search(ia_keys[i], data, 0, n) ) ? YES : NO));
	}
		
	return 0;
}

int Binary_search(int key, int data[], int begin, int data_size){

	if(DBG) 
		printf("Binary_Search(key: %d, begin: %d, data_size: %d)\n", 
			   key, begin, data_size);
	
 	int	b_found = 0;

	int mid;

    if (data_size > begin){

		mid = DIV_BY_2(data_size + begin);
		
		if (DBG) printf("mid: %d\n", mid);

		if (data[mid] == key){

			b_found = 1;

		}else{
		
			if (data[mid] > key){
          	
				b_found = Binary_search(key, data, begin, mid);
          	
          	}else{
          	
          		b_found = Binary_search(key, data, mid + 1, data_size);
          	
          	}//end if
          	
		}//end if
             	
    }//end if
    
	return b_found;
}

void Split_data(int data[], int *num_data, int keys[], int *num_keys){

	int i;

	// Store original data array size
	int tmp_num_data = *num_data;
	
	// New data array size in the number of values to be sorted
	*num_data = data[0];
	
	for (i = 0; i < tmp_num_data; i++){
	
		if (i <= *num_data){
		
			Exchange(&data[i], &data[i+1]);
			
		}else{
		
			keys[i - (*num_data + 1)] = data[i + 1];
			
			++(*num_keys);
			
		}//end if	
		
	}//end for

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

/**
 * Framework for the sorting programs. 
 * Modified by: Alejandro G. Carlstein
 * Program Number: 1
 * Description: This code will implement an insertion sort algorithm
 *              which will follow the following steps:
 *              1. Copy item at current position
 *              2. Shift previous position item to current position
 *                 while item (in previous positions) is greater than
 *                 the item copied and there are previous items 
                   to compare with the key item
 *              3. Insert copied item in the previous position in which 
 *                 the previous item is found to be
 *                 smaller than the copied item
 *                 
 */
#include <stdio.h>
#define MAX_SIZE 1000000
int data[MAX_SIZE];
int n;

int main()
{
  int i;
  int j;
  int key_item;

  /* Read in the data */
  n = 0;
  while (scanf("%d", &data[n]) == 1)
    ++n;

  /* Sort the numbers low to high */
  for (i = 1; i < n; i++){

  	key_item = data[i];

  	for (j = i; (j > 0) && (data[j - 1] > key_item); j--){

 	  data[j] = data[j - 1];

 	}//end for 

 	data[j] = key_item;

  }//end for

  /* Print out the data */
  for (i = 0; i < n; ++i)
    printf("%d\n", data[i]);
}

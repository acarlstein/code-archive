#ifndef PRIORITY_QUEUE_CC_
#define PRIORITY_QUEUE_CC_

#include <iostream>

using namespace std;


#include <iostream>
#include <cstdlib>

enum{
	FALSE = 0,
	TRUE = -1
};

/////////////////////////////////
///// Implements Priority Queue
/////////////////////////////////

// Node of Priority Queue
template <typename T> class PriorityQueue;

template <typename T> 
class Node {

	public:

		friend class PriorityQueue<T>;
	
		Node<T>*  previous;

		T data;

		Node<T>*  next;

};


// Class Prioriry Queue
template <typename T>
class PriorityQueue{
	
	private:
	
		Node<T> current;
	
		Node<T>* head;  // Pointer to Head

		Node<T>* ptr;   

        // Pointer for travelling through Queue

		static int num_nodes;

        // Keeps track of Number of nodes

	public:

		PriorityQueue(void);
	
		PriorityQueue(const T&);

		T get_maximum(void);

		T get_minimum(void);

		void insert(const T&);

		int remove(const T&);

		void print(void);

		int search (const T&);

		~PriorityQueue(void);

};

// First Nodes Created With Constructor
template <typename T> 
int PriorityQueue<T>::num_nodes=1;


template <typename T> 
PriorityQueue<T>::PriorityQueue(void){

    current.previous=NULL;

	cout << "Enter First Element of Queue: ";
    cin >> current.data;
	
	cout << endl;

    current.next = NULL;

    head = &current;

    ptr = head;

}

// Constructor
template <typename T> 
PriorityQueue<T>::PriorityQueue(const T& new_data){

    current.previous=NULL;

    current.data = new_data;

    current.next = NULL;

    head = &current;

    ptr = head;

}

// Function Finding get_maximum Priority Element
template <typename T> 
T PriorityQueue<T>::get_maximum(void){

    int tmp;

    ptr = head;

    tmp = ptr->data;

    while(ptr->next!=NULL){
	
        if(ptr->data > tmp){
		
            tmp = ptr->data;
		
		}
		
        ptr=ptr->next;
    }
	
    if(ptr->next == NULL && ptr->data>tmp){
     
		tmp = ptr->data;

	}
	
    return(tmp);
}

// Function Finding get_minimum Priority Element
template <typename T> 
T PriorityQueue<T>::get_minimum(void){

    int tmp;

    ptr = head;

    tmp = ptr->data;

    while(ptr->next!=NULL){
	
        if(ptr->data<tmp){
		
            tmp = ptr->data;
		
		}
        
		ptr=ptr->next;
    
	}
    
	if(ptr->next == NULL && ptr->data<tmp){
	
        tmp = ptr->data;
    
	}
	
	return(tmp);
}

// Function inserting element in Priority Queue
template <typename T> 
void PriorityQueue<T>::insert(const T& DT){

    Node<T>* new_node;
    
    new_node = new Node<T>;

    new_node->data = DT;

    while(ptr->next!=NULL){
    
		ptr=ptr->next;
	
	}
    
	if(ptr->next == NULL){
	
        new_node->next = ptr->next;
    
		ptr->next = new_node;
    
	}
    
	num_nodes++;
}

// Function deleting element in Priority Queue
template <typename T> 
int PriorityQueue<T>::remove(const T& dataDel){

    Node<T>* mynode,*tmp;

    ptr = head;
    
    if(num_nodes  ==  1){
	
        cout<<"Cannot remove the only Node"<<endl;
    
		return FALSE;
    }
	
    if(ptr->data == dataDel){

		/***  Checking condition for deletion of first node  ***/
        tmp = ptr;
		
        ptr=ptr->next;
		
        ptr->previous=NULL;
		
        //delete tmp;
		
        head=ptr;
		
        num_nodes--;
		
        return(TRUE);
		
    }else{
	
        while(ptr->next->next!=NULL){
		
            /***  Checking condition for deletion of   ***/
            /*** all nodes except first and last node  ***/
            if(ptr->next->data == dataDel){
			
                mynode = ptr;
            
				tmp = ptr->next;

                mynode->next = mynode->next->next;

                mynode->next->previous=ptr;

                delete tmp;

                num_nodes--;

                return(TRUE);

			}

            ptr=ptr->next;

		}

        if(ptr->next->next == NULL && ptr->next->data == dataDel){

			/***  Checking condition for deletion of last node  ***/
            tmp = ptr->next;

            delete tmp;

            ptr->next = NULL;

            num_nodes--;

            return(TRUE);

		}

	}

    return(FALSE);
}

// Function searching element in Priority Queue
template <typename T> 
int PriorityQueue<T>::search(const T& datasearch){

    ptr = head;

    while(ptr->next!=NULL){
	
        if(ptr->data == datasearch){
		
            return ptr->data;
		
		}//end if
        
		ptr=ptr->next;
    }
    
	if(ptr->next == NULL && ptr->data == datasearch){

		return ptr->data;
	}

    return(FALSE);

}

// Function printing elements of Priority Queue
template <typename T> 
void PriorityQueue<T>::print(void){

    ptr = head;

    cout<<"Priority Queue is as Follows:-"<<endl;

    while(ptr!=NULL){
	
        cout<<ptr->data<<endl;

        ptr=ptr->next;

	}

}

// Destructor of Priority Queue
template <typename T> 
PriorityQueue<T>::~PriorityQueue(void){

	/* tmporary variable */
    Node<T>*  tmp;                      
    
	while(head->next!=NULL){
	
        tmp = head->next;

		//    delete head;
		
        head=tmp;
    }
	
    if(head->next == NULL){
        delete head;
	}
	
}

#endif
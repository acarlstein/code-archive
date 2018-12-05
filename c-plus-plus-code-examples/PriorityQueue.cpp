
#include "PriorityQueue.h"
// First Nodes Created With Constructor

int PriorityQueue::NumOfNodes=1;

// Constructor

PriorityQueue::PriorityQueue(void){

    Current.Previous=NULL;

    cout<<"Enter First Element of Queue"<<endl;

    cin>>Current.Data;

    Current.Next=NULL;

    head=&Current;

    ptr=head;

}

// Function Finding Maximum Priority Element
int PriorityQueue::Maximum(void){

    int Temp;

    ptr=head;

    Temp=ptr->Data;

    while(ptr->Next!=NULL){
	
        if(ptr->Data>Temp){
		
            Temp=ptr->Data;
		
		}
		
        ptr=ptr->Next;
    }
	
    if(ptr->Next==NULL && ptr->Data>Temp){
     
		Temp=ptr->Data;

	}
	
    return(Temp);
}

// Function Finding Minimum Priority Element
int PriorityQueue::Minimum(void){

    int Temp;

    ptr=head;

    Temp=ptr->Data;

    while(ptr->Next!=NULL){
	
        if(ptr->Data<Temp){
		
            Temp=ptr->Data;
		
		}
        
		ptr=ptr->Next;
    
	}
    
	if(ptr->Next==NULL && ptr->Data<Temp){
	
        Temp=ptr->Data;
    
	}
	
	return(Temp);
}

// Function inserting element in Priority Queue
void PriorityQueue::Insert(int DT){

    struct Node *newnode;
    
    newnode=new Node;

    newnode->Data=DT;

    while(ptr->Next!=NULL){
    
		ptr=ptr->Next;
	
	}
    
	if(ptr->Next==NULL){
	
        newnode->Next=ptr->Next;
    
		ptr->Next=newnode;
    
	}
    
	NumOfNodes++;
}

// Function deleting element in Priority Queue
int PriorityQueue::Delete(int DataDel){

    struct Node *mynode,*temp;

    ptr=head;
    
    if(NumOfNodes == 1){
	
        cout<<"Cannot Delete the only Node"<<endl;
    
		return FALSE;
    }
	
    if(ptr->Data==DataDel){

		/***  Checking condition for deletion of first node  ***/
        temp=ptr;
		
        ptr=ptr->Next;
		
        ptr->Previous=NULL;
		
        //delete temp;
		
        head=ptr;
		
        NumOfNodes--;
		
        return(TRUE);
		
    }else{
	
        while(ptr->Next->Next!=NULL){
		
            /***  Checking condition for deletion of   ***/
            /*** all nodes except first and last node  ***/
            if(ptr->Next->Data==DataDel){
			
                mynode=ptr;
            
				temp=ptr->Next;

                mynode->Next=mynode->Next->Next;

                mynode->Next->Previous=ptr;

                delete temp;

                NumOfNodes--;

                return(TRUE);

			}

            ptr=ptr->Next;

		}

        if(ptr->Next->Next==NULL && ptr->Next->Data==DataDel){

			/***  Checking condition for deletion of last node  ***/
            temp=ptr->Next;

            delete temp;

            ptr->Next=NULL;

            NumOfNodes--;

            return(TRUE);

		}

	}

    return(FALSE);
}

// Function Searching element in Priority Queue
int PriorityQueue::Search(int DataSearch){

    ptr=head;

    while(ptr->Next!=NULL){
	
        if(ptr->Data==DataSearch){
		
            return ptr->Data;
		
		}//end if
        
		ptr=ptr->Next;
    }
    
	if(ptr->Next==NULL && ptr->Data==DataSearch){

		return ptr->Data;
	}

    return(FALSE);

}

// Function Displaying elements of Priority Queue
void PriorityQueue::Display(void){

    ptr=head;

    cout<<"Priority Queue is as Follows:-"<<endl;

    while(ptr!=NULL){
	
        cout<<ptr->Data<<endl;

        ptr=ptr->Next;

	}

}

// Destructor of Priority Queue
PriorityQueue::~PriorityQueue(void){

	/* Temporary variable */
    struct Node *temp;                      
    
	while(head->Next!=NULL){
	
        temp=head->Next;

		//    delete head;
		
        head=temp;
    }
	
    if(head->Next==NULL){
        delete head;
	}
	
}

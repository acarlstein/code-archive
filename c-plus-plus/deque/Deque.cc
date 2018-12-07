#ifndef DEQUE_CC_
#define DEQUE_CC_

#include <iostream>

using namespace std;

template <typename T> class Deque;

template <typename T>
class Node {

	private:

		// Contains the data of the linked Deque node
		T data;	

		// Contains a pointer to the previous item in the linked Deque
		Node<T> *previous;

		// Contains a pointer to the next item in the linked Deque
		Node<T> *next;

	public:

	        friend class Deque<T>;

		//The default constructor doesn't initialize the data members
		Node(void);

		// Create a linked Deque node by setting its data to the input parameter
		// and the next node in the linked Deque to NULL (0)
		Node(const T& new_data);

		Node(const T& new_data,
			 Node<T>* new_previous,
			 Node<T>* new_next);

		T get_data(void);

		Node<T>* get_previous(void);

		Node<T>* get_next(void);

		void set_data(T new_data);	 

		void set_previous(Node<T>* new_previous);

		void set_next(Node<T>* new_next);

		//The default destructor doesn't initialize the data members
		~Node(void);

};

template <typename T>
class Deque {
	private:

		int num_elements;

		// Contains a pointer to the first node in the
		// linked Deque (the head of the Deque)
		Node<T> *head;	

		// Contains a pointer to the last node in the
		// linked Deque (the head of the Deque)
		Node<T> *tail;		

	public:

		// **** Overload Operators ****

		T& operator[] (const int index);

		Deque<T>& operator= (const Deque<T>& new_deque);

		// **** Constructors ****

		// Create a Linked Deque by initializing it's head to NULL (0)
		Deque(void);

		Deque(const Deque<T>& new_deque);

		// Delete all the elements in the linked Deque when the Deque is deleted
		~Deque(void);

		// **** Get Methods ****

		bool is_empty(void) const;

		int size(void) const;

		// **** Set Methods ****

		// **** Print Methods ****

		// **** Methods ****

		void push_front(const T& new_data);

		void push_back(const T& new_data);

		void pop_front(void);

		void pop_back(void);

		T front(void) const;

		T back(void) const;

		void remove_at(int index);

		T& at(const int index);

		//erase

};

/////////////////////////////////////////////////////////
// NODE PUBLIC METHODS
///////////////////////////////////////////////////////////

// **** Constructors ****

template <typename T>
Node<T>::Node(void):
			  previous(NULL),
			  next(NULL){
}

template <typename T>
Node<T>::Node(const T& new_data):
			  data(new_data),
			  previous(NULL),
			  next(NULL){
}

template <typename T>
Node<T>::Node(const T& new_data,
			  Node<T>* new_previous,
			  Node<T>* new_next):
			  data(new_data),
			  previous(new_previous),
			  next(new_next){

}

// **** Get Methods ****
template <typename T>
T Node<T>::get_data(void){
	return data;
}

template <typename T>
Node<T>* Node<T>::get_previous(void){
	return previous;
}

template <typename T>
Node<T>* Node<T>::get_next(void){
	return next;
}

// **** set Methods ****
template <typename T>
void Node<T>::set_data(T new_data){
	data = new_data;
}

template <typename T>
void Node<T>::set_previous(Node<T>* new_previous){
	previous = new_previous;
}

template <typename T>
void Node<T>::set_next(Node<T>* new_next){
	next = new_next;
}

// **** Print Methods ****

// **** Methods ****

// **** Destructor ****

template <typename T>
Node<T>::~Node(void) {
}

/////////////////////////////////////////////////////////
// DEQUE OVERLOAD OPERATORS
///////////////////////////////////////////////////////////
template <typename T>
T& Deque<T>::operator[] (const int index){

	int i  = 0;

	Node<T>* current_node;

	if (index > -1 && index < num_elements && !is_empty()){

		// If index is between the middle and the end of the list, begin  from the end of the list
		// else
		// (index is between the middle and the begin of the list), begin from the beginning of the list
		if (index >= (num_elements / 2) ){

			current_node = tail;

			for (i = num_elements - 1;
				i > index;
				i--, current_node = current_node->previous);

		}else{

			current_node = head;

			for (i = 0;
				i < index;
				i++,current_node = current_node->next);

		}// end if

		return current_node->data;

	}else{

		//cerr << "[X] ERROR: Index out of bounds : " << index << "/" << (num_elements) << endl;

	}// end if

	return current_node->data;
}

/**
 * operator =
 * @description: deep copy deque
 * @param: new_deque
 * @return: Deque&
 */
template <typename T>
Deque<T>& Deque<T>::operator= (const Deque<T>& new_deque)
{

	num_elements = 0;

    if ( new_deque.head != NULL ){

		Node<T> *current_node = new_deque.head;

		while (current_node != NULL){

			push_back(current_node->data);

			current_node = current_node->next;

			num_elements++;
		}
	}

	// return the existing object
    return *this;
}

/////////////////////////////////////////////////////////
// DEQUE PRIVATE METHODS
///////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
// DEQUE PUBLIC METHODS
///////////////////////////////////////////////////////////

// **** Constructors ****
template <typename T>
Deque<T>::Deque(void):
		        num_elements(0),
				head(NULL),
				tail(NULL){
}

template <typename T>
Deque<T>::Deque(const Deque<T>& new_deque){

	num_elements = 0;

    if ( new_deque.head != NULL ){

		Node<T> *current_node = new_deque.head;

		while (current_node != NULL){

			push_back(current_node->data);

			current_node = current_node->next;

			num_elements++;
		}
	}
}

// **** Get Methods ****

template <typename T>
bool Deque<T>::is_empty() const{
	return((num_elements < 1));
}

template <typename T>
int Deque<T>::size() const{
	return num_elements;
}
// **** set Methods ****

// **** Print Methods ****

// **** Methods ****

template <typename T>
void Deque<T>::push_front(const T& new_data){

    Node<T> *new_node;

    if (head == NULL) {

		 new_node = new Node<T>(new_data, NULL, NULL);

		 head = new_node;

		 tail = new_node;

    } else {

		Node<T> *next_node = head;

		new_node = new Node<T>(new_data, NULL, next_node); 

		head = new_node;

		next_node->set_previous(new_node);

    }

    num_elements++;

}

// Takes an item as a parameter, appends that item to
// the back of the Deque, and returns the Deque
template <typename T>
void Deque<T>::push_back(const T& new_data){

    Node<T> *new_node;

    if (tail == NULL){

		new_node = new Node<T>(new_data, NULL, NULL);

		tail = new_node;

		head = new_node;

    } else {

		Node<T> *previous_node = tail;

		new_node = new Node<T>(new_data, previous_node, NULL);

		tail = new_node;

		previous_node->set_next(new_node);

    }// end if

    num_elements++; 

}

template <typename T>
void Deque<T>::pop_front(void){

	if (!is_empty()){

		Node<T> *new_head = head->get_next();

		if (new_head != NULL){

			new_head->set_previous(NULL);

			delete head;

			head = new_head;

			num_elements--;

		}

	}//end if

}

template <typename T>
void Deque<T>::pop_back(void){

	if (!is_empty()){

		Node<T> *new_tail = tail->get_previous();

		if (new_tail != NULL){

			new_tail->set_next(NULL);

			delete tail;

			tail = new_tail;

			num_elements--;

		} //end if

	}//end if

}

template <typename T>
T Deque<T>::front() const{
	return (head->data);
}

template <typename T>
T Deque<T>::back() const{
	return (tail->data);
}

template <typename T>
void Deque<T>::remove_at(int index){

	bool is_found = false;

    Node<T> *current_node;

	current_node = head;
	for (int i = 0; current_node != NULL && !is_found; i++){

		if (i == index){

			//Remove from beginning
			if (current_node->previous == NULL){

				head = current_node->next;

				  // Remove from the end
			}else if(current_node->next == NULL){
				current_node->previous->next  = NULL;

			}else{	//Remove from middle

				// Fix previous node's next to skip over the removed node
				current_node->previous->next = current_node->next;

				// Fix next node's previous to skip over the removed node
				current_node->next->previous = current_node->previous;

			}//end if

			delete current_node;

			is_found = true;

		}//end if 

		current_node = current_node->next;

	}//end for	 

/*
	Node<T> *new_node;

    Node<T> *current_node = head;

	bool is_node_found = false;

	for (int i = 0;
		 i < size() &&
		 current_node != NULL
		 && !is_node_found;
		 i++){

		if (i == index){

			is_node_found = true;

			if (current_node == head){

				pop_front();

			}else if (current_node == tail){

				pop_back();

			}else{

				// In order to remove the current node, we have to conect the next node with
				// the node previous to the curent node.
				new_node = current_node->next;

				new_node->set_previous(current_node->get_previous());

				delete(current_node);

				current_node = new_node;

			}//end if

			num_elements--;

		}//end if

		current_node = current_node->next;

	}//end if
*/
}

template <typename T>
T& Deque<T>::at(const int index){

	int i  = 0;

	Node<T>* current_node;

	if (index > -1 && index < num_elements && !is_empty()){

		// If index is between the middle and the end of the list, begin  from the end of the list
		// else
		// (index is between the middle and the begin of the list), begin from the beginning of the list
		if (index >= (num_elements / 2) ){

			current_node = tail;

			for (i = num_elements - 1;
				i > index;
				i--, current_node = current_node->previous);

		}else{

			current_node = head;

			for (i = 0;
				i < index;
				i++,current_node = current_node->next);

		}// end if

		return current_node->data;

	}else{

		//cerr << "[X] ERROR: Index out of bounds : " << index << "/" << (num_elements) << endl;

	}// end if

	return current_node->data;
}

// **** Destructor ****
template <typename T>
Deque<T>::~Deque(void) {

	Node<T> *next_node;

    Node<T> *current_node = head;

    while (current_node != NULL) {

       	next_node = current_node->next;

        delete(current_node);

        current_node = next_node;

		num_elements--;
    }	

}

#endif


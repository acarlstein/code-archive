#ifndef BST_CC
#define BST_CC

#include <iostream>

using namespace std;

// Forward declaration of class BST
// By fowarding the declaration, the class BST
// can access to the private data members of BSTNode
// helping to maintain the concept of encapsulation
template <typename T> class BST;

/**
 * BSTNode
 * @description:
 */
template <typename T> 
class BSTNode {
	
	// This is needed to grant class BST access 
	// to the private members of BSTNode
	// and help to maintaining the concept of encapsulation
	friend class BST<T>;

	private:	
		BSTNode<T>* pLeft;
		T data;
		BSTNode<T>* pRight;

	public:
		
	//Default Constructor
	BSTNode(void);
	
	//Constructor
	BSTNode(const T& newData);
	
	// **** Get Methods ****

	T getData() const;
	
	// **** Set Methods ****

	void setData(const T& newData);
	
	//Destructor
	~BSTNode(void);

};

//////////////////////////////////////////////////////////////////

/**
 * BST
 * @description:
 */
template <typename T> 
class BST {

	private:	
	
	int numberOfNodes;
	
	BSTNode<T> *pRoot;
	
	T insertNode(BSTNode<T> **pBSTNode,
			     const T& newData);

	T findNode(BSTNode<T> **pBSTNode,
		  	   const T& searchData);

	void displayPreOrderTraversal(BSTNode<T> *pBSTNode) const;

	void displayInOrderTraversal(BSTNode<T> *pBSTNode) const;

	void displayPostOrderTraversal(BSTNode<T> *pBSTNode) const;

	void removeAll(BSTNode<T> *pBSTNode) const;
	
	public:
		
	//Default Constructor
	BST(void);
	
	//Constructor
	BST(const T& newData);


	// **** Get Methods ****

	
	// **** Set Methods ****

	
	// **** Methods ****
	T insert(const T& newData);
	
	T find(const T& searchData);
	
	int size(void);
	
	void displayPreOrder(void) const;

	void displayInOrder(void) const;

	void displayPostOrder(void) const;

	//Destructor
	~BST(void);

};


//*****************************************************************************
//**** BSTNODE METHODS ****
//*****************************************************************************

///////////////////////////////////////////////////////////////////////////////
//**** BSTNODE PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**** BSTNODE PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

template <typename T>
BSTNode<T>::BSTNode(void){
	//cout << endl << "[Default BSTNode]" << endl;
}

template <typename T>
BSTNode<T>::BSTNode(const T& newData):
					  pLeft(NULL), 
					  data(newData),
					  pRight(NULL){
//	cout << endl << "[BSTNode]" << endl;
}

// **** Get Methods ****

/**
 * 
 */
template <typename T>
T BSTNode<T>::getData() const{
	return data;
}
	
// **** Set Methods ****

template <typename T>
void BSTNode<T>::setData(const T& newData){
	data = newData;
}

template <typename T>
BSTNode<T>::~BSTNode(void){
//	cout << endl << "[~BSTNode(X)]" << endl;
}

//*****************************************************************************
//**** BST METHODS ****
//*****************************************************************************

///////////////////////////////////////////////////////////////////////////////
//**** BST PRIVATE METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 *
 */
template <typename T>
T BST<T>::insertNode(BSTNode<T> **pBSTNode,
			 		 const T& newData){
	
	// If subBST is empty then
	// create new BSTNode for the value
	if (*pBSTNode == NULL){
	
		*pBSTNode = new BSTNode<T>(newData);
		
		numberOfNodes++;
		
		return newData;
		
	}else{
		
		// If the data is not duplicated
		if (newData != (*pBSTNode)->data){
	
			// if newData is less than the current node's data
			// then insert a left BSTNode with newData
			// else insert a right BSTNode with newData
			if (newData < (*pBSTNode)->data ){
			
				insertNode( &( ( *pBSTNode) -> pLeft), newData);		
		
			}else{
			
				insertNode( &( ( *pBSTNode) -> pRight), newData);		
				
			}
		}else{
		
			T rtnT;
			
			return rtnT;
		}
			
	}	
}

/**
 *
 */
template <typename T>
T BST<T>::findNode(BSTNode<T> **pBSTNode,
	  	   		   const T& searchData){

	T rtnT;

	// If subBST is empty 
	if (*pBSTNode == NULL){
	
		// Object not found 
					
		return rtnT;
		
	}else{
		

		// If the data is not found
		// Keep searching
		if (searchData != (*pBSTNode)->data){
					
			// if newData is less than the current node's data
			// then insert a left BSTNode with newData
			// else insert a right BSTNode with newData
			if (searchData < (*pBSTNode)->data ){
							
				rtnT = findNode( &( ( *pBSTNode) -> pLeft), searchData);		
						
			}else{
			
				rtnT = findNode( &( ( *pBSTNode) -> pRight), searchData);		
				
			}

		}else{
	
			rtnT = (*pBSTNode)->data;
		}
			
	}	

	return rtnT;
}

/**
 *
 */
template <typename T>
void BST<T>::displayPreOrderTraversal(BSTNode<T> *pBSTNode) const{

	if (pBSTNode != NULL){

		// Process Node
		cout << pBSTNode->data << " ";
		
		// Traverse left subBST
		displayPreOrderTraversal(pBSTNode->pLeft);
		
		// Traverse right subBST
		displayPreOrderTraversal(pBSTNode->pRight);

	}
}

/**
 *
 */
template <typename T>
void BST<T>::displayInOrderTraversal(BSTNode<T> *pBSTNode) const{

	if (pBSTNode != NULL){
		
		// Traverse left subBST
		displayInOrderTraversal( pBSTNode->pLeft);

		// Process Node
		cout << pBSTNode->data << " ";
		
		// Traverse right subBST
		displayInOrderTraversal( pBSTNode->pRight);

	}

}

/**
 *
 */
template <typename T>
void BST<T>::displayPostOrderTraversal(BSTNode<T> *pBSTNode) const{

	if (pBSTNode != NULL){
		
		// Traverse left subBST
		displayPostOrderTraversal(pBSTNode->pLeft);
		
		// Traverse right subBST
		displayPostOrderTraversal(pBSTNode->pRight);

		// Process Node
		cout << pBSTNode->data << " ";

	}

}

/**
 *
 */
template <typename T>
void BST<T>::removeAll(BSTNode<T> *pBSTNode) const{

	if (pBSTNode != NULL){
		
		// Traverse left subBST
		removeAll(pBSTNode->pLeft);
		
		// Traverse right subBST
		removeAll(pBSTNode->pRight);

		delete pBSTNode;

	}

}


///////////////////////////////////////////////////////////////////////////////
//**** BST PUBLIC METHODS ****
///////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
template <typename T>
BST<T>::BST(void){
	//cout << endl << "[Default BST]" << endl;
	pRoot = NULL;
	numberOfNodes = 0;
}

/**
 * 
 */
template <typename T>
BST<T>::BST(const T& newData){
	//cout << endl << "[BST]" << endl;
	numberOfNodes = 0;
}

// **** Get Methods ****

// **** Set Methods ****

// **** Methods ****

/**
 *
 */
template <typename T>
T BST<T>::insert(const T& newData){
	return insertNode( &pRoot, newData);
}


/**
 *
 */
template <typename T>
T BST<T>::find(const T& searchData){
	
	//cout << endl << "[find : " << searchData << "]" << endl;

	return findNode( &pRoot, searchData);
}

/**
 *
 */
template <typename T>
int BST<T>::size(void){
	return numberOfNodes;
}


/**
 *
 */
template <typename T>
void BST<T>::displayPreOrder(void) const{
	displayPreOrderTraversal( pRoot );
}
	
/**
 *
 */
template <typename T>
void BST<T>::displayInOrder(void) const{
	displayInOrderTraversal( pRoot );
}

/**
 *
 */
template <typename T>
void BST<T>::displayPostOrder(void) const{
	displayPostOrderTraversal( pRoot );
}

/**
 * 
 */
template <typename T>
BST<T>::~BST(void){
	
	cout << endl << "[~BST(X)]" << endl;

//	removeAll(pRoot);
	
}


#endif

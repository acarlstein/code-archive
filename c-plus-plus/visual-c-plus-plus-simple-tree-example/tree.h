tree.h:

#ifndef tree_h

#define tree_h

#include "standard.h"

struct nodeType

{

	int value;

};

struct treeType

{

	nodeType  data;

    treeType* left;

	treeType* right;

};

typedef treeType* treePtr;

class TreeClass

{ 

	private:

		treePtr root;

		//Insert the node in ascending order

		void InsertNode ( treePtr& ptr,

		                  nodeType aNode );

		//Create memory, insert data into a tree node

		treePtr GetANode ( nodeType ANode );

		//Delete a leaf node from a tree, free the memory

		void DeleteLeaf( treePtr location, 

					     treePtr& parent );

		//Delete a node with one left child only

		void DeleteLeft ( treePtr location,

					      treePtr& parent );

		//Delete a node with one right child only

		void DeleteRight ( treePtr location,

						   treePtr& parent );

		//Delete a node that has two children

		void DeleteTwoChildren( treePtr& location );

		//Called recursively to visit each node in the tree InOrder

		void InOrder ( ofstream& fout,

			           treePtr ptr );

		//Called recursively to visit each node in the tree PreOrder

		void PreOrder ( ofstream& fout,

			            treePtr ptr );

		//Called recursively to visit each node in the tree PostOrder

		void PostOrder ( ofstream& fout,

			             treePtr ptr );

		//Count the nodes in the tree

		void CountNodes ( treePtr ptr,

			              int& count );

	public:

		//Constructor

		TreeClass( void );

		//Create a tree from an input file

		void CreateATree ( ifstream& fin );

		//Return a bool based on value of root

		bool EmptyTree() const;

		//Print Tree content to an output file

		void PrintTree ( ofstream& fout );

		//Count the nodes in a tree

		int CountNodesInTree ( void );

		//Delete a node in the tree, return success of delete

		bool Delete ( int num );

		//Insert a node in Order in a tree

		void Insert ( nodeType node );

		//Print tree in PreOrder

		void PrintPreOrder ( ofstream& fout );

		//Print tree in PostOrder

		void PrintPostOrder ( ofstream& fout );

		//Search the tree for a num, return the node, the parent and a flag

		void Search ( treePtr& ptr,

			          treePtr& parent,

					  int num,

					  bool& success );

		//The destructor, free the memory

		~TreeClass ( void );

};

#endif


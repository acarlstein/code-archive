mainTree.cpp:

#include "standard.h"
#include "tree.h"

using namespace std;

//Print the divider to the specified file
void PrintDivider ( ofstream& fout,
				    char symbol,
					int numOfSymbols,
					int section );

//Print the count to the specified file
void PrintCount ( ofstream& fout,
				  int count );

int main(void)
{
	//declare the files
	ifstream fin;
	ofstream fout;

	//Set the task number to -1
	int section = -1;

	//Open the files
	fin.open("tree.txt");
	fout.open("treeOut.txt");

	//Create an instance of the class
	TreeClass tree;

	//Declare variables
	int numOfNodesInTree;

	//print empty tree message
	tree.PrintTree ( fout );
	PrintDivider ( fout,
		           '*',
				   63,
				   section++);

	//Insert values from the input file
	tree.CreateATree ( fin );

	//Print the tree nodes on one line
	tree.PrintTree ( fout );
	PrintDivider ( fout,
		           '*',
				   63,
				   section++);

	//Calculate the number of nodes in the tree
	numOfNodesInTree = tree.CountNodesInTree();

	//Print the count
	PrintCount ( fout,
		         numOfNodesInTree );
	fout << endl;

	//Close the files
	fin.close();
	fout.close();

	return 0;
}

//Print the divider to the specified file
void PrintDivider ( ofstream& fout,
				    char symbol,
					int numOfSymbols,
					int section )
{
	fout << endl << endl;
	fout << "#" << setw(2)<< section << BLANK;
	fout.fill( symbol );
	fout << setw( numOfSymbols ) << BLANK;
	fout << endl;
	fout.fill( BLANK );
	fout << setw(3)<<BLANK;

}

//Print the count to the specified file
void PrintCount ( ofstream& fout,
				  int count )
{
	fout << " Number of Nodes currently in the tree are: "
		 << count << endl;

}

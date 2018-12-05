//StreamOperation.h:

#ifndef STREAM_OPERATION_H
#define STREAM_OPERATION_H

#include <iostream>		// for cout

#include <fstream>		// for ifstream, ofstream

#include <string>       // for String
#include <cctype>       // for classify and transform individual characters

using namespace std;

/**
 * author: Alejandro G. Carlstein
 * Class: StreamOperation
 * Description: This class will read a textfile and produce an output
 *				in another text file. The other text file will contain
 * 				a copy of the input file but all blank lines will be
 *				removed, the lines are going to be numbered, all
 *              semicolons will be replaces with the string 'SEMI-COLON',
 *				print the number of lines removed at the second to last
 *              line, and finally print the number of alphabetic characters
 */
class StreamOperation {

private:   

	bool doRemoveBlankLines;

	bool doReplaceAllStrings;

	bool doCountLines;	

	int numLinesRemoved;

	int numAlphaCharacters;

	string oldStr;

	string newStr;

	void replaceAll(string& str,
					string oldStr,
					string newStr);

	int countAlphaCharacters(string str);

	void copyStream(ifstream& fin,
			  		ofstream& fout);

public:

	// Default constructor
	StreamOperation(void);

	// * Get Methods *

	// Get the number of lines removed
	int getNumberLinesRemoved();

	// Get the number of alphabetic character
	int getNumberAlphaCharacters();

	// * Set Methods * 	

	// * Print Methods *

	// Print the number of blank lines removed
	void printNumberLinesRemoved(ofstream& output);		

	// Print the number of alphabetic characters
	void printNumberAlphaCharacters(ofstream& output);		

	// * Process Methods *

	// Copy the content from an input stream to an output stream
	void copy(ifstream& input,
			  ofstream& output);	

	// Copy the content from an input stream to an output stream.
    // This method can remove all the blank lines in the output
    // stream when copying.
	void copy(ifstream& input,
			  ofstream& output,
			  bool removeBlankLines);

	// Copy the content from an input stream to an output stream.
	// This method can remove all the blank lines in the output
 	// stream when copying.
	// This method can number all the lines in the output stream.
	void copy(ifstream& input,
			  ofstream& output,
			  bool removeBlankLines,
              bool numberLines);

	// Copy the content from an input stream to an output stream.
	// This method can replace all old strings for a new string
	// This method can remove all the blank lines in the output
 	// stream when copying.
	// This method can number all the lines in the output stream.
	void copy(ifstream& input,
			  ofstream& output,
              string oldString,
			  string newString,
			  bool removeBlankLines,
			  bool numberLines);

    // Default destructor
	~StreamOperation(void);
};

#endif


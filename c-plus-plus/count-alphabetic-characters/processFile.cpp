processFile.cpp:

/**
 * Author: Alejandro G. Carlstein
 * Description: Use the file StreamOperations.cpp as an input file
 *				and process it using StreamOperation class
 */

#include <iostream>
#include <fstream>
#include "StreamOperation.h"

static const string INPUT_FILE = "StreamOperation.cpp";
static const string OUTPUT_FILE = "Output.txt";
static const string SEMI_COLON = ";";
static const string STR_SEMI_COLON = "SEMI-COLON";

/**
 * Main function
 * @param: argc, argv
 */

int main(int argc, char *argv[]){

	ifstream inputFile;
	ofstream outputFile;

	// If the program is executed with two parameters (file 1  and file 2)
    // used these parameters as input file and output file
	// If the program is executed without parameters use default files
    // If the program is executed with the -h parameter display help
	// If the program get more than two parameters or
    // wrong key display help
	if (argc == 1 || argc == 3){

		if (argc == 1){

			inputFile.open(INPUT_FILE.data());

			outputFile.open(OUTPUT_FILE.data());	

		}else{

			inputFile.open(argv[1]);

			outputFile.open(argv[2]);
		}

		StreamOperation StrOp;

		// Copy the content from the input file to the output file
	    // In the process, replace the ; with string SEMI-COLON,
		// remove the blank lines and number all the lines
		StrOp.copy(inputFile,
				   outputFile,
				   SEMI_COLON,
				   STR_SEMI_COLON,
				   true,
	               true);

		outputFile << "Lines Removed: "
				   << StrOp.getNumberLinesRemoved() << endl;

		outputFile << "Alphabetic Characters: "
				   << StrOp.getNumberAlphaCharacters();

		inputFile.close();

		outputFile.close();

	} else {
		cout << argv[0] << " input_file output_file " << endl;
	}	

	return 0;
}

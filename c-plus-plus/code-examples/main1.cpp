/**
 * @author: Alejandro G. Carlstein
 * @course: cs240
 * @description: War Game
 */
#include <iostream>
#include <fstream>
#include <string>

#include "WarMachine.h"

int main(int argc, char *argv[]){

	WarMachine warMachine;
	
	srand(time(NULL));

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	string str_player_name;
	
	if (fin.is_open() && fout.is_open()){
	
		// Add players names
		while (getline(fin, str_player_name)){
			warMachine.add_player(str_player_name);
		}
	
		if (!warMachine.start()){
		
			warMachine.print_log(fout);			
							
			warMachine.print_statistics((ofstream&) cout);

		}	
	}else{
		cerr << "[X] ERROR: Cannot open files" << endl;
	}
	
	fin.close();
	
	fout.close();
	return 0;
}

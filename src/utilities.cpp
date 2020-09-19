/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

vector<process_stats> stats;

bool compareProcessStats(const process_stats& b1,  const process_stats& b2) {
	return b1.process_number < b2.process_number;
}
bool compareCPUStats(const process_stats& b1,  const process_stats& b2) {
	return b1.cpu_time < b2.cpu_time;
}
bool compareStartStats(const process_stats& b1,  const process_stats& b2) {
	return b1.start_time < b2.start_time;
}
bool compareIOStats(const process_stats& b1,  const process_stats& b2) {
	return b1.io_time < b2.io_time;
}
//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	stats.clear();
	ifstream inputfile;
	inputfile.open(filename);

	if (!inputfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	string token;
	stringstream ss;


	if (ignoreFirstRow == true) {
		getline(inputfile, line);
	}

	while (!inputfile.eof()) {

		getline(inputfile, line);
		ss.str(line);
		process_stats stat;

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		stat.process_number = atoi(token.c_str());

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		stat.start_time = atoi(token.c_str());

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		stat.cpu_time = atoi(token.c_str());

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		stat.io_time = atoi(token.c_str());

		stats.push_back(stat);

		ss.clear();

	}
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder) {
	case PROCESS_NUMBER:
		sort(stats.begin(), stats.end(), compareProcessStats);
		break;
	case CPU_TIME:
		sort(stats.begin(), stats.end(), compareCPUStats);
		break;
	case IO_TIME:
		sort(stats.begin(), stats.end(), compareIOStats);
		break;
	case START_TIME:
		sort(stats.begin(), stats.end(), compareStartStats);
		break;
	}

}

process_stats getNext() {
	process_stats myFirst;
	stats.erase(stats.begin());
	myFirst = stats.front();
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}



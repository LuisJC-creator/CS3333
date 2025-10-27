/**************************************************************************
Class:			CSCI 3333.01 Data Structures and Algorithms
				Spring 2025
Project 3:		Finding Common Patterns from Large Text Documents
Name:			Coder Warrior
ID:             11111111
Description: use some combination of hash maps, lists, and sorting techniques 
	to discover the most common phrases and common paragraphs between two 
	large text documents: The King James version of the bible and 
	the Complete Works of William Shakespeare. 
Input file: bible.txt, WilliamShakespeare.txt
Output file: topPhrases.txt
Example format of output file:
	top 10 most frequent phrases of length 1
	phrase  		frequency in Bible		frequency in William Shakespeare
	trout			100						150
	snapper 		600						95	
	......
	top 10 most frequent phrases of length 2
	phrase  		frequency in Bible		frequency in William Shakespeare
	speckled trout	100						150
	red snapper 	600						95
	......
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	time used: xxx seconds
**************************************************************************/

#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <utility>
#include <time.h>
#include <windows.h>

//define the needed parts in the header file
#include "project3_head.h"

using namespace std;

int main()
{
	ifstream myfile;  //input file variable
	istringstream ss; //string stream input
	ofstream outfile; //output file variable

	map<string, int> bk1, bk2; //hash maps to store all phrases with frequencies
	map<string, int>::iterator it; //iterator to iterate through a map
	vector<myPhraseType> topPhrases[10]; //top 10 lists of phrase of length 1 to 10
	unsigned int i, j, k, cnt, num;
	string str, tmp, np;
	myPhraseType p; //this is defined the header file
	vector<string> words(10000);
	time_t start, end; //to record needed.

	//record the start time
	start = time(NULL);
	//load phrases into bk1
	cout << "loading the Bible ...... " << endl;
	myfile.open("bible.txt"); 
	bk1.clear();
	while (!myfile.eof()){
		//read a sentense str ended with a punctuation
		//convert to lower case
		// .....
		
		//find all phrases with 1 to 10 words from str
		//basically, you can use a three-layered nested loop
		//or a sliding window way with length from 1 to 10 
		//to extract all phrases with 1 to 10 words from str. 
		//use the map to record the frequencies of the phrases.
		//......		
	}
	myfile.close();
	cout << "finished loading the Bible. " << endl;

	//load pharses into bk2
	cout << "loading the Complet Work of William Shakespeare ...... " << endl;
	myfile.open("WilliamShakespeare.txt"); 
	bk2.clear();
	while (!myfile.eof()){
		//read a sentense str ended with a punctuation
		//convert to lower case
		// .....

		//find all phrases with 1 to 10 words from str
		//basically, you can use a three layered nested loop
		//or a a sliding window way with window length from 1 to 10 
		//to extract all phrases with 1 to 10 word from str. 
		//use the map to record the frequencies of the phrases.
		//......		
	}
	myfile.close();
	cout << " finished loading William Shakepeare " << endl;
	
	//Use the two maps to find top phrases with 1 to 10 words.
	cout << "finding top phrases ......" << endl;
	//.....
	
	//Now output the top pharses 
	ofstream outfile("topPhrases.txt");
	//......

	
	//record the end time
	end = time(NULL);
	//record the time to complete the work
	outfile << endl << "+++++++++++++++++++++" << endl;
	outfile << "time used: " << difftime(end, start) << " seconds" << endl;
	outfile.close();

	//Complete the work
	return 1;
}

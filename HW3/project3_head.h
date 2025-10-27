/**************************************************************************
Class:			CSCI 3333.01 Data Structures and Algorithms
				Spring 2025
Project 3:		Finding Common Patterns from Large Text Documents
Name:			Coder Warrior
ID:             11111111
Description:	In this header file for Project 3, we define myPhraseType, 
				and several functions. 
**************************************************************************/

#ifndef HW2
#define HW2

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>

using namespace std;

//find number of words in a string
int findNumOfWords(string str)
{
	//do the work
}

//take non-ASCII characters out of a string 
void takeOutStangers(string& str)
{
	//do the work
}

//convert to lower case and take off extra non-alpha or non-number characters
void clean(string& str)
{
	//do the work
}

//define myPhraseType
class myPhraseType
{
private:
	string str;			//save a phrase with/without spaces
	int count;			//save frequency of the phrase
	int numOfWords;		//save number of words in the phrase	

public:
	bool operator<=(myPhraseType& p);
	bool operator<(myPhraseType& p);
	bool operator==(myPhraseType& p);
	void setPhrase(string s, int c);
	myPhraseType& operator=(const myPhraseType& p);
	myPhraseType();
	myPhraseType(const myPhraseType& p);
	int getNumOfWords() { return numOfWords; }
	int getFreq() { return count; }
	string getPhrase() { return str; }
	void clear() { str.clear(); count = numOfWords = 0; }
};
//define all the methods for myPhraseType
//do the work


}

//insert a phrase into a vector of at most 10 myPhraseType objects and keep the vector 
//in descending order. 
void insertPhrase(vector<myPhraseType>& list, myPhraseType& p)
{
	//do the work
}

#endif

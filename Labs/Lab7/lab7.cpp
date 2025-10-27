// *********************************************************************************
// Class:		CSCI 3333
// Lab 7:		Merge Sort
// Comment:		The code here is meant to be revised.
//----------------------------------------------------------------------------------
// Description: This file contains the prototype of the class arrayListType with 
// two versions of merge-sort algorithm: the recursive one and the iterative one. 
// simple sorting algorithms of insertion sort, selection sort and bubble sort
// also included. 
//
// Since we have implemented the array based list, we can choose to add a new set of 
// searching and sorting methods into it:
//	
// Search methods include linear search, randomized search, and binary search.
//
// sorting methods include bubble sort, selection sort, insertion sort, 
// and two versions of merge sort (the recrusive one and the iterative one). 
// 
// Compile and run your program. When everything is fine,
// print your .h and .cpp files and turn them to me or the TA.
// ***********************************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>

#include "lab7head.h"				


using namespace std; 

int main()
{
	/**********************************************************
	 Part A: Some practice
	 **********************************************************/
	//var decarations
	unsigned int seed;					//a random seed
	int num;							//to hold an int value
	arrayListType<int> list(100);		//create a list of int type
	char tag; 
	
	cout<<"loading the list with random numbers between 0 and 666 ... "<<endl; 

	cout<<"Enter a random seed => ";	//get the random seed
	cin >> seed; 
	srand(seed);						//set the randon seed

	for (int i=0; i < 45; i++)			//insert 50 random numbers into the list
	{
		num = rand()%41; 
		list.insertLast(num);
	}
	list.print(); 
	cout<<endl; 
	
	//list.insertionSort(); 
	//list.bubbleSort(); 
	//list.selectionSort(); 
	
	cout<<"Want to use recursive merge Sort (r) or iterative merge sort (i) => "; 
	cin>>tag; 
	switch(tag)
	{
	case 'r':
	case 'R':	cout<<"calling recusing merge sort .... "<<endl; 
				list.recursiveMergSort();
				break; 
	case 'i':
	case 'I':
				cout<<"calling iterative merge sort ....."<<endl; 
				list.iterativeMergeSort(); 
	default: 
				cout<<"entered a wrong choice"<<endl;
	}

	cout<<"after sorting, the list is ....."<<endl; 
	cout<<list<<endl; 

	/*while(true)
	{
		cout<<"Enter a number to search or stop when -99 is entered => "; 
		cin >> num;
		if(num == -99)					//break when the event/sentenel -99 happened
			break; 
		list.binSearch(num);			//do binary search
	} 
	*/
	/***************************************************************
	 Part B: Try to create a list of strings and practice 
	 both recursive merge sort and the iterative merge sort.
	 ***************************************************************/
	
	//Write your code here

	/*****************************************************************************
	 Part C: First define a personType class with three data members 
	 (string name, int ID, and double grade). Second, create a list
	 of personType. Third, both recursive merge sort and the iterative merge sort.
	 *****************************************************************************/
	
	//Write your code here


	//complete the program
	return 0; 
}
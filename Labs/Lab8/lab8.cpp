// ********************************************************************************
// Class:		CSCI 3333
// Lab 8:		Quick Sort
// Comment:		The code here is meant to be revised.
//----------------------------------------------------------------------------------
// Description: This file contains the prototype of the class arrayListType with 
// two versions of quick-sort algorithm: the recursive one and the iterative one. 
// Simple sorting algorithms of insertion sort, selection sort and bubble sort
// are included. Two versions (recursive and iterative) merge sort algorithms are 
// also included. 
//
// Since we have implemented the array based list, we can choose to add a new set of 
// searching and sorting methods into it:
//	
// Search methods include linear search, randomized search, and binary search.
//
// sorting methods include bubble sort, selection sort, insertion sort, 
// two versions of merge sort (the recrusive one and the iterative one), 
// and two versions of quick sort (the recrusive one and the iterative one).
// 
// Compile and run your program. When everything is fine,
// print your .h and .cpp files and turn them to me or the TA.
// ***********************************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>

#include "lab8head.h"


using namespace std; 

int main()
{
	/**********************************************************
	 Part A: Some practice
	 **********************************************************/
	//var decarations
	unsigned int seed;					//a random seed
	int num;							//to hold an int value
	arrayListType<int> list(1000);		//create a list of int type
	char tag; 
	
	cout<<"loading the list with random numbers between 0 and 666 ... "<<endl; 

	cout<<"Enter a random seed => ";	//get the random seed
	cin >> seed; 
	srand(seed);						//set the randon seed

	for (int i=0; i <500 ; i++)			//insert 50 random numbers into the list
	{
		num = rand()%501; 
		list.insertLast(num);
	}
	list.print(); 
	cout<<endl; 
	
	//list.insertionSort(); 
	//list.bubbleSort(); 
	//list.selectionSort(); 
	

	cout<<"Want to use recursive quick Sort (r) or iterative quick sort (i) => "; 
	cin>>tag; 
	switch(tag)
	{
	case 'r':
	case 'R':	cout<<"calling recursive quick sort .... "<<endl; 
				list.recursiveMedian3QuickSort();
				break; 
	case 'i':
	case 'I':
				cout<<"calling iterative quick sort ....."<<endl; 
				list.iterativeMedian3QuickSort(); 
				break; 
	default: 
				cout<<"entered a wrong choice"<<endl;
	}

	cout<<"after sorting, the list is ....."<<endl; 
	cout<<list<<endl; 


	/***************************************************************
	 Part B: Try to create a list of strings and practice 
	 both recursive quick sort and the iterative quick sort.
	 ***************************************************************/
	
	//Write your code here

	/*****************************************************************************
	 Part C: First define a personType class with three data members 
	 (string name, int ID, and double grade). Second, create a list
	 of personType. Third, both recursive quick sort and the iterative quick sort.
	 *****************************************************************************/
	
	//Write your code here


	//complete the program
	return 0; 
}
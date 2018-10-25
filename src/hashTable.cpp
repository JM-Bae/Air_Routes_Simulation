// CS_302 Section 1001
// Assignment 11
// Junho Bae
// Due: 04-25-17
// hashTable implementation file
// Description: Creates a hash table data structure consisting of general hash fucntions.

#include "hashTable.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
using namespace hasht;

hashTable::hashTable()
// default constructor
// creates and intializes the hash table to a emtpy state
{
	flightHash = new string*[hashSize];
	for(unsigned int i=0; i<hashSize; i++)
		flightHash[i] = new string[2];
}

hashTable::~hashTable()
// destructor
// deallocates the dynamically allocated memory
{
	for(unsigned int i=0; i<hashSize; i++)
		delete [] flightHash[i];
	delete [] flightHash;
	flightHash = NULL;

	delete [] ALindex;
	ALindex = NULL;
}

bool hashTable::insert(const string code, const string name)
// attempts to insert the passed key into the hash table.
// if successful, return true.
// parameters: 3 letter airport code, and full airport name
{
	// determines table location 
	unsigned int location = hash(code);

	if(flightHash[location][0].empty())
	{
		flightHash[location][0] = code;
		flightHash[location][1] = name;
	}
	return true;
}

void hashTable::setALindex()
// sets the indices of the Adjacency List
{
	ALindex = new unsigned int[hashSize];
	unsigned int j = 0;
	for(unsigned int i=0; i<hashSize; i++)
		if(!flightHash[i][0].empty())
			ALindex[i] = j++;
		
	// exception for the purpose of the assignment
	flightHash[hash("PSZ")][0] = "";
}	

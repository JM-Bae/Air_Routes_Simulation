// CS_302 Section 1001
// Assignment 11
// Junho Bae
// Due: 04-25-17
// hashTable header file

#ifndef hashTable_h
#define hashTable_h

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
namespace hasht
{

	class hashTable
	{
	public:
		hashTable();	// default constructor
		~hashTable();	// destructor
		bool insert(const string, const string); // inserts airport code and full name

		// looksup full name of the passed aiport code
		void lookup(const string code, string &name)
		{
			name = flightHash[hash(code)][1];	
		};

		// returns the index of Adjacency List
		unsigned int getIndex(const string code)
		{
			return  ALindex[hash(code)];
		};

		// returns true if the airport exists
		bool find(const string code)
		{
			if(flightHash[hash(code)][0] != "")
				return true;
			else
				return false;
		};

		// called after filling up the Table to set Adjacency List indices
		void setALindex();

	private:
		// hash function determining the location of the hash table
		unsigned int hash(string str) const
		{
		  static unsigned int asso_values[] =
		    {
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858,  2585,    10,    15,    41, 17404,
		      23259,  6734,  5855, 14703, 19321,  1700,   150,     5, 10627, 14847,
		         20,  7830,  3821,     0,    25, 32024, 30324, 28974,   510,  7725,
		      13752, 76858, 76858,     5,    15,    10,     0,     5,    15,    10,
		          5, 76858,     5,     0, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858,    30,   785,   256, 10057,    60, 29604,  3633,   283,    90,
		      19996,  2746,  5180,     3,  8040,     0, 11612, 11583,  4290,  1945,
		       1665,   120, 13438, 32324,  4922, 16072, 23324,   635,  6841,  8622,
		        250,    23,  2349,  7620,  3545,  3915, 28589,  7403,   351,  1498,
		          0,  2563, 14114, 32129,  1465,   845,  1090,   470, 17944, 23554,
		      16819, 13332, 23994, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858,
		      76858, 76858, 76858, 76858, 76858, 76858, 76858, 76858
		    };
		  return asso_values[(unsigned char)str[2]+72] + asso_values[(unsigned char)str[1]+46] + asso_values[(unsigned char)str[0]];
		};	
			
		string **flightHash;	// hash table pointer
		unsigned int *ALindex;
		static constexpr unsigned int hashSize = 77000;
	};

}
#endif
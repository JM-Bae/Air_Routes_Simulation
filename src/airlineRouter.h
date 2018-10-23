// CS_302 Section 1001
// Assignment 11
// Junho Bae
// Due: 04-25-17
// Airline Router Class header file

#ifndef airlineRouter_h
#define airlineRouter_h

// includes and prototypes
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "hashTable.h"

using namespace std;
using namespace hasht;
namespace aRout
{	
	class airlineRouter
	{
	public:
		airlineRouter();	// default constructor
		~airlineRouter();	 // destructor
		// checks if airport exists
		bool checkAirportCode(const string code)
		{
			if(airports.find(code))
				return true;
			else
				return false;
		};
		// reads in airport data
		bool readAirports(const string);
		// reads in flight data
		bool readFlights(const string);
		// prints results of the flight
		void showGraphStats() const;
		// finds the fastest arrival time to an airport
		void findFlights(const string, const string, const int);
						
	private:
		struct flightNode
		{
			string code;
			string from;
			string to;
			int depart;
			int arrive;
			flightNode *next;
		};

		void newGraph(int);		// allocates and initializes adjacency list
		void addEdge(flightNode&);		// adds an edge to the adjacency list
		void dijkstraSP(int, int);	// implements Dijkstra's algorithm to find shortest path 
		void showPath(const int);		// recursively prints the path of 2 nodes
		void destroyGraph();		// deletes all dynamically allocated memory 


		static constexpr unsigned int graphSize = 5500;

		hashTable airports;
		int vertexCount;		// vertex Count of current graph
		int edgeCount;			// edge count of graph

		flightNode *graphList;		// adjacency list data
		int *dist;					// distance array used for dijkstra's algorithm
		flightNode *prev;			// previous node array used for dijkstra's algorithm 
		bool graph; // bool for check is graph data exists
	};
}
#endif // airlineRouter_h
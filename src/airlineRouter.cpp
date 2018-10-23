// CS_302 Section 1001
// Assignment 11
// Junho Bae
// Due: 04-25-17
// Airline Router Class implementation file

#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

#include "airlineRouter.h"
#include "priorityQueue.h"
#include "hashtable.h"

using namespace std;
using namespace pQue;
using namespace aRout;
using namespace hasht;

airlineRouter::airlineRouter()
// default constructor
// newGraph function called to allocate & initialize adjacency matrix
{
	// initialize class variables to an empty state
	graphList = NULL;
	vertexCount = 0;
	edgeCount = 0;
	dist = NULL;
	prev = NULL;
	graph = false;
}

airlineRouter::~airlineRouter()
// destructor
// deletes dynamically allocated memory & resets all variables to empty state
{
	// delete dynamically allocated memory
	destroyGraph();
	// resets class variables
	vertexCount = 0;
	edgeCount = 0;
}

bool airlineRouter::readAirports(const string filename)
// reads a formatted graph file and creates a new graph.
// parameters: name of the input file
{
	ifstream infile(filename.c_str()); // attempts to open file
	if(!infile) // if file does not exists, output error message
		return false;
	else 
	{
		string str, name, code;
		getline(infile,str);

		while(!infile.eof() && str.length() > 1) // updates hash table with file data
		{
			name = str.substr(0,55);

			int loc = 111;
			code = str.substr(111,3);

			while(code[0] == ' '){
				code = str.substr(++loc, 3);
			}

			airports.insert(code, name);
			vertexCount++;
			getline(infile,str); 
		}
		infile.close(); // closes file
		airports.setALindex();
	}
	return true; // returns true if successful 
}

bool airlineRouter::readFlights(const string filename)
// reads a formatted graph file and creates a new graph.
// parameters: name of the input file
{
	ifstream infile(filename.c_str()); // attempts to open file
	if(!infile) // if file does not exists, output error message
		return false;
	else 
	{
		string str, code, from, depart, to, arrive;
		flightNode flight;
		graph = true;
		newGraph(graphSize);	// creates new graph
		getline(infile,str);  

		while(!infile.eof() && str.length() > 1) // updates hash table with file data
		{
			flight.code = str.substr(0,6);
			flight.from = str.substr(8,3);
			flight.depart = stoi(str.substr(12,4));
			flight.to = str.substr(19,3);
			flight.arrive = stoi(str.substr(23,4));
			addEdge(flight);
			getline(infile,str); 
		}
		infile.close(); // closes file
	}
	return true; // returns true if successful 
}

void airlineRouter::findFlights(const string from, const string to, const int start)
// uses modified dijkstra's SP algorithm to find the shortest arrival time
// parameters: from, to, and earliest flight time
{
	string str;
	int index = airports.getIndex(from);
	if(graphList[index].next == NULL)
		cout << endl << "No flights from " << from << endl << endl;
	else
	{
		cout << endl;
		dijkstraSP(index, start);
		cout << "--------------------------------------------" << endl;
		cout << "From / To" << endl;
		airports.lookup(from, str);
		cout << "  " << from << " - " << str << endl;
		airports.lookup(to, str);
		cout << "  " << to << " - " << str << endl << endl;

		index = airports.getIndex(to);
		if(dist[index] < std::numeric_limits<int>::max())
			showPath(index);
		else
			cout << "  " << to << " is not reachable from " << from << "." << endl << endl;
	}

}

void airlineRouter::showGraphStats() const
// prints graph stats.
// no parameters
{
	cout << "Graph Statistics:" << endl;
	cout << "   Nodes: " << vertexCount << endl;
	cout << "   Edges: " << edgeCount << endl << endl;
}

// Private Functions -----------------------------------------

void airlineRouter::newGraph(int size)
// allocate and initialize the adjacency list as empty
// parameters: size of the adjacency list
{
	// checking if graph data exists
	if(graph == true)
	{
		// ensure that there is no memory leak
		destroyGraph();
		// creates adjacency matrix 
		graphList = new flightNode[size];

		// initialize as empty state
		for(int i=0; i<size; i++)
			graphList[i].next = NULL;
	}
	else
		cout << "newGraph: Error, graph data does not exist." << endl;
}

void airlineRouter::addEdge(flightNode &newflight)
// adds an edge to the adjacency list
// parameters: flight node
{
	flightNode *flight = new flightNode;

	flight->code = newflight.code;
	flight->from = newflight.from;
	flight->depart = newflight.depart;
	flight->to = newflight.to;
	flight->arrive = newflight.arrive;
	flight->next = NULL;

	unsigned int index = airports.getIndex(flight->from);
	if(graphList[index].next == NULL)
		graphList[index].next = flight;
	else
	{
		flight->next = graphList[index].next;
		graphList[index].next = flight;
	}
	edgeCount++;
}

void airlineRouter::dijkstraSP(int start, int sttime)
// implements Dijksta's Algorithm to find the shortest path from the passed node to every node
// parameters: the starting vertex
{
	// ensures graph data exists
	if(graph == true)
	{	
		int v;
		int atime, utime;
		flightNode *it = new flightNode;
		// creates an priority queue object
		priorityQueue path;
		// item = vertex # 
		// priority = distance weight

		// distance and previous node array initializations
		dist = new int[vertexCount];
		for(int i=0; i<vertexCount; i++)
			dist[i] = std::numeric_limits<int>::max();

		prev = new flightNode[vertexCount];
		for(int i=0; i<vertexCount; i++)
			prev[i].depart = -1;

		// inserts starting vertex to priority queue
		path.insert(start, sttime);
		dist[start] = 0;

		while(!path.isEmpty())
		{
			// removes shortest path from heap
			path.deleteMin(start, utime);
			it = graphList[start].next;
			while(it != NULL)
			{
				// checks if if there is a shorter path distance to v from u
				v = airports.getIndex(it->to);	
				atime = it->arrive;
				if(utime < it->depart && atime < dist[v] && it->depart < atime)
				{
					// if a shorter path exists, update
					dist[v] = atime;
					prev[v] = *it;
					atime +=30;
					if(atime%100 > 60)
						atime += 40; 
					path.insert(v, atime);
				}
				it = it->next;
			}
		}
	}
	else
		cout << "dijkstra: Error, no graph data." << endl;
}

void airlineRouter::showPath(const int dest)
// recusively prints the path from the source node to the destination node.
// parameters: the destination node
{
	// base case

	if(prev[dest].depart < 0)
		return;
	else
	{
		// recursive calls
		unsigned int from = airports.getIndex(prev[dest].from);
		showPath(from);

		cout << "Flight:" << endl;
		cout << "  " << prev[dest].from << "-" << prev[dest].to << " :: DeptTime: " 
			 << prev[dest].depart << "   ArrvTime: " << prev[dest].arrive 
			 <<  "   " << endl << "  Flight Number: " << prev[dest].code << endl << endl;		
	}
}

void airlineRouter::destroyGraph()
// deletes all dynamically allocated memory & initialize class variables as empty.
// no parameters
{
	// deletes graphMatrix
	if(graphList != NULL)
	{
		flightNode *it;
		for(int i=0; i<vertexCount; i++)
		{
			it = graphList[i].next;
			while(it != NULL)
			{
				it = it->next;
				delete graphList[i].next;
				graphList[i].next = it;
			}
		}
	}
	// deletes distance array
	if(dist != NULL)
	{
		delete [] dist;
		dist = NULL;
	}
	// deletes previous node array
	if(prev != NULL)
	{
		delete [] prev;
		prev = NULL;
	}
}
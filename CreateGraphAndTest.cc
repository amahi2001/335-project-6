// CSCI 335 Homework #6

// Your name: Abrar Mahi
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "graph.h"
using namespace std;

graph createGraph(const string graph_file)
{
  // Open graph input file
  ifstream graphInput(graph_file);

  if(graphInput.fail())
  {
    cerr << "unable to open graph input file" << endl;
    exit(1);
  }

  int size = 0, origin = 0, Vertex = 0;
  float eW = 0.0;

  string line;
  stringstream ssLine;

  // Read in size and initialize Graph
  getline(graphInput, line);
  ssLine.str(line);
  ssLine >> size;
  graph newGraph(size);

  // Read in directed edges and construct Graph
  while (getline(graphInput, line))
  {
    ssLine.clear();
    ssLine.str(line);

    ssLine >> origin;

    while (ssLine >> Vertex)
    {
      ssLine >> eW;

      newGraph.addEdge(origin, Vertex, eW);
    }
  }
  graphInput.close();

  return newGraph;
}


void testGraphDriver(const string query_file, graph &graph)
{
  // Open query file
  ifstream queryInput(query_file);
  if(queryInput.fail())
  {
    cerr << "wasn't able to open query file" << endl;
    exit(1);
  }
  
  //initialize vars
  stringstream ssLine;
  float eW = 0.0;
  int origin = 0, Vertex = 0;
  string line;
  

  // for every edge in query, check if edge exists between origin and "target" verte
  while (getline(queryInput, line))
  {
    ssLine.clear();
    ssLine.str(line);

    ssLine >> origin >> Vertex;

    eW = graph.isConnected(origin, Vertex);

    if (eW != -1.0)
    {
      cout << origin << " " << Vertex
           << ": connected " << eW << endl;
    }
    else if (origin == Vertex)
    {
      cout << origin << " " << Vertex
           << ": Same vertex 0" << endl;
    }
    else
    {
      cout << origin << " " << Vertex
           << ": not_connected" << endl;
    }
  }
  
  cout << endl; 
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
    return 0;
  }

  //setting paramters
  const string graph_file(argv[1]);
  const string query_file(argv[2]);

  // Creating a new Graph param file
  graph graph = createGraph(graph_file);

  // Test Graph
  testGraphDriver(query_file, graph);

  return 0;
}

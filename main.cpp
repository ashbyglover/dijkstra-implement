/*
Name: Ashby Glover
Final Program Spring 2020
Implementing Dijkstra

This program as a whole implements Dijkstra's algorithm to determine
 the shortest path in a specified graph (read in from a file)
 from a starting vertex to the other vertices in the graph.
 The program also outputs the shortest path information to an output file.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "graph.cpp"
using namespace std;

int main() {

  // Read in and open graph text file
  string input;
  ifstream myReadFile;
  cout << "Enter name of graph text file: ";
  cin >> input;
  myReadFile.open(input);

  // Gets max number of vertices from file
  int x;
  myReadFile >> x;

  // Creates adjaceny matrix that is [numVertices]x[numVertices]
  Graph matrix(x);


  // Reads in edge values from file and puts them in adjacency matrix
  int row, col, edge;
  while (myReadFile >> row >> col >> edge) {
    matrix.addEdge(row, col, edge);
  }

  //close file
  myReadFile.close();

  // Let user choose starting vertex
  int start;
  cout << "Enter vaild vertex id for starting vertex: ";
  cin >> start;

  // Find shortest path from starting vertex to each other vertex in the graph
  // and write to outfile
  matrix.dijkstra(start);

return 0;
}

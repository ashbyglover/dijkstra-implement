/*
Name: Ashby Glover
Final Program Spring 2020
Implementing Dijkstra


graph.cpp implements the functions found in graph.h

*/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "graph.h"
using namespace std;
using namespace std::chrono;




//--------------------------------------------------------------------------
/*
graph(): constructor.
  Initalizes each element of the adjaceny matrix to INFINITY

  x: the first number read in from the graph file. It represents the maximum
    number of vertices

*/
Graph::Graph (int x) {
  numVertex = x;

  for (int i = 1; i <= numVertex; i++) {
    for (int j = 1; j <= numVertex; j++) {
      adjacencyMatrix[i][j] = INFINITY;
    }
  }
}

/*---------------------------------------------------------------------------
 addEdge(): adds data to a row and col in an adjacencyMatrix
  used to populate adjacenyMatrix with weights from graph file

    This function also adds the vertices to a set, which can only hold one
      copy of each vertex. This allows a check of whether a certain vertex
      exists in practice in this matrix. (i.e. a [10][10] matrix where no
      edge references the vertex #8.)

    row: the number that represents the row in the adjacencyMatrix
    col: the number for the column
    data: the weight for that edge
*/
void Graph::addEdge(int row, int col, int data) {
  adjacencyMatrix[row][col] = data;
  exists.insert(row); //creates a set that only holds vertices that exist
  exists.insert(col);
}

/*----------------------------------------------------------------------------
  displayMatrix(): prints out the adjacency matrix in this format (x, y) = #.

  Does not print out the edges with no weight (still set to INFINITY).
*/
void Graph::displayMatrix() {
  for (int i = 1; i <= numVertex; i++) {
    for (int j = 1; j <= numVertex; j++) {
      if (adjacencyMatrix[i][j] != INFINITY)
        cout << "(" << i << ", " << j << ") = " << adjacencyMatrix[i][j] << endl;
      }
    }
}

/*---------------------------------------------------------------------------
  isQueueEmpty(): returns a boolean indicating whether there are any vertices
    left in the priority queue
    used in dijkstra()

    dist[]: an int array created in dijkstra() to hold distance values
    visited[]: a bool array created in dijkstra() to indicate whether a vertex
      has been visited yet or not

    returns: bool isEmpty
*/
bool Graph::isQueueEmpty(int dist[], bool visited[]) {
  bool isEmpty = true;
  for (int i = 1; i <= numVertex; i++) {
    if (dist[i] != INFINITY && !visited[i]) {
      isEmpty = false;
      return isEmpty;
    }
  }
  return isEmpty;
}

/*---------------------------------------------------------------------------
  findMin(): return the vertex with the smallest distance
    used in dijkstra()

    dist[]: an int array created in dijkstra() to hold distance values
    visited[]: a bool array created in dijkstra() to indicate whether a vertex
      has been visited yet or not

    returns: int smallest, which represents the vertex with the smallest
      distance in the priority queue

*/
int Graph::findMin(int dist[], bool visited[]) {
  int min = INFINITY;
  int smallest;
  for (int i = 1; i <= numVertex; i++) {
    if (dist[i] < min && visited[i] != true) {
      min = dist[i];
      smallest = i;
    }
  }
  return smallest;
}

/*--------------------------------------------------------------------------
  printPrev(): creates a queue of prev values to assist in printing them
    to an outfile
    used in dijkstra()

    This function recursively inserts prev values into a queue, so that they
      can be printed in order in dijkstra()

    start: the vertex the path starts from
    i: where the path ends
    prev[]: array that holds the prev values that represent the shortest path
    printPath: queue of integers, holds values from prev[]

*/
void Graph::printPrev(int start, int i, int prev[], queue<int> & printPath) {
  if (prev[i] == UNDEFINED) {
    printPath.push(i);
    return;
  }
  else {
    printPrev(start, prev[i], prev, printPath);
    printPath.push(i);
  }
}

/*---------------------------------------------------------------------------
  dijkstra(): determines the shortest path in a specified graph from a
    specified starting vertex to each other vertex in the graph

    int start: represents the starting vertex
*/
void Graph::dijkstra (int start) {
  auto srt = high_resolution_clock::now(); // will time dijkstra algorithm
  int dist[MAX]; // holds distance
  bool visited[MAX]; // holds whether vertex has been visited or not
  int prev [MAX]; // holds prev vertex


  for (int i = 1; i <= numVertex; i++) {
    dist[i] = INFINITY;
    prev[i] = UNDEFINED;
    visited[i] = false;
  }
  dist[start] = 0;
  visited[start] = false;


// the following sets each vertex's dist (or weight) to its shortest path value
  int alt;
  while (!isQueueEmpty(dist, visited)) {
    int v = findMin(dist, visited);
    visited[v] = true;
    for (int w = 1; w <= numVertex; w++) {
      if (adjacencyMatrix[v][w] != INFINITY) {
        if (!visited[w]) {
          alt = dist[v] + adjacencyMatrix[v][w];
          if (alt < dist[w]) {
            dist[w] = alt;
            prev[w] = v;
          }
        }
      }
    }
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop - srt);
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: "
    << duration.count() << endl;

  //prints out shortest path information to outfile
  string output;
  cout << "Please enter the name of an output text file: ";
  cin >> output;
  ofstream outfile(output);
  queue<int> printPath; // queue to assist with printing prev

  for (int i = 1; i <= numVertex; i++) {
    if (dist[i] != INFINITY) {
      outfile << i << ": " << dist[i] << " [";
      printPrev(start, i, prev, printPath);
      while (!printPath.empty()) {
        outfile << printPath.front();
        printPath.pop();
        if (!printPath.empty())
        outfile << ", ";
      }
      outfile << "]" << endl;
    }
    else {
      if (exists.count(i) == 1) // if the vertex exists
        outfile << i << ": " << "NO PATH" << endl;
      } // if it does not exist, do not print a line for it
  }
}

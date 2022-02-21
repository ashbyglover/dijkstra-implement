/*
Name: Ashby Glover
Final Program Spring 2020
Implementing Dijkstra


graph.h defines the functions used in graph.cpp

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int INFINITY = 1000000;
const int MAX = 30;
const int UNDEFINED = -1;

class Graph {
public:
  Graph (int x);
    // creates an adjaceny matrix with x number of vertices, and initializes
    // whole matrix to INFINITY
  void addEdge (int row, int col, int data);
    // adjacencyMatrix[row][col] = data
  void displayMatrix();
    // displays the matrix
  void dijkstra (int start);
    // runs the dijkstra algorithm and outputs shortest path to text file

private:
  int numVertex;
  int adjacencyMatrix[MAX][MAX];
  set<int> exists;
  int findMin(int dist[], bool visited[]);
  bool isQueueEmpty(int dist[], bool visited[]);
  void printPrev(int start, int i, int prev[], queue<int> & printPath);
};

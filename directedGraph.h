#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

class directedGraph : public Graph
{
public:
    directedGraph(int nodeCount) : Graph(nodeCount)
    {
        // this will inherit the constructor of the parent class (Graph)
    }
    virtual bool isCyclic();
    virtual void addEdge(int node1, int node2, int weight = 1)
    {
        adj[node1].push_back({node2, weight});
    }
    virtual vector<vector<int>> ListToMatrix();
    directedGraph Transpose();

private:
    bool cycleDetectionHelper(int node, vector<int> &visited, vector<int> &recStack);
};

// function to convert from adjacency list to adjacency matrix
vector<vector<int>> directedGraph::ListToMatrix()
{

    vector<vector<int>> adjMatrix(nodeCount + 1, vector<int>(nodeCount + 1));
    for (int i = 1; i <= nodeCount; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            adjMatrix[i][adj[i][j].first] = adj[i][j].second;
        }
    }
    // return the adjacency matrix
    return adjMatrix;
}

// function to get the transpose of the graph
directedGraph directedGraph::Transpose()
{
    directedGraph graphPrime(nodeCount);
    for (int node = 1; node <= nodeCount; node++)
    {
        for (pair<int, int> p : adj[node])
        {
            graphPrime.addEdge(p.first, node);
        }
    }
    return graphPrime;
}

// function for detecting cycle
bool directedGraph::cycleDetectionHelper(int node, vector<int> &visited, vector<int> &recStack)
{
    visited[node] = true;
    recStack[node] = true;
    for (pair<int, int> neighbours : adj[node])
    {
        int neighbour = neighbours.first;
        if (visited[neighbour] == false)
        {
            if (cycleDetectionHelper(neighbour, visited, recStack) == true)
            {
                return true;
            }
        }
        else if (recStack[node] == true)
        {
            return true;
        }
    }
    recStack[node] = false;
    return false;
}

// function to check whether the graph contains cycle or not
bool directedGraph::isCyclic()
{
    int numberOfNodes = this->nodeCount;
    vector<int> visited(numberOfNodes + 1, false);
    vector<int> recStack(numberOfNodes + 1, false);
    for (int node = 1; node <= numberOfNodes; node++)
    {
        if (visited[node] == false)
        {
            if (cycleDetectionHelper(node, visited, recStack) == true)
            {
                return true; // cycle detected
            }
        }
    }
    return false; // cycle not detected
}

#endif
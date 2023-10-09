#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

class undirectedGraph : public Graph
{
public:
    undirectedGraph(int nodeCount) : Graph(nodeCount)
    {
        // inherit the constructor of the parent class (Graph)
    }

    virtual bool isCyclic();
    virtual void addEdge(int node1, int node2, int weight = 1)
    {
        adj[node1].push_back({node2, weight});
        adj[node2].push_back({node1, weight});
    }
    virtual vector<vector<int>> ListToMatrix();
    virtual void showGraph();

private:
    bool cycleDetectionHelper(int node, int parent, vector<int> &visisted);
    int getNumberOfNodes();
};

void undirectedGraph::showGraph()
{
    int numberOfNodes = getNumberOfNodes();

    for (int node = 1; node <= numberOfNodes; node++)
    {
        for (pair<int, int> neighbours : adj[node])
        {
            int neighbour = neighbours.first;
            int weight = neighbours.second;
            cout << node << " ----- "
                 << "{" << neighbour << " , " << weight << "}"
                 << "\n";
        }
    }
}

// function to get the number of nodes
int undirectedGraph::getNumberOfNodes()
{
    return this->nodeCount;
}

// helper function to detect the cycle
bool undirectedGraph::cycleDetectionHelper(int node, int parent, vector<int> &visited)
{
    visited[node] = true;
    for (pair<int, int> neighbours : adj[node])
    {
        int neighbour = neighbours.first;
        if (visited[neighbour] == false)
        {
            if (cycleDetectionHelper(neighbour, node, visited))
            {
                return true;
            }
        }
    }
    return false;
}

// function to check whether the graph contains cycle or not
bool undirectedGraph::isCyclic()
{
    int numberOfNode = getNumberOfNodes();
    vector<int> visited(numberOfNode + 1);

    for (int node = 1; node <= numberOfNode; node++)
    {
        if (visited[node] == false)
        {
            if (cycleDetectionHelper(node, -1, visited))
            {
                return true;
            }
        }
    }
    return false;
}

// function to convert adjacency list to matrix
vector<vector<int>> undirectedGraph::ListToMatrix()
{
    int numberOfNodes = getNumberOfNodes();

    // adjMatrix vector can be initialised with some non-permissible weight value so that there is clear distiction-
    // between the nodes which have and edge
    // in case of an unweighted graph , can be filled with 0
    // in case of positive weighted graph , can be filled with -1
    // in case of negative weighted graph , can be filled with some large negative value or large positive value
    // here dummy value used is -1e9
    vector<vector<int>> adjMatrix(numberOfNodes + 1, vector<int>(numberOfNodes + 1, -1e9));
    for (int node = 1; node <= numberOfNodes; node++)
    {
        for (pair<int, int> neighbours : adj[node])
        {
            int neighbour = neighbours.first;
            int weight = neighbours.second;
            adjMatrix[node][neighbour] = weight;
        }
    }
    return adjMatrix;
}

#endif
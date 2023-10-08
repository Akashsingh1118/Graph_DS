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
        adj[node2].push_back({node2, weight});
    }

private:
    bool cycleDetectionHelper(int node, int parent, vector<int> &visisted);
};

// function to detect the cycle
bool undirectedGraph::cycleDetectionHelper(int node, int parent, vector<int> &visited)
{
    visited[node] = true;
    for (pair<int, int> neighbours : adj[node])
    {
        int neighbour = neighbours.first;
        if (visited[neighbour] == false)
        {
            if (cycleDetectionHelper(neighbour, node, visited))
                ;
        }
    }
}

// function to check whether the graph contain cycle or not

bool undirectedGraph::isCyclic()
{
    int numberOfNode = this->nodeCount;
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

#endif
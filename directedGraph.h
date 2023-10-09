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
        // inherit the constructor of the parent class (Graph)
    }
    virtual bool isCyclic();
    virtual void addEdge(int node1, int node2, int weight = 1)
    {
        adj[node1].push_back({node2, weight});
    }
    virtual vector<vector<int>> ListToMatrix();
    virtual void showGraph();
    directedGraph Transpose();
    vector<int> topologicalSort();

private:
    bool cycleDetectionHelper(int node, vector<int> &visited, vector<int> &recStack);
    vector<int> getIndegree();
    int getNumberOfNodes();
};

// function to get the indegree value for all the nodes
vector<int> directedGraph::getIndegree()
{
    int numberOfNodes = getNumberOfNodes();
    vector<int> inDegree(numberOfNodes + 1);
    for (int node = 1; node <= numberOfNodes; node++)
    {
        for (pair<int, int> neighbours : adj[node])
        {
            int neighbour = neighbours.first;
            inDegree[neighbour]++;
        }
    }
    return inDegree;
}
// function to get the number of nodes
int directedGraph::getNumberOfNodes()
{
    return this->nodeCount;
}

// function to print the graph with edges
void directedGraph::showGraph()
{
    int numberOfNodes = getNumberOfNodes();

    for (int node = 1; node <= numberOfNodes; node++)
    {
        for (pair<int, int> neighbours : adj[node])
        {
            int neighbour = neighbours.first;
            int weight = neighbours.second;
            cout << node << " ----> "
                 << "{" << neighbour << " , " << weight << "}"
                 << "\n";
        }
    }
}

// function to convert from adjacency list to adjacency matrix
vector<vector<int>> directedGraph::ListToMatrix()
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

// function to get the transpose of the graph
directedGraph directedGraph::Transpose()
{
    int numberOfNodes = getNumberOfNodes();
    directedGraph graphPrime(numberOfNodes);
    for (int node = 1; node <= numberOfNodes; node++)
    {
        for (pair<int, int> p : adj[node])
        {
            graphPrime.addEdge(p.first, node);
        }
    }
    return graphPrime;
}

// helper function for detecting cycle
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
        else if (recStack[neighbour] == true)
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
    int numberOfNodes = getNumberOfNodes();
    vector<int> visited(numberOfNodes + 1, false);
    vector<int> recStack(numberOfNodes + 1, false);
    for (int node = 1; node <= numberOfNodes; node++)
    {
        if (visited[node] == false)
        {
            if (cycleDetectionHelper(node, visited, recStack) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// function to get the topological sort of the graph (kahn's algorithm)
vector<int> directedGraph::topologicalSort()
{
    bool cycle = isCyclic();
    vector<int> topoOrder;
    if (cycle == true)
    {
        cout << "Graph is cyclic and hence no topological order possible";
        return topoOrder;
    }
    int numberOfNodes = getNumberOfNodes();
    vector<int> inDegree = getIndegree();
    queue<int> nodesInQueue;
    for (int node = 1; node <= numberOfNodes; node++)
    {
        if (inDegree[node] == 0)
        {
            nodesInQueue.push(node);
        }
    }

    while (nodesInQueue.empty() == false)
    {
        int frontNode = nodesInQueue.front();
        nodesInQueue.pop();
        topoOrder.push_back(frontNode);
        for (pair<int, int> neighbours : adj[frontNode])
        {
            int neighbour = neighbours.first;
            inDegree[neighbour]--;
            if (inDegree[neighbour] == 0)
            {
                nodesInQueue.push(neighbour);
            }
        }
    }
    return topoOrder;
}

#endif
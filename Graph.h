// header guards
#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
using namespace std;

// Abstract graph class
class Graph
{
protected:
	int nodeCount;
	vector<vector<pair<int, int>>> adj; // adjacency list to store the graph

public:
	Graph(int nodeCount)
	{
		this->nodeCount = nodeCount;
		adj = vector<vector<pair<int, int>>>(nodeCount + 1); // assuming nodes start from 1
	}
	virtual void addEdge(int node1, int node2, int weight) = 0;
	virtual bool isCyclic() = 0;
	virtual vector<vector<int>> ListToMatrix() = 0;
	virtual void showGraph() = 0;
	vector<int> dfsTraversal(int source);
	vector<int> bfsTraversal(int source);
};

// function for Depth-First Search traversal of the graph
vector<int> Graph::dfsTraversal(int source)
{
	vector<int> nodesDiscovered;
	vector<bool> visited(nodeCount + 1, false);

	// helper function for doing depth first search
	function<void(int)> dfsHelper = [&](int node)
	{
		visited[node] = true;
		nodesDiscovered.push_back(node);
		for (pair<int, int> neighbours : adj[node])
		{
			int neighbour = neighbours.first;
			if (visited[neighbour] == false)
			{
				dfsHelper(neighbour);
			}
		}
	};
	dfsHelper(source);
	return nodesDiscovered;
}

// function for Breadth-First Search traversal of the graph
vector<int> Graph::bfsTraversal(int source)
{
	vector<int> nodesDiscovered;
	vector<bool> visited(nodeCount + 1, false);
	queue<int> nodesInQueue;
	nodesInQueue.push(source);

	while (nodesInQueue.empty() == false)
	{
		int frontNode = nodesInQueue.front();
		nodesInQueue.pop();
		nodesDiscovered.push_back(frontNode);

		for (pair<int, int> neighbours : adj[frontNode])
		{
			int neighbour = neighbours.first;
			if (visited[neighbour] == false)
			{
				nodesInQueue.push(neighbour);
				visited[neighbour] = true;
			}
		}
	}
	return nodesDiscovered;
}

#endif
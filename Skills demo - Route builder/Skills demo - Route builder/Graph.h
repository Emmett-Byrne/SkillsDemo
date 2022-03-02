#pragma once
#include <string>
#include <vector>
#include <queue>
#include "Node.h"
#include "Math.h"

/// <summary>
/// This class is responsible for building our graph and pathfinding through the graph
/// </summary>
class Graph
{
public:
	Graph(std::vector<std::vector<std::string>> nodeData)
	{
		buildGraph(nodeData);
	}

	Node* getNodeFromName(std::string cityName);
	std::vector<Node*> createPath(std::string start, std::string destination);

private:
	void buildGraph(std::vector<std::vector<std::string>> nodeData);

	std::vector<Node> nodes;
	Node* m_graph;
};

inline Node* Graph::getNodeFromName(std::string cityName)
{
	for (Node& node : nodes)
	{
		if (node.getName() == cityName)
		{
			return &node;
		}
	}
	return nullptr;
}

/// <summary>
/// This function simply builds a graph from the given node data. Creates all the nodes and sets the connections between them
/// </summary>
/// <param name="nodeData">Node data</param>
inline void Graph::buildGraph(std::vector<std::vector<std::string>> nodeData)
{
	//add nodes to the list
	for (std::vector<std::string> data : nodeData)
	{
		Node node = { data[0], std::stof(data[1]), std::stof(data[2]) };
		nodes.push_back(node);
	}

	//add connections for each node
	for (std::vector<std::string> data : nodeData)
	{
		Node* currentNode = getNodeFromName(data[0]);
		for (int i = 3; i < data.size(); i++)
		{
			currentNode->addConnection(getNodeFromName(data[i]));
		}
	}
}

/// <summary>
/// This is the pathfinding algorithm that will create a path between 2 nodes.
/// It is an implementation of the A* pathfinding algorithm
/// Realisticaly for what i'm using it for here it's a bit overkill and Djikstras algorithm would be better.
/// I would like to come back to this project at some point and add in a proceedurally generated maze and have the algorithm solve it.
/// Which would be a much better use case for A*
/// </summary>
/// <param name="start"></param>
/// <param name="destination"></param>
/// <returns></returns>
inline std::vector<Node*> Graph::createPath(std::string start, std::string destination)
{
	int iterations = 0;
	for (Node& node : nodes)
	{
		node.reset();
	}

	Node* startNode = getNodeFromName(start);
	Node* destinationNode = getNodeFromName(destination);

	//Creating custom compare function for the priority queue
	auto compare = [](Node* l, Node* r) {
		return l->getTotalDistance() > r->getTotalDistance();
	};
	std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> queue(compare);
	startNode->setDistance(0);
	startNode->setTotalDistance(Math::distanceBetween(startNode->getEast(), startNode->getNorth(), destinationNode->getEast(), destinationNode->getNorth()));
	queue.push(startNode);

	while (!queue.empty() && queue.top() != destinationNode)
	{
		iterations++;
		Node* current = queue.top();
		queue.pop();

		std::vector<Node*> connections = current->getConnections();

		for (Node* connection : connections)
		{
			float distance = Math::distanceBetween(connection->getEast(),
				connection->getNorth(),
													startNode->getEast(), 
													startNode->getNorth());

			if (connection->getDistance() > distance)
			{
				connection->setDistance(distance);
				connection->setTotalDistance(distance + Math::distanceBetween(connection->getEast(),
																		connection->getNorth(),
																		destinationNode->getEast(),
																		destinationNode->getNorth()));
				connection->setPreviousNode(current);
				queue.push(connection);
			}
		}
	}

	if (queue.top() == destinationNode)
	{
		std::vector<Node*> path;
		Node* currentNode = destinationNode;

		do
		{
			path.insert(path.begin(), currentNode); //pushing to front of vector
			currentNode = currentNode->getPrevious();
		} while (currentNode);

		std::cout << "Path created in " << iterations << " iteration" << std::endl;
		return path;
	}

	return std::vector<Node*>();
}
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Graph.h"

int main()
{
	//Reading data from file and prepping it to be passed into our Graph object
	std::string line;
	std::vector<std::vector<std::string>> data;
	std::ifstream file("nodes.txt"); 
	while (std::getline(file, line)) {
		std::vector<std::string> nodeData;
		size_t split;
		do
		{
			split = line.find(", ");
			std::string subStr = line.substr(0, split);
			line.erase(0, split +2);
			nodeData.push_back(subStr);
		} while (split != std::string::npos);

		data.push_back(nodeData);
	}

	//Creating Graph
	Graph graph(data);

	//Taking input
	std::string startpoint;
	std::string endpoint;

	std::cout << "Input starting city: ";
	std::cin >> startpoint;

	std::cout << "Input destination city: ";
	std::cin >> endpoint;

	//Pathfinding
	//std::vector<Node*> path = graph.createPath(startpoint, endpoint);
	std::vector<Node*> path = graph.createPath("Dublin", "Kyiv");

	std::cout << "Path: ";
	for (Node* node : path)
	{
		std::cout << node->getName() << ", ";
	}
}
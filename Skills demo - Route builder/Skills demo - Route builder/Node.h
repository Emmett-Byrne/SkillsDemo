#pragma once
#include <string>
#include <vector>


//This is a simple class to contain the data each node will have
//Now that I've already finished implementing this I realise this would probably have been better as a struct... Oh well.
class Node
{
public:
	Node(std::string name, float north, float east) :
		m_name(name),
		m_north(north),
		m_east(east),
		m_distance(0),
		m_totalDistance(0),
		m_previous(nullptr)
	{
	}

	const std::string getName()
	{
		return m_name;
	}

	const float getNorth()
	{
		return m_north;
	}

	const float getEast()
	{
		return m_east;
	}

	std::vector<Node*> getConnections() 
	{
		return m_connections;
	}

	void addConnection(Node* connection)
	{
		m_connections.push_back(connection);
	}

	void setDistance(float distance)
	{
		m_distance = distance;
	}

	float getDistance()
	{
		return m_distance;
	}

	void setTotalDistance(float distance)
	{
		m_totalDistance = distance;
	}

	float getTotalDistance()
	{
		return m_totalDistance;
	}

	void setPreviousNode(Node* previous)
	{
		m_previous = previous;
	}

	Node* getPrevious()
	{
		return m_previous;
	}

	void reset()
	{
		m_distance = std::numeric_limits<float>::max();
		m_totalDistance = std::numeric_limits<float>::max();
		m_previous = nullptr;
	}

private:
	//Node Data
	std::string m_name;
	float m_north;
	float m_east;
	std::vector<Node*> m_connections;


	//Pathfinding Data
	float m_distance;		//This is the amount of distance traveled so far.
	float m_totalDistance;	//This is the estimated total amount of distance required to travel to the destination. Also known as the Heuristic.
	Node* m_previous;		//The previous Node in the path.
};


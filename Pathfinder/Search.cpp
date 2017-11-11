#include "Search.h"

Search::Search(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	agent = _agent;
	pathFound = false;
	start = agent->GetStartNode();
	end = agent->GetEndNode();
}

Search::~Search()
{

}

void Search::Update()
{
	switch (agent->GetSearchType())
	{
	case(BREADTH):
	{
		BreadthSearch();
		break;
	}
	case(BEST):
	{
		BestFirst();
		break;
	}
	case(ASTAR):
	{
		AStarSearch();
		break;
	}
	}
	while (end != start)
	{
		path.push_back(end);
		end = end->getParent();
	}
	agent->SetPath(path);
	if (pathFound)
	{
		stateManager->ChangeState(new Movement(stateManager, agent));
	}
}

void Search::BreadthSearch()
{
	std::vector<Node*> Open;
	std::vector<Node*> Closed;
	std::vector<Node*> Neighbours;
	Open.push_back(start);
	while (pathFound != true && Open.size() > 0)
	{
		if (Open.front() == end)
		{
			pathFound = true;
		}
		else
		{
			Neighbours = Open.front()->getNeighbours();
			Closed.push_back(Open.front());
			for (size_t i = 0; i < Neighbours.size(); i++)
			{
				Node* currentNeighbour = Neighbours.at(i);
				if (currentNeighbour->getIsMoveable())
				{
					if (!(std::find(Closed.begin(), Closed.end(), currentNeighbour) != Closed.end()))
					{
						if (!(std::find(Open.begin(), Open.end(), currentNeighbour) != Open.end()))
						{
							Neighbours.at(i)->setParent(Open.front());
							Open.push_back(Neighbours.at(i));
							if (Neighbours.at(i) != end && Neighbours.at(i) != start)
							{
								//Neighbours.at(i)->setTexture(searched);
							}
						}
					}
				}
			}
			Open.erase(Open.begin());
		}
	}
	Neighbours.clear();
	if (pathFound)
	{
		Node* rtn = Open.front();
		Open.clear();
		//return rtn;
	}
	else
	{
		//return nullptr;
	}
}

void Search::BestFirst()
{
	int noSearched = 0;
	std::vector<Node*> Open;
	std::vector<Node*> Closed;
	std::vector<Node*> Neighbours;
	Open.push_back(start);
	Node* curr = nullptr;

	while (pathFound != true && Open.size() > 0)
	{
		curr = Open.front();
		for (int i = 0; i < Open.size(); i++)
		{
			if (Open.at(i)->getH() < curr->getH())
			{
				curr = Open.at(i);
			}
		}
		if (curr == end)
		{
			pathFound = true;
		}
		else
		{
			Neighbours = curr->getNeighbours();
			Open.erase(std::remove(Open.begin(), Open.end(), curr), Open.end());
			Closed.push_back(curr);
			for (size_t i = 0; i < Neighbours.size(); i++)
			{
				Node* currentNeighbour = Neighbours.at(i);
				if (currentNeighbour->getIsMoveable())
				{
					if (!(std::find(Closed.begin(), Closed.end(), currentNeighbour) != Closed.end()))
					{
						if (!(std::find(Open.begin(), Open.end(), currentNeighbour) != Open.end()))
						{
							currentNeighbour->setParent(curr);
							float a = abs(currentNeighbour->GetGridX() - end->GetGridX());
							float b = abs(currentNeighbour->getGridY() - end->getGridY());
							currentNeighbour->setH(sqrt((a*a) + (b*b))*10);
							Open.push_back(currentNeighbour);

							if (currentNeighbour != end && currentNeighbour != start)
							{
								noSearched++;
							}
						}
					}
				}
			}
			Neighbours.clear();
		}
	}
	if (pathFound)
	{
		std::cout << noSearched << "\n";
		Node* rtn = curr;
		Open.clear();
		Closed.clear();
		//return rtn;
	}
	else
	{
		//return nullptr;
	}
}

void Search::AStarSearch()
{
	int noSearched = 0;
	std::vector<Node*> Open;
	std::vector<Node*> Neighbours;
	std::vector<Node*> Closed;
	Node* currentNode = nullptr;
	Node* currentNeighbour = nullptr;
	bool skip = false;
	bool isInOpen = false;
	Open.push_back(start);

	while (Open.size() > 0 && pathFound != true)
	{
		int i = 0;
		currentNode = Open.front();

		while (i < Open.size())
		{
			if (Open.at(i)->getF() < currentNode->getF())
			{
				currentNode = Open.at(i);
			}
			else if (Open.at(i)->getF() == currentNode->getF())//find the losest F valued node(closest)
			{
				if (Open.at(i)->getH() < currentNode->getH())
				{
					currentNode = Open.at(i);
				}
			}
			i++;
		}
		for (size_t b = 0; b < Open.size(); b++)
		{
			if (Open.at(b) == end)
			{
				currentNode = Open.at(b);
				pathFound = true;
				break;
			}
		}
		if (pathFound)
		{
			break;
		}

		Closed.push_back(currentNode);
		if (currentNode != end && currentNode != start)
		{
			noSearched++;
			//currentNode->setTexture(searched);
		}
		Open.erase(std::remove(Open.begin(), Open.end(), currentNode), Open.end());

		for each(Node* Node in currentNode->getNeighbours())
		{
			Neighbours.push_back(Node);
		}

		for (size_t c = 0; c < Neighbours.size(); c++)//for every neighbour
		{
			currentNeighbour = Neighbours.at(c);
			if (currentNeighbour->getIsMoveable())//if its not a wall
			{
				float cost = 0;
				if (currentNeighbour->GetGridX() != currentNode->GetGridX() && currentNeighbour->getGridY() != currentNode->getGridY())//generate the added G cost based on if its a diagonal
				{
					cost = 14;//diagonal neighbour
				}
				else
				{
					cost = 10;//verticle/horizontal neighbour
				}

				if (!(std::find(Closed.begin(), Closed.end(), currentNeighbour) != Closed.end()))//if its not in closed
				{
					if (!(std::find(Open.begin(), Open.end(), currentNeighbour) != Open.end()))//if its not in open set parent, canclulate g, h and f and put into open
					{
						currentNeighbour->setParent(currentNode);//set parent

						currentNeighbour->setG(currentNode->getG() + cost);//set the G score
						float a = abs((currentNeighbour->GetGridX() - end->GetGridX()));
						float b = abs((currentNeighbour->getGridY() - end->getGridY()));
						currentNeighbour->setH(sqrt((a*a) + (b*b)) * 10);//calculate H
						currentNeighbour->setF();//set F
						Open.push_back(currentNeighbour);//push back neighbour
					}
					else//if it is in open check if the new current node would make a better parent
					{
						ReEvaluate(currentNeighbour, currentNode, Open, cost);
					}
				}
				else//if it is in open check if its a better route
				{
					ReEvaluate(currentNeighbour, currentNode, Closed, cost);//check if the current node makes a better parent
				}
			}
		}
		Neighbours.clear();
	}
	Open.clear();
	Neighbours.clear();
	Closed.clear();
	if (pathFound)
	{
		std::cout << noSearched << "\n";
		//return currentNode;
	}
	else
	{
		//return nullptr;
	}
}

void Search::ReEvaluate(Node* _neighbour, Node* _node, std::vector <Node*> _vec, float cost)
{
	int m = 0;
	while (m < _vec.size())//find where it is in the vector
	{
		if (_vec.at(m) == _neighbour)
		{
			if (_neighbour->getH() + _node->getG() + cost < _neighbour->getF())//if the current nodes G gives a better value to the neighbours F
			{
				_vec.at(m)->setParent(_node);//change the parent
				_neighbour->setG(_node->getG() + cost);
				_vec.at(m)->setF();//update the new F
			}
			break;
		}
		m++;
	}
}

void Search::Draw()
{
	agent->Draw();
}
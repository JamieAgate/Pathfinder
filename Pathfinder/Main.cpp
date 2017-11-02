#include <SDL/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "StateManager.h"
#include "StateTemplate.h"
#include "Idle.h"
#include "AI.h"
#include "Search.h"
#include "Node.h"
#include "Cursor.h"
#include "SetUp.h"

void MainLoop(SDL_Renderer* _renderer, SDL_Window* _window);
Node* BreadthSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched);
Node* AStarSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched);
Node* BestFirst(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched);
void ResetAllNodes(std::vector<Node*> _vec);
void ReEvaluate(Node* _neighbour ,Node* _node, std::vector <Node*> _vec, float cost);

int main(int arc, char* args[])
{
	const int SCREEN_WIDTH = 960;
	const int SCREEN_HEIGHT = 960;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not Initialize. SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		if (!IMG_Init((IMG_INIT_PNG)& IMG_INIT_PNG))
		{
			printf("IMG could not be initialized. SDL_Error: %s\n", SDL_GetError());
		}
		window = SDL_CreateWindow("Pathfinder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window couldn't be created. SDL_Error %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)//initialise renderer
			{
				printf("Renderer could not be created! SDL_ERROR %s\n", SDL_GetError());
			}
			else
			{
				MainLoop(renderer, window);
			}
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	system("PAUSE");
	return 0;
}

void MainLoop(SDL_Renderer* _renderer, SDL_Window* _window)
{

	bool quit = false;
	SDL_Event e;
	//std::vector<Node*> Grid;
	//int GridWIDTH = 30;
	//int GridHEIGHT = 30;
	//int previousStartNode = 0;
	//int previousEndNode = 0;
	//int currentNode = 0;
	//enum Search { BREADTH, BEST, ASTAR };
	//int searchType = BREADTH;


	//SDL_Surface* bmp = IMG_Load("tile32.png");
	//SDL_Texture* tile = SDL_CreateTextureFromSurface(_renderer, bmp);

	//bmp = IMG_Load("Start.png");
	//SDL_Texture* Start = SDL_CreateTextureFromSurface(_renderer, bmp);

	//bmp = IMG_Load("End.png");
	//SDL_Texture* End = SDL_CreateTextureFromSurface(_renderer, bmp);

	//bmp = IMG_Load("Wall.png");
	//SDL_Texture* Wall = SDL_CreateTextureFromSurface(_renderer, bmp);

	//bmp = IMG_Load("Select.png");
	//SDL_Texture* select = SDL_CreateTextureFromSurface(_renderer, bmp);

	//bmp = IMG_Load("path.png");
	//SDL_Texture* Path = SDL_CreateTextureFromSurface(_renderer, bmp);

	//bmp = IMG_Load("Searched.png");
	//SDL_Texture* searched = SDL_CreateTextureFromSurface(_renderer, bmp);

	//SDL_FreeSurface(bmp);

	//Cursor* Select = new Cursor(_renderer, select, 0, 0, 32, 32);
	//Sprite* start = new Sprite(_renderer, Start, -32, -32, 32, 32);
	//Sprite* end = new Sprite(_renderer, End, -32, -32, 32, 32);
	//Node* StartNode = nullptr;
	//Node* EndNode = nullptr;
	//Node* finished = nullptr;
	//bool pathfound = false;

	////make the grid
	//for (int x = 0; x < GridWIDTH; x++)
	//{
	//	for (int y = 0; y < GridHEIGHT; y++)
	//	{
	//		Node* newNode = new Node(_renderer, tile, x * 32, y * 32, 32, 32, x, y);
	//		Grid.push_back(newNode);
	//	}
	//}

	////make the neighbours
	//int i = 0;
	//for (int x = 0; x < GridWIDTH; x++) {
	//	for (int y = 0; y < GridHEIGHT; y++) 
	//	{
	//		if (x == 0)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH));
	//		}
	//		else if (x == GridWIDTH - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridHEIGHT));
	//		}
	//		else
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH));
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridHEIGHT));
	//		}

	//		if (y == 0)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + 1));
	//		}
	//		else if (y == GridHEIGHT - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - 1));
	//		}
	//		else
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i - 1));
	//		}
	//		if (x != 0 && y != 0 && x != GridWIDTH - 1 && y != GridHEIGHT - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
	//		}
	//		//edge diagonals
	//		if (x == 0 && y != 0 && y != GridHEIGHT - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
	//		}
	//		if (y == 0 && x != 0 && x != GridWIDTH - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
	//		}
	//		if (x == GridWIDTH - 1 && y != 0 && y != GridHEIGHT - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
	//		}
	//		if (y == GridHEIGHT - 1 && x != 0 && x != GridWIDTH - 1)
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
	//		}
	//		if (x == 0 && y == 0)//top left corner
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
	//		}
	//		if (x == 0 && y == GridHEIGHT - 1)//bottom left corner
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
	//		}
	//		if (x == GridWIDTH - 1 && y == 0)//top right corner
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
	//		}
	//		if (x == GridWIDTH - 1 && y == GridHEIGHT - 1)// bottom right corner
	//		{
	//			Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
	//		}
	//		i++;
	//	}
	//}

	//StateManager aiStateManager;
	//AIData* breadthFirstData = new AIData(BREADTH,Grid);
	StateManager gameStateManager;
	StateManager aiStateManager;
	gameStateManager.AddState(new SetUp(&gameStateManager,&aiStateManager ,_renderer));
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		SDL_RenderClear(_renderer);

		gameStateManager.Update();
		gameStateManager.Draw();

		//Select->update();
		//const Uint8* key = SDL_GetKeyboardState(NULL);
		//currentNode = Select->getMouseX() / 32 * 30 + Select->getMouseY() / 32;
		//
		////place start node
		//if (key[SDL_SCANCODE_S])
		//{
		//	if (previousStartNode != currentNode)
		//	{
		//		Grid.at(previousStartNode)->setIsStart(false);
		//		previousStartNode = currentNode;
		//	}
		//	start->SetX(Grid.at(currentNode)->GetX());
		//	start->SetY(Grid.at(currentNode)->GetY());
		//	Grid.at(currentNode)->setIsStart(true);
		//	StartNode = Grid.at(currentNode);
		//}
		////place end node
		//if (key[SDL_SCANCODE_E])
		//{
		//	if (previousEndNode != currentNode)
		//	{
		//		Grid.at(previousEndNode)->setIsGoal(false);
		//		previousEndNode = currentNode;
		//	}
		//	end->SetX(Grid.at(currentNode)->GetX());
		//	end->SetY(Grid.at(currentNode)->GetY());
		//	Grid.at(currentNode)->setIsGoal(true);
		//	EndNode = Grid.at(currentNode);
		//}
		////clear grid
		//if (key[SDL_SCANCODE_BACKSPACE])
		//{
		//	for each(Node* _node in Grid)
		//	{
		//		_node->setTexture(tile);
		//		_node->setMoveable(true);
		//	}
		//}
		////
		//if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
		//{
		//	if (key[SDL_SCANCODE_LCTRL])
		//	{
		//		Grid.at(currentNode)->setTexture(tile);
		//		Grid.at(currentNode)->setMoveable(true);
		//	}
		//	else
		//	{
		//		Grid.at(currentNode)->setTexture(Wall);
		//		Grid.at(currentNode)->setMoveable(false);
		//	}
		//}
		//if (key[SDL_SCANCODE_1])
		//{
		//	aiStateManager.AddState(new Idle(&aiStateManager, breadthFirstData));
		//	searchType = BREADTH;
		//}
		//if (key[SDL_SCANCODE_3])
		//{
		//	searchType = ASTAR;
		//}
		//if (key[SDL_SCANCODE_2])
		//{
		//	searchType = BEST;
		//}
		//if (key[SDL_SCANCODE_RETURN])
		//{
		//	pathfound = false;
		//	for (size_t i = 0; i < Grid.size(); i++)
		//	{
		//		if (!Grid.at(i)->getIsGoal() && !Grid.at(i)->getIsStart() && Grid.at(i)->getIsMoveable())
		//		{
		//			Grid.at(i)->setTexture(tile);
		//		}
		//	}
		//	switch (searchType)
		//	{
		//	case(BREADTH):
		//	{
		//		finished = BreadthSearch(StartNode, EndNode, pathfound, searched);
		//		break;
		//	}
		//	case(ASTAR):
		//	{
		//		ResetAllNodes(Grid);
		//		finished = AStarSearch(StartNode, EndNode, pathfound, searched);
		//		break;
		//	}
		//	case(BEST):
		//	{
		//		ResetAllNodes(Grid);
		//		finished = BestFirst(StartNode, EndNode, pathfound, searched);
		//		break;
		//	}
		//	}
		//}
		//if (pathfound == true)
		//{
		//	bool firstTime = true;
		//	while (!finished->getIsStart())
		//	{
		//		if (firstTime == false)
		//		{
		//			finished->setTexture(Path);
		//		}
		//		finished = finished->getParent();
		//		firstTime = false;
		//	}
		//	pathfound = false;
		//}
		////draw functions
		//for (size_t i = 0; i < Grid.size(); i++)
		//{
		//	Grid.at(i)->Draw();
		//}
		//Select->Draw();
		//start->Draw();
		//end->Draw();

		SDL_RenderPresent(_renderer);
	}
	//delete all elements in vector and clear it
	/*for (size_t i = 0; i < Grid.size(); i++)
	{
		delete Grid.at(i);
	}
	Grid.clear();
	delete Select;
	delete start;
	delete end;
	delete StartNode;
	delete EndNode;*/
}

Node* BreadthSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched)
{
	std::vector<Node*> Open;
	std::vector<Node*> Closed;
	std::vector<Node*> Neighbours;
	Open.push_back(_start);
	while (_pathfound != true && Open.size() > 0)
	{
		if (Open.front() == _endNode)
		{
			_pathfound = true;
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
							currentNeighbour->setParent(Open.front());
							Open.push_back(Neighbours.at(i));
							if (currentNeighbour != _endNode && currentNeighbour != _start)
							{
								currentNeighbour->setTexture(_searched);
							}
						}
					}
				}
			}
			Open.erase(Open.begin());
		}
	}
	Neighbours.clear();
	if (_pathfound)
	{
		Node* rtn = Open.front();
		Open.clear();
		Closed.clear();
		return rtn;
	}
	else
	{
		return nullptr;
	}
}

Node* AStarSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched)
{
	int noSearched = 0;
	std::vector<Node*> Open;
	std::vector<Node*> Neighbours;
	std::vector<Node*> Closed;
	Node* currentNode = nullptr;
	Node* currentNeighbour = nullptr;
	bool skip = false;
	bool isInOpen = false;
	Open.push_back(_start);

	while (Open.size() > 0 || _pathfound != true)
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
			if (Open.at(b) == _endNode)
			{
				currentNode = Open.at(b);
				_pathfound = true;
				break;
			}
		}
		if (_pathfound)
		{
			break;
		}

		Closed.push_back(currentNode);
		if (currentNode != _endNode && currentNode != _start)
		{
			noSearched++;
			currentNode->setTexture(_searched);
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
						float a = abs((currentNeighbour->GetGridX() - _endNode->GetGridX()));
						float b = abs((currentNeighbour->getGridY() - _endNode->getGridY()));
						currentNeighbour->setH(sqrt((a*a) + (b*b))*10);//calculate H
						currentNeighbour->setF();//set F
						Open.push_back(currentNeighbour);//push back neighbour
					}
					else//if it is in open check if the new current node would make a better parent
					{
						ReEvaluate(currentNeighbour,currentNode,Open,cost);
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
	if (_pathfound)
	{
		std::cout << noSearched << "\n";
		return currentNode;
	}
	else
	{
		return nullptr;
	}
}

Node* BestFirst(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched)
{
	int noSearched = 0;
	std::vector<Node*> Open;
	std::vector<Node*> Closed;
	std::vector<Node*> Neighbours;
	Open.push_back(_start);
	Node* curr = nullptr;

	while (_pathfound != true && Open.size() > 0)
	{
		curr = Open.front();
		for (int i = 0; i < Open.size(); i++)
		{
			if (Open.at(i)->getH() < curr->getH())
			{
				curr = Open.at(i);
			}
		}
		if (curr == _endNode)
		{
			_pathfound = true;
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
							float a = (currentNeighbour->GetGridX() - _endNode->GetGridX());
							float b = (currentNeighbour->getGridY() - _endNode->getGridY());
							currentNeighbour->setH(sqrt((a*a) + (b*b)));
							Open.push_back(currentNeighbour);

							if (currentNeighbour != _endNode && currentNeighbour != _start)
							{
								noSearched++;
								Neighbours.at(i)->setTexture(_searched);
							}
						}
					}
				}
			}
			Neighbours.clear();
		}
	}
	if (_pathfound)
	{
		std::cout << noSearched << "\n";
		Node* rtn = curr;
		Open.clear();
		Closed.clear();
		return rtn;
	}
	else
	{
		return nullptr;
	}
	
}

void ResetAllNodes(std::vector<Node*> _vec)
{
	for each (Node* n in _vec)
	{
		n->setG(0);
		n->setH(0);
		n->setF();
	}
}

void ReEvaluate(Node* _neighbour,Node* _node ,std::vector <Node*> _vec, float cost)
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
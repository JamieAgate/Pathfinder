#include <SDL/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Node.h"
#include "Cursor.h"

void MainLoop(SDL_Renderer* _renderer, SDL_Window* _window);
Node* BreadthSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched);
Node* AStarSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched);
bool checkIfDiag(Node* _node, Node* _neighbour);

int main(int arc, char* args[])
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 640;
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
	std::vector<Node*> Grid;
	int GridWIDTH = 20;
	int GridHEIGHT = 20;
	int previousStartNode = 0;
	int previousEndNode = 0;
	int currentNode = 0;
	enum Search {BREADTH,ASTAR};
	int searchType = BREADTH;

	SDL_Surface* bmp = IMG_Load("tile32.png");
	SDL_Texture* tile = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Start.png");
	SDL_Texture* Start = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("End.png");
	SDL_Texture* End = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Wall.png");
	SDL_Texture* Wall = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Select.png");
	SDL_Texture* select = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("path.png");
	SDL_Texture* Path = SDL_CreateTextureFromSurface(_renderer, bmp);

	bmp = IMG_Load("Searched.png");
	SDL_Texture* searched = SDL_CreateTextureFromSurface(_renderer, bmp);

	SDL_FreeSurface(bmp);

	Cursor* Select = new Cursor(_renderer, select, 0, 0, 32, 32);
	Node* StartNode = nullptr;
	Node* EndNode = nullptr;
	Node* finished = nullptr;
	bool pathfound = false;

	for (int x = 0; x < GridWIDTH; x++)
	{
		for (int y = 0; y < GridHEIGHT; y++)
		{
			Node* newNode = new Node(_renderer, tile, x * 32, y * 32, 32, 32, x, y);
			Grid.push_back(newNode);
		}
	}
	int i = 0;
	for (int x = 0; x < GridWIDTH; x++) {
		for (int y = 0; y < GridHEIGHT; y++) {
			if (x == 0)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH));
				/*if (y != 0)
				{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
				}
				if (y != GridHEIGHT - 1)
				{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				}*/
			}
			else if (x == GridWIDTH - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridHEIGHT));
				/*if (y != 0)
				{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
				}
				if (y != GridHEIGHT - 1)
				{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				}*/
			}
			else
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH));
				Grid.at(i)->SetNeighbours(Grid.at(i - GridHEIGHT));
				/*if (y != 0)
				{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
				}
				if (y != GridHEIGHT - 1)
				{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				}*/
			}

			if (y == 0)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + 1));
			}
			else if (y == GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - 1));
			}
			else
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + 1));
				Grid.at(i)->SetNeighbours(Grid.at(i - 1));
			}
			if (x != 0 && y != 0 && x != GridWIDTH - 1 && y != GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH - 1));
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
			}
			/*if (x != 0 || y != 0)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH - 1));
			}
			if (x != 0 || y != GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i - GridWIDTH + 1));
			}
			if (x != GridWIDTH - 1 || y != GridHEIGHT - 1)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH  -1));
			}
			if (x != GridWIDTH - 1 || y != 0)
			{
				Grid.at(i)->SetNeighbours(Grid.at(i + GridWIDTH + 1));
			}*/

			i++;
		}
	}

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		SDL_RenderClear(_renderer);

		Select->update();
		const Uint8* key = SDL_GetKeyboardState(NULL);


		currentNode = Select->getMouseX() / 32 * 20 + Select->getMouseY() / 32;
		std::cout << Grid.at(currentNode)->getF() << ",g: " << Grid.at(currentNode)->getG() << ",h: " << Grid.at(currentNode)->getH() <<"\n";
		if (key[SDL_SCANCODE_S])
		{
			if (previousStartNode != currentNode)
			{
				Grid.at(previousStartNode)->setTexture(tile);
				Grid.at(previousStartNode)->setIsStart(false);
				previousStartNode = currentNode;
			}
			Grid.at(currentNode)->setTexture(Start);
			Grid.at(currentNode)->setIsStart(true);
			StartNode = Grid.at(currentNode);
		}
		if (key[SDL_SCANCODE_E])
		{
			if (previousEndNode != currentNode)
			{
				Grid.at(previousEndNode)->setTexture(tile);
				Grid.at(previousEndNode)->setIsGoal(false);
				previousEndNode = currentNode;
			}
			Grid.at(currentNode)->setTexture(End);
			Grid.at(currentNode)->setIsGoal(true);
			EndNode = Grid.at(currentNode);
		}
		if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			if (key[SDL_SCANCODE_LCTRL])
			{
				Grid.at(currentNode)->setTexture(tile);
				Grid.at(currentNode)->setMoveable(true);
			}
			else
			{
				Grid.at(currentNode)->setTexture(Wall);
				Grid.at(currentNode)->setMoveable(false);
			}
		}
		if (key[SDL_SCANCODE_1])
		{
			searchType = BREADTH;
		}
		if (key[SDL_SCANCODE_2])
		{
			searchType = ASTAR;
		}

		if (key[SDL_SCANCODE_RETURN])
		{
			pathfound = false;
			for (size_t i = 0; i < Grid.size(); i++)
			{
				Grid.at(i)->setSearched(false);
				if (!Grid.at(i)->getIsGoal() && !Grid.at(i)->getIsStart() && Grid.at(i)->getIsMoveable())
				{
					Grid.at(i)->setTexture(tile);
				}
			}
			switch (searchType)
			{
			case(BREADTH):
			{
				finished = BreadthSearch(StartNode, EndNode, pathfound, searched);
				break;
			}
			case(ASTAR):
			{
				finished = AStarSearch(StartNode, EndNode, pathfound,searched);
				break;
			}
			}
		}

		if (pathfound == true)
		{
			bool firstTime = true;
			while (!finished->getIsStart())
			{
				if (firstTime == false)
				{
					finished->setTexture(Path);
				}
				finished = finished->getParent();
				firstTime = false;
			}
			pathfound = false;
		}
for (size_t i = 0; i < Grid.size(); i++)
{
	Grid.at(i)->Draw();
}
Select->Draw();


SDL_RenderPresent(_renderer);
	}
	for (size_t i = 0; i < Grid.size(); i++)
	{
		delete Grid.at(i);
	}
	Grid.clear();
	delete Select;
	delete StartNode;
	delete EndNode;
}

Node* BreadthSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched)
{
	std::vector<Node*> Open;
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
			for (size_t i = 0; i < Neighbours.size(); i++)
			{
				if (!Neighbours.at(i)->getSearched() && Neighbours.at(i)->getIsMoveable())
				{
					Neighbours.at(i)->setParent(Open.front());
					Open.push_back(Neighbours.at(i));
					Neighbours.at(i)->setSearched(true);
					if (Neighbours.at(i) != _endNode && Neighbours.at(i) != _start)
					{
						Neighbours.at(i)->setTexture(_searched);
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
		return rtn;
	}
	else
	{
		return nullptr;
	}
}

Node* AStarSearch(Node* _start, Node* _endNode, bool &_pathfound, SDL_Texture* _searched)
{
	std::vector<Node*> Open;
	std::vector<Node*> Neighbours;
	std::vector<Node*> Closed;
	Node* currentNode = nullptr;
	Node* currentNeighbour = nullptr;
	bool skip = false;
	bool isInOpen = false;
	Open.push_back(_start);

	do
	{
		int i = 0;
		currentNode = Open.front();

		while (i < Open.size())
		{
			if (Open.at(i)->getF() == currentNode->getF())//find the losest F valued node(closest)
			{
				if (Open.at(i)->getH() > currentNode->getH())
				{
					currentNode = Open.at(i);
				}
			}
			else if (Open.at(i)->getF() < currentNode->getF())
			{
				currentNode = Open.at(i);
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
		Open.erase(std::remove(Open.begin(), Open.end(), currentNode), Open.end());

		Neighbours.clear();
		Neighbours = currentNode->getNeighbours();

		for (size_t c = 0; c < Neighbours.size(); c++)//for every neighbour
		{
			currentNeighbour = Neighbours.at(c);
			if (currentNeighbour->getIsMoveable())
			{
				float cost = 0;
				if (currentNeighbour->GetGridX() != currentNode->GetGridX() && currentNeighbour->getGridY() != currentNode->getGridY())
				{
					cost = 14;
				}
				else
				{
					cost = 10;
				}

				if (!(std::find(Closed.begin(), Closed.end(), currentNeighbour) != Closed.end()))//if its not in closed
				{
					if (currentNeighbour != _endNode && currentNeighbour != _start)
					{
						currentNeighbour->setTexture(_searched);
					}
					if (!(std::find(Open.begin(), Open.end(), currentNeighbour) != Open.end()))//if its not in open set parent, canclulate g, h and f and put into open
					{
						currentNeighbour->setParent(currentNode);

						currentNeighbour->setG(currentNode->getG() + cost);
						float a = abs((currentNeighbour->GetGridX() - _endNode->GetGridX()));
						float b = abs((currentNeighbour->getGridY() - _endNode->getGridY()));
						currentNeighbour->setH(sqrt((a*a) + (b*b)));
						currentNeighbour->setF();
						Open.push_back(currentNeighbour);
					}
				}
				else//if it is in open check if its a better route
				{
					isInOpen = false;
					int m = 0;
					while (m < Closed.size())//check if its in open already
					{
						if (Closed.at(m) == currentNeighbour)
						{
							if (currentNeighbour->getH() + currentNode->getG() + cost < currentNeighbour->getF())
							{
								Closed.at(m)->setParent(currentNode);
								currentNeighbour->setG(currentNode->getG() + cost);
								Closed.at(m)->setF();
							}
							break;
						}
						m++;
					}
				}
			}
		}
	} while (Open.size() > 0 || _pathfound != true);
	Open.clear();
	Neighbours.clear();
	Closed.clear();
	return currentNode;
}
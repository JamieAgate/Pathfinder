/// @file Search.cpp
/// @brief Search State for the AI
#include "Search.h"

bool function( Node* i, Node* j ) { return(i->getH() < j->getH()); }//Used to Sort vector based on H values

struct Sort {
	bool operator() ( Node* i, Node* j ) { return i->getH() < j->getH(); }
}sortH;//sorts vector based on H value

Search::Search( StateManager* _stateManager, AIData* _agent ) :
	StateTemplate( _stateManager )
{
	m_agent = _agent;//sets agent
	m_pathFound = false;//sets if the path is found
	m_end = m_agent->GetCurrentOccupiedNode();//sents the end node
	m_start = m_agent->GetPathEndNode();//sets the start node
}

Search::~Search()
{

}

void Search::Update()
{
	m_start = m_agent->GetCurrentOccupiedNode();//sets the start node
	m_end = m_agent->GetPathEndNode();//sents the end node
	ResetGrid();//resets all values of nodes
	switch ( m_agent->GetSearchType() )//switch for the algorithm used
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
	//CREATS PATH
	int sizeOfPath = 0;
	m_end = m_end->getParent();
	while ( m_end != m_start )
	{
		m_path.push_back( m_end );
		m_end = m_end->getParent();
		sizeOfPath++;
	}
	m_agent->SetPath( m_path );//set the path
	m_agent->SetSizeOfPath( ceil( sizeOfPath / 2 ) );//set the size of path to be half the size
	//FINISHED CREATING PATH
	if ( m_pathFound )//if the path has been found
	{
		m_stateManager->ChangeState( new Movement( m_stateManager, m_agent ) );//change to movement state
	}
}

void Search::ResetGrid()
{
	std::vector<Node*> grid = m_agent->GetGrid();//gets the grid
	for each(Node* n in grid)//for all nodes in grid
	{
		n->setG( 0 );//reset G
		n->setH( 0 );//reset H
		n->setF();//reset F
	}
}

void Search::BreadthSearch()
{
	std::vector<Node*> Open;//make open list
	std::vector<Node*> Closed;//make closed list
	std::vector<Node*> Neighbours;//make neighbours list
	Open.push_back( m_start );//push the start into open
	while ( m_pathFound != true && Open.size() > 0 )//while there are nodes in open or path hasnt been found
	{
		if ( Open.front() == m_end )//if the first node in open is the end node
		{
			m_pathFound = true;//exit
		}
		else
		{
			Neighbours = Open.front()->getNeighbours();//get the neighbours of the current node
			Closed.push_back( Open.front() );//push the current node into closed
			for ( size_t i = 0; i < Neighbours.size(); i++ )//for all the neighbours
			{
				Node* currentNeighbour = Neighbours.at( i );
				if ( currentNeighbour->getIsMoveable() )//if its not a wall
				{
					if ( !(std::find( Closed.begin(), Closed.end(), currentNeighbour ) != Closed.end()) )//if its not in closed
					{
						if ( !(std::find( Open.begin(), Open.end(), currentNeighbour ) != Open.end()) )//if its not in open
						{
							Neighbours.at( i )->setParent( Open.front() );//set the parent to be the current node
							Open.push_back( Neighbours.at( i ) );//push the neighbour in open
						}
					}
				}
			}
			Open.erase( Open.begin() );//remove the current node from open
		}
	}
	Open.clear();//clear Open
	Neighbours.clear();//clear the neighbour vector
	Closed.clear();//clears Closed
}

void Search::BestFirst()
{
	std::vector<Node*> Open;//make open list
	std::vector<Node*> Closed;//make closed list
	std::vector<Node*> Neighbours;//make Neighbours list
	Open.push_back( m_start );//push start into open list
	Node* curr = nullptr;//initialize current node
	while ( m_pathFound != true && Open.size() > 0 )//while there are nodes in open or path hasnt been found
	{
		std::sort( Open.begin(), Open.end(), sortH );//sort open baseed on H values
		curr = Open.front();//set current node to be the first node in open

		if ( curr == m_end )//if current node is the end node
		{
			m_pathFound = true;//set pathfound to be true
		}
		else
		{
			Neighbours = curr->getNeighbours();//get the neighbours of the current node
			Open.erase( std::remove( Open.begin(), Open.end(), curr ), Open.end() );//erase currenet node from open 
			Closed.push_back( curr );//push current node from open
			for ( size_t i = 0; i < Neighbours.size(); i++ )//for all the neighbours
			{
				Node* currentNeighbour = Neighbours.at( i );//set the current neighbour
				if ( currentNeighbour->getIsMoveable() )//if the current neighbour is not a wall
				{
					if ( !(std::find( Closed.begin(), Closed.end(), currentNeighbour ) != Closed.end()) )//if the current neighbour is not in closed
					{
						if ( !(std::find( Open.begin(), Open.end(), currentNeighbour ) != Open.end()) )//if the current neighbour is not in open
						{
							currentNeighbour->setParent( curr );//set the parent to be the current node
							//calculate H
							float a = abs( (currentNeighbour->GetGridX() - m_end->GetGridX()) );
							float b = abs( (currentNeighbour->getGridY() - m_end->getGridY()) );
							currentNeighbour->setH( sqrt( ((a*a) + (b*b)) * 10 ) );//set H
							//finish calculating h
							Open.push_back( currentNeighbour );//push the current neighbour into open
						}
					}
				}
			}
			Neighbours.clear();//clear neighbour vector
		}
	}
	Open.clear();//clears open
	Closed.clear();//clears closed
}

void Search::AStarSearch()
{
	std::vector<Node*> Open;//makes open list
	std::vector<Node*> Neighbours;//makes neighbours list
	std::vector<Node*> Closed;//makes closed list
	Node* currentNode = nullptr;//initializes current node
	Node* currentNeighbour = nullptr;//initialize current Neighbour
	Open.push_back( m_start );//push start into open
	while ( Open.size() > 0 && m_pathFound != true )//while there are nodes in open or path hasnt been found
	{
		currentNode = Open.front();//set current node to be first in open

		int i = 0;
		while ( i < Open.size() )//find the losest F valued node(closest)
		{
			if ( Open.at( i )->getF() < currentNode->getF() )//if a better F value is found
			{
				currentNode = Open.at( i );//set current node to be best F value
			}
			else if ( Open.at( i )->getF() == currentNode->getF() )//if F is the same
			{
				if ( Open.at( i )->getH() < currentNode->getH() )//If a better H value is found
				{
					currentNode = Open.at( i );//set current node to be the best H value
				}
			}
			i++;
		}
		for ( size_t b = 0; b < Open.size(); b++ )//attempt to find end in open
		{
			if ( Open.at( b ) == m_end )//if end is in open
			{
				currentNode = Open.at( b );//set current node to end
				m_pathFound = true;//pathfound is true
				break;
			}
		}
		if ( m_pathFound )
		{
			break;
		}

		Closed.push_back( currentNode );//push current node into closed
		Open.erase( std::remove( Open.begin(), Open.end(), currentNode ), Open.end() );//erase current node from open

		for each(Node* Node in currentNode->getNeighbours())//get all neighbours of current node
		{
			Neighbours.push_back( Node );
		}

		for ( size_t c = 0; c < Neighbours.size(); c++ )//for every neighbour
		{
			currentNeighbour = Neighbours.at( c );
			if ( currentNeighbour->getIsMoveable() )//if its not a wall
			{
				float cost = 0;
				if ( currentNeighbour->GetGridX() != currentNode->GetGridX() && currentNeighbour->getGridY() != currentNode->getGridY() )//generate the added G cost based on if its a diagonal
				{
					cost = 14;//diagonal neighbour
				}
				else
				{
					cost = 10;//verticle/horizontal neighbour
				}

				if ( !(std::find( Closed.begin(), Closed.end(), currentNeighbour ) != Closed.end()) )//if its not in closed
				{
					if ( !(std::find( Open.begin(), Open.end(), currentNeighbour ) != Open.end()) )//if its not in open set parent, canclulate g, h and f and put into open
					{
						currentNeighbour->setParent( currentNode );//set parent
						currentNeighbour->setG( currentNode->getG() + cost );//set the G score
						float a = abs( (currentNeighbour->GetGridX() - m_end->GetGridX()) );
						float b = abs( (currentNeighbour->getGridY() - m_end->getGridY()) );
						currentNeighbour->setH( (sqrt( (a*a) + (b*b) ) * 10) + currentNeighbour->GetNodeCost() );//calculate H
						currentNeighbour->setF();//set F
						Open.push_back( currentNeighbour );//push back neighbour
					}
					else//if it is in open check if the new current node would make a better parent
					{
						ReEvaluate( currentNeighbour, currentNode, Open, cost );
					}
				}
				else//if it is in open check if its a better route
				{
					ReEvaluate( currentNeighbour, currentNode, Closed, cost );//check if the current node makes a better parent
				}
			}
		}
		Neighbours.clear();
	}
	Open.clear();
	Neighbours.clear();
	Closed.clear();
	if ( m_pathFound )
	{
		//std::cout << noSearched << "\n";
		//return currentNode;
	}
	else
	{
		//return nullptr;
	}
}

void Search::ReEvaluate( Node* _neighbour, Node* _node, std::vector <Node*> _vec, float cost )
{
	int m = 0;
	while ( m < _vec.size() )//find where it is in the vector
	{
		if ( _vec.at( m ) == _neighbour )
		{
			if ( _neighbour->getH() + _node->getG() + cost < _neighbour->getF() )//if the current nodes G gives a better value to the neighbours F
			{
				_vec.at( m )->setParent( _node );//change the parent
				_neighbour->setG( _node->getG() + cost );
				_vec.at( m )->setF();//update the new F
			}
			break;
		}
		m++;
	}
}

void Search::Draw()
{
	m_agent->Draw();//draw agent
}
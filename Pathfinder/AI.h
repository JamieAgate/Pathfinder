/// \file AI.h
/// \brief Contains all Data the AI needs to operate.

#ifndef _AI_H_
#define _AI_H_
//File Includes
#include "Sprite.h"
#include "Node.h"
#include "Player.h"

class AIData {
public:
	AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite, SDL_Texture* _pathSprite,SDL_Renderer* _renderer, Player* _player,Sprite* _attack, Sprite* _Idle);//constructor for AIData
	~AIData();//Destructor for AIData

	void Update();//Update AI
	
	int GetSearchType() { return m_searchType; } //Gets the ID for what Algorithm will be used by this agent
	Node* GetStartNode() { return m_start; }//gets the Node that the agent will search from
	Node* GetEndNode() { return m_end; }//gets the Node the agent will search to
	int GetDrawnathSize() { return m_drawnPath.size(); }//retruns the size of the drawn path vector
	int GetPathSize() { return m_path.size(); }//gets the size of the path vector
	Node* GetPathEndNode() { return m_player->GetCurrentOccupiedNode(); }//gets the node the player is currently on
	Node* GetCurrentOccupiedNode() { return m_grid.at(m_image->GetX() / 32 * 30 + m_image->GetY() / 32); }//gets the node the agent is currently on
	int GetSizeOfPath() { return m_sizeOfPath; }//gets the size of the path
	int GetCurrentSizeOfPath() { return m_path.size(); }//gets the size of the path vector
	std::vector<Node*> GetGrid() { return m_player->GetGrid(); }//Gets the Grid
	int GetDistanceForPlayer();//gets the distance from the agent to the player


	void SetPostitionInGridVector(int _g) { m_positionInGridVector = _g; }//sets the position in the grid vector
	void SetStartNode(Node* _start) { m_start = _start; }//sets the start node used in the pathfind
	void SetEndNode(Node* _end) { m_end = _end; }//sets the end node used in the pathfind
	void SetPath(std::vector<Node*> _path) { m_path.clear(); m_path = _path; }//sets the path that the agent will move down
	void SetSizeOfPath(int _n) { m_sizeOfPath = _n; }//sets the size of the path

	void Move();//moves the agent
	void MakeDrawPath();//creats the vector of sprites to represent the path

	void Draw();//draws the agent
	void DrawAttack();//draws the agent in attack mode
	void DrawIdle();//draws the agent in idle mode
	void DrawPath();//draws the path
protected:
	Player* m_player;
	SDL_Renderer* m_renderer;
	Node* m_start;//node the pathfind starts from
	Node* m_end;//node that the pathfind will end at
	Sprite* m_image;//sprite of the normal agent
	Sprite* m_attack;//sprite used when agent is attacking
	Sprite* m_idle;//sprite used when agent is idle
	SDL_Texture* m_pathSprite;//the path texture
	enum e_searchType { BREADTH, BEST, ASTAR };
	int m_searchType;//search algorithm id used by the agent
	std::vector<Node*> m_grid;//grid of nodes
	int m_positionInGridVector;//the position of the node in the vector that the agent is currently on
	std::vector<Node*> m_path;//the path that the agent will move along
	std::vector<Sprite*> m_drawnPath;//the vector of sprites used to represent the path
	int m_sizeOfPath;//the size of the path
};
#endif // !_AI_H_

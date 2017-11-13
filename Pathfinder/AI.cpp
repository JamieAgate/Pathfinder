/// @file AI.cpp
/// @brief Contains all data and functions used by the AI
#include "AI.h"

AIData::AIData( int _searchType, std::vector<Node*> _grid, Sprite* _sprite, SDL_Texture* _pathSprite, SDL_Renderer* _renderer, Player* _player, Sprite* _attack, Sprite* _Idle )
{
	m_searchType = _searchType;
	m_grid = _grid;
	m_image = _sprite;

	m_pathSprite = _pathSprite;
	m_renderer = _renderer;

	m_player = _player;

	m_attack = _attack;
	m_idle = _Idle;
}

AIData::~AIData()
{
	m_grid.clear();
	SDL_DestroyTexture( m_pathSprite );
}

void AIData::Update()
{

}

void AIData::Move()
{
	if ( m_path.size() > 0 )//if the path size is greater than 0
	{
		m_image->SetX( m_path.back()->GetX() );//move the sprite to the next x co-ordinate in the path
		m_image->SetY( m_path.back()->GetY() );//move the sprite to the next y co-ordinate in the path
		m_path.pop_back();//remove the node moved to from the path
	}
}

int AIData::GetDistanceForPlayer()
{
	//calculates distance from player and returns it
	int a = abs( GetCurrentOccupiedNode()->GetX() - GetPathEndNode()->GetX() );
	int b = abs( GetCurrentOccupiedNode()->GetY() - GetPathEndNode()->GetY() );
	return sqrt( (a*a) + (b*b) );

}

void AIData::MakeDrawPath()
{
	for each(Sprite* s in m_drawnPath)//clears the previous draw path
	{
		delete s;
	}
	m_drawnPath.clear();
	for each (Node* n in m_path)//makes the new draw path
	{
		m_drawnPath.push_back( new Sprite( m_renderer, m_pathSprite, n->GetX(), n->GetY(), 32, 32, false ) );
	}
}

void AIData::Draw()
{
	m_image->Draw();//draws the agent
}

void AIData::DrawAttack()
{
	//sets attack to be in the correct location
	m_attack->SetX( m_image->GetX() );
	m_attack->SetY( m_image->GetY() );

	m_attack->Draw();//draws the attack
}

void AIData::DrawIdle()
{
	//sets idle to be in the correct location
	m_idle->SetX( m_image->GetX() );
	m_idle->SetY( m_image->GetY() );
	m_idle->Draw();//draws the idle
}

void AIData::DrawPath()
{
	for each(Sprite* s in m_drawnPath)//draws all sprites in the path
	{
		s->Draw();
	}
}
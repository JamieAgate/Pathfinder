#include "AI.h"

AIData::AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite, SDL_Texture* _pathSprite, SDL_Renderer* _renderer, Player* _player, Sprite* _attack, Sprite* _Idle)
{
	searchType = _searchType;
	grid = _grid;
	image = _sprite;
	
	pathSprite = _pathSprite;
	renderer = _renderer;

	player = _player;

	attack = _attack;
	idle = _Idle;
}

AIData::~AIData()
{
	grid.clear();
	SDL_DestroyTexture(pathSprite);
}

void AIData::Update()
{

}

void AIData::Move()
{
	if (path.size() > 0)
	{
		image->SetX(path.back()->GetX());
		image->SetY(path.back()->GetY());
		path.pop_back();
	}
}

int AIData::GetDistanceForPlayer()
{
	int a = abs(GetCurrentOccupiedNode()->GetX() - GetPathEndNode()->GetX());
	int b = abs(GetCurrentOccupiedNode()->GetY() - GetPathEndNode()->GetY());
	return sqrt((a*a) + (b*b));

}

void AIData::MakeDrawPath()
{
	for each(Sprite* s in drawnPath)
	{
		delete s;
	}
	drawnPath.clear();
	for each (Node* n in path)
	{
		drawnPath.push_back(new Sprite(renderer, pathSprite, n->GetX(), n->GetY(), 32, 32,false));
	}
}

void AIData::Draw()
{
	image->Draw();
}

void AIData::DrawAttack()
{
	attack->SetX(image->GetX());
	attack->SetY(image->GetY());
	attack->Draw();
}

void AIData::DrawIdle()
{
	idle->SetX(image->GetX());
	idle->SetY(image->GetY());
	idle->Draw();
}

void AIData::DrawPath()
{
	for each(Sprite* s in drawnPath)
	{
		s->Draw();
	}
}
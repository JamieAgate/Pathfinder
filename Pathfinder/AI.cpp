#include "AI.h"

AIData::AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite, SDL_Texture* _pathSprite, SDL_Renderer* _renderer, Player* _player)
{
	searchType = _searchType;
	grid = _grid;
	image = _sprite;
	
	pathSprite = _pathSprite;
	renderer = _renderer;

	player = _player;
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
		image->SetX(path.front()->GetX());
		image->SetY(path.front()->GetY());
		path.erase(path.begin());
	}
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

void AIData::DrawPath()
{
	for each(Sprite* s in drawnPath)
	{
		s->Draw();
	}
}
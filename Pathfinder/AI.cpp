#include "AI.h"

AIData::AIData(int _searchType, std::vector<Node*> _grid, Sprite* _sprite)
{
	searchType = _searchType;
	grid = _grid;
	image = _sprite;
}

AIData::~AIData()
{
	grid.clear();
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

void AIData::Draw()
{
	image->Draw();
}
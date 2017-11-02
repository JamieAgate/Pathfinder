#include "Movement.h"

Movement::Movement(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	agent = _agent;
	movementDelayTimer = SDL_GetTicks();
}

Movement::~Movement()
{

}

void Movement::Update()
{
	if (SDL_GetTicks() - movementDelayTimer >= 100)
	{
		agent->Move();
		movementDelayTimer = SDL_GetTicks();
	}
}

void Movement::Draw()
{
	agent->Draw();
}
#include "Idle.h"

Idle::Idle(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	startTimer = SDL_GetTicks();
	agent = _agent;
	srand(time(NULL));
	randTimer = rand() % 2001;
}

Idle::~Idle()
{

}

void Idle::Update()
{
	if (SDL_GetTicks() - startTimer >= 1000 + randTimer)
	{
		stateManager->ChangeState(new Search(stateManager, agent));
	}
}

void Idle::Draw()
{
	agent->DrawIdle();
}
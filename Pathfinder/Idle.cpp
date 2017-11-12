#include "Idle.h"

Idle::Idle(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	m_startTimer = SDL_GetTicks();
	m_agent = _agent;
	srand(time(NULL));
	m_randTimer = rand() % 2001;
}

Idle::~Idle()
{

}

void Idle::Update()
{
	if (SDL_GetTicks() - m_startTimer >= 1000 + m_randTimer)
	{
		stateManager->ChangeState(new Search(stateManager, m_agent));
	}
}

void Idle::Draw()
{
	m_agent->DrawIdle();
}
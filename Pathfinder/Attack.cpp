#include "Attack.h"

Attack::Attack(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	m_AttackTimer = SDL_GetTicks() + 1200;
	m_agent = _agent;
}

Attack::~Attack()
{

}

void Attack::Update()
{
	if (SDL_GetTicks() > m_AttackTimer)
	{
		stateManager->ChangeState(new Idle(stateManager ,m_agent));

	}
}

void Attack::Draw()
{
	m_agent->DrawAttack();
}
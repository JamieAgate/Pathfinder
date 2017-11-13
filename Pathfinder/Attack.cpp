/// @file Attack.cpp
/// @brief Attack state for the AI

#include "Attack.h"

Attack::Attack( StateManager* _stateManager, AIData* _agent ) :
	StateTemplate( _stateManager )
{
	m_AttackTimer = SDL_GetTicks() + 1200;//sets the attack timer to be 1.2 seconds from now
	m_agent = _agent;//sets the agent
}

Attack::~Attack()
{

}

void Attack::Update()
{
	if ( SDL_GetTicks() > m_AttackTimer )//if the time is greater than the timer
	{
		m_stateManager->ChangeState( new Idle( m_stateManager, m_agent ) );//change to idle
	}
}

void Attack::Draw()
{
	m_agent->DrawAttack();//draw the attack sprite
}
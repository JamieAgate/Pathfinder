/// @file Idle.cpp
/// @brief Idle state for the AI
#include "Idle.h"

Idle::Idle( StateManager* _stateManager, AIData* _agent ) :
	StateTemplate( _stateManager )
{
	m_startTimer = SDL_GetTicks();//Gets the current time
	m_agent = _agent;//sets the agent
	srand( time( NULL ) );//seeds random
	m_randTimer = rand() % 2001;//sets the random idle time
}

Idle::~Idle()
{

}

void Idle::Update()
{
	if ( SDL_GetTicks() - m_startTimer >= 1000 + m_randTimer )//if timer is greater than 1 second + the random time
	{
		m_stateManager->ChangeState( new Search( m_stateManager, m_agent ) );//switch to the search state
	}
}

void Idle::Draw()
{
	m_agent->DrawIdle();//draw the idle sprite
}
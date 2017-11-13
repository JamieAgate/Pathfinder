/// @file Movement.cpp
/// @brief Movement State for the AI
#include "Movement.h"

Movement::Movement( StateManager* _stateManager, AIData* _agent ) :
	StateTemplate( _stateManager )
{
	m_agent = _agent;//set the agent
	m_movementDelayTimer = SDL_GetTicks();//set the movement delay timer to current time
	m_inputDelay = SDL_GetTicks() + 200;//set the input delay to 0.2s from now
	m_stateSwtich = e_Movement;//set the current state to move
}

Movement::~Movement()
{

}

void Movement::Update()
{
	const Uint8* key = SDL_GetKeyboardState( NULL );//get keyyboard state

	switch ( m_stateSwtich )//switch for current ai state
	{
	case(e_Movement)://will allow the AI to move
	{
		if ( SDL_GetTicks() - m_movementDelayTimer >= 200 )//if the current time is greater than the movement delay
		{
			m_agent->Move();//move the agent
			m_movementDelayTimer = SDL_GetTicks();//reset the delay timer
		}
		if ( key[SDL_SCANCODE_ESCAPE] && SDL_GetTicks() >= m_inputDelay )//if escape is pressed and the current time is greater than the input delay
		{
			m_inputDelay = SDL_GetTicks() + 200;//set the input delay
			m_stateSwtich = e_Path;//set the state switch to show the path and not move
			m_agent->MakeDrawPath();//make the sprite path to be drawn
		}
		if ( m_agent->GetSizeOfPath() > m_agent->GetCurrentSizeOfPath() || m_agent->GetCurrentSizeOfPath() == 0 )//if the AI gets to the end of its path
		{
			m_stateManager->ChangeState( new Search( m_stateManager, m_agent ) );//set the AI state to search
		}
		else if ( m_agent->GetDistanceForPlayer() <= 128 )//if the AI gets within 128 of the player
		{
			m_stateManager->ChangeState( new Attack( m_stateManager, m_agent ) );//switch to attack state
		}
		break;
	}
	case(e_Path)://Will Stop the AI from moving and show the path it is going to take
	{
		if ( key[SDL_SCANCODE_ESCAPE] && SDL_GetTicks() >= m_inputDelay )//if escape is pressed and the current time is greater than the input delay
		{
			m_inputDelay = SDL_GetTicks() + 200;//set the input delay
			m_stateSwtich = e_Movement;//set the state switch to move
		}
		break;
	}
	}
}

void Movement::Draw()
{
	m_agent->Draw();//draw the agent
	if ( m_stateSwtich == e_Path )//if the state is in the path state
	{
		m_agent->DrawPath();//draw the path
	}
}
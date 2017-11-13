/// @file StateManager.cpp
/// @brief The Manager for all states in the state machine
#include "StateManager.h"

StateManager::~StateManager()
{
	for ( unsigned int i = 0; i < m_stateVector.size(); i++ )//destroy all game states in the game states vector
	{
		delete m_stateVector.at( i );
	}
}

void StateManager::AddState( StateTemplate* _state )
{
	m_stateVector.push_back( _state );//push the state into the vector
}

void StateManager::ChangeState( StateTemplate* _state )
{
	for ( unsigned int i = 0; i < m_stateVector.size(); i++ )//delete current game state
	{
		delete m_stateVector.at( i );
	}

	m_stateVector.clear();//clear the vector
	AddState( _state );//add new game state
}

void StateManager::RemoveLastState()
{
	delete m_stateVector.back();//delete the last game state
	m_stateVector.pop_back();
}

void StateManager::Update()
{
	m_stateVector.back()->Update();//update the top state on the vector
}

void StateManager::Draw()
{
	for ( unsigned int i = 0; i < m_stateVector.size(); i++ )
	{
		m_stateVector.at( i )->Draw();//draw all states in the vector
	}
}
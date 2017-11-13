/// @file StateTemplate.cpp
/// @brief The template that all states are based off in the state machine
#include "StateTemplate.h"

StateTemplate::StateTemplate( StateManager* _stateManager )
{
	m_stateManager = _stateManager;//set the state manager to be the state manager being used
}

void StateTemplate::Update()
{

}

void StateTemplate::Draw()
{

}
#include "StateManager.h"

StateManager::~StateManager()
{
	for (unsigned int i = 0; i < stateVector.size(); i++)//destroy all game states in the game states vector
	{
		delete stateVector.at(i);
	}
}

void StateManager::AddState(StateTemplate* _state)
{
	stateVector.push_back(_state);
}

void StateManager::ChangeState(StateTemplate* _state)
{
	for (unsigned int i = 0; i < stateVector.size(); i++)//delete current game state
	{
		delete stateVector.at(i);
	}

	stateVector.clear();//clear the vector
	AddState(_state);//add new game state
}

void StateManager::RemoveLastState()
{
	delete stateVector.back();
	stateVector.pop_back();
}

void StateManager::Update()
{
	stateVector.back()->Update();
}

void StateManager::Draw()
{
	for (unsigned int i = 0; i < stateVector.size(); i++)
	{
		stateVector.at(i)->Draw();
	}
}
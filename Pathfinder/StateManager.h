/// \file StateManager.h
/// \brief Will manage all state based systems.
#pragma once

//File Includes
#include <vector>
//Additional File Includes
#include "StateTemplate.h"

class StateManager
{
public:
	~StateManager();//destructor of StateManager

	void AddState(StateTemplate* _state);//Adds a State to the state vector
	void ChangeState(StateTemplate* _state);//Changes the State to a new state on the vector
	void RemoveLastState();//removes the last state from the state vector

	int GetSizeOfStateVector() { return m_stateVector.size(); }//gets the size of the state vector

	void Update();//Updates the last state on the vector

	void Draw();//Draws the last vector in the state vector
protected:
	std::vector<StateTemplate*> m_stateVector;//vector of states
};


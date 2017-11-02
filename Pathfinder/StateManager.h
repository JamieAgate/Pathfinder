#pragma once
#include "StateTemplate.h"
#include <vector>

class StateManager
{
public:
	~StateManager();

	void AddState(StateTemplate* _state);
	void ChangeState(StateTemplate* _state);
	void RemoveLastState();

	void Update();

	void Draw();
protected:
	std::vector<StateTemplate*> stateVector;
};
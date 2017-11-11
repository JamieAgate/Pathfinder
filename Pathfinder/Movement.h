#pragma once
#include <vector>

#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"
#include "AI.h"
#include "Search.h"

class Movement : public StateTemplate
{
public:
	Movement(StateManager* _stateManager, AIData* _agent);
	~Movement();

	void Update();

	void Draw();
protected:
	AIData* agent;
	int movementDelayTimer;

	int inputDelay;

	enum States { e_Movement, e_Path };
	int stateSwtich;
};
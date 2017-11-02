#pragma once
#include <vector>

#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"
#include "AI.h"

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
};
#pragma once
#include "StateTemplate.h"
#include "StateManager.h"
#include "Search.h"


class Idle : public StateTemplate {
public:
	Idle(StateManager* _stateManager, AIData* _agent);
	~Idle();

	void Update();

	void Draw();
protected:
	int startTimer;
	AIData* agent;
};
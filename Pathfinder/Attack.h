#pragma once
#include "StateTemplate.h"
#include "StateManager.h"
#include "AI.h"
#include "Idle.h"

class Attack : public StateTemplate
{
public:
	Attack(StateManager* _stateManager, AIData* _agent);
	~Attack();

	void Update();

	void Draw();
private:
	AIData* m_agent;
	int m_AttackTimer;
};


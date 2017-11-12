/// \file Attack.h
/// \brief AI state that will be used when the AI is Attacking.

#ifndef _ATTACK_H_
#define _ATTACK_H_
//File Includes
#include "StateTemplate.h"
#include "StateManager.h"
#include "AI.h"
#include "Idle.h"

class Attack : public StateTemplate
{
public:
	Attack(StateManager* _stateManager, AIData* _agent);//Attack constuctor
	~Attack();//Attack Destuructor

	void Update();//Update for Attack

	void Draw();//Draw for Attack
private:
	AIData* m_agent;//The agent in this state
	int m_AttackTimer;//The timer before switching state
};

#endif // !_ATTACK_H_





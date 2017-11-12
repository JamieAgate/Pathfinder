/// \file Idle.h
/// \brief AI state that will be used when the AI is Moving.

#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_
//File Includes
#include <vector>
//Aditional File Includes
#include "StateTemplate.h"
#include "StateManager.h"
#include "Node.h"
#include "AI.h"
#include "Search.h"
#include "Attack.h"

class Movement : public StateTemplate
{
public:
	Movement(StateManager* _stateManager, AIData* _agent);//constuctor of Movement
	~Movement();//destructor of Movement

	void Update();//Update Movement

	void Draw();//Draw Movement
protected:
	AIData* m_agent;//AI agent
	int m_movementDelayTimer;//Delay Timer between each movement

	int m_inputDelay;//delay between pausing to see path

	enum m_States { e_Movement, e_Path };//differnet states for moving and showing path
	int m_stateSwtich;//switch for differnet states
};

#endif // !_MOVEMENT_H_



/// \file Idle.h
/// \brief AI state that will be used when the AI is Idle.
#pragma once


//File Includes
#include <time.h>
#include "StateTemplate.h"
#include "StateManager.h"

#include "Search.h"

class Idle : public StateTemplate {
public:
	Idle(StateManager* _stateManager, AIData* _agent);//Idle consturctor
	~Idle();//Idle Destructor

	void Update();//Update Idle

	void Draw();//Draw Idle
protected:
	int m_startTimer;//Timer used at the start
	int m_randTimer;//Random timer for idles end
	AIData* m_agent;//AI agent
};







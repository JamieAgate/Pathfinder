#pragma once
#ifndef STATETEMPLATE_H
#define STATETEMPLATE_H
#include <SDL.h>

class StateManager;

class StateTemplate 
{
public:
	StateTemplate(StateManager* _stateManager);

	virtual void Update();

	virtual void Draw();
protected:
	StateManager* stateManager;
};
#endif

/// \file StateTemplate.h
/// \brief Template that all other states will inherit from.

#ifndef STATETEMPLATE_H
#define STATETEMPLATE_H
//File Includes
#include <SDL.h>

class StateManager;//Pre-Declaring State Manager

class StateTemplate 
{
public:
	StateTemplate(StateManager* _stateManager);//State Template Constuctor

	virtual void Update();//base Update

	virtual void Draw();//base Draw
protected:
	StateManager* m_stateManager;//State Manager being used.
};
#endif

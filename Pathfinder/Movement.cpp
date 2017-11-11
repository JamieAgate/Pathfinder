#include "Movement.h"

Movement::Movement(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	agent = _agent;
	movementDelayTimer = SDL_GetTicks();
	inputDelay = SDL_GetTicks() + 500;
	stateSwtich = e_Movement;
}

Movement::~Movement()
{

}

void Movement::Update()
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	switch (stateSwtich)
	{
	case(e_Movement):
	{
		if (SDL_GetTicks() - movementDelayTimer >= 200)
		{
			agent->Move();
			movementDelayTimer = SDL_GetTicks();
		}
		if (key[SDL_SCANCODE_ESCAPE] && SDL_GetTicks() >= inputDelay)
		{
			inputDelay = SDL_GetTicks() + 200;
			stateSwtich = e_Path;
			agent->MakeDrawPath();
		}
	break;
	}
	case(e_Path):
	{
		if (key[SDL_SCANCODE_ESCAPE] && SDL_GetTicks() >= inputDelay)
		{
			inputDelay = SDL_GetTicks() + 200;
			stateSwtich = e_Movement;
		}
		break;
	}
	}
}

void Movement::Draw()
{
	agent->Draw();
	if (stateSwtich == e_Path)
	{
		std::cout << agent->GetDrawnathSize() << "\n";
		agent->DrawPath();
	}
}
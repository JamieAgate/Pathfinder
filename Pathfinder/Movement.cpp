#include "Movement.h"

Movement::Movement(StateManager* _stateManager, AIData* _agent) :
	StateTemplate(_stateManager)
{
	m_agent = _agent;
	m_movementDelayTimer = SDL_GetTicks();
	m_inputDelay = SDL_GetTicks() + 200;
	m_stateSwtich = e_Movement;
}

Movement::~Movement()
{

}

void Movement::Update()
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	switch (m_stateSwtich)
	{
	case(e_Movement):
	{
		if (SDL_GetTicks() - m_movementDelayTimer >= 200)
		{
			m_agent->Move();
			m_movementDelayTimer = SDL_GetTicks();
		}
		if (key[SDL_SCANCODE_ESCAPE] && SDL_GetTicks() >= m_inputDelay)
		{
			m_inputDelay = SDL_GetTicks() + 200;
			m_stateSwtich = e_Path;
			m_agent->MakeDrawPath();
		}
		if (m_agent->GetSizeOfPath() > m_agent->GetCurrentSizeOfPath() || m_agent->GetCurrentSizeOfPath() == 0)
		{
			stateManager->ChangeState(new Search(stateManager, m_agent));
		}
		else if (m_agent->GetDistanceForPlayer() <= 128)
		{
			stateManager->ChangeState(new Attack(stateManager, m_agent));
		}
	break;
	}
	case(e_Path):
	{
		if (key[SDL_SCANCODE_ESCAPE] && SDL_GetTicks() >= m_inputDelay)
		{
			m_inputDelay = SDL_GetTicks() + 200;
			m_stateSwtich = e_Movement;
		}
		break;
	}
	}
}

void Movement::Draw()
{
	m_agent->Draw();
	if (m_stateSwtich == e_Path)
	{
		std::cout << m_agent->GetDrawnathSize() << "\n";
		m_agent->DrawPath();
	}
}
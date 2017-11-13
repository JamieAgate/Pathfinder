/// @file InGame.cpp
/// @brief Modual that will run when in game
#include "InGame.h"

InGame::InGame( StateManager* _stateManager, std::vector<Node*> _grid, StateManager* _breadthStateManager, StateManager* _bestFirstStateManager, StateManager* _aStarStateManager, SDL_Renderer* _renderer, Player* _player ) :
	StateTemplate( _stateManager )
{
	m_renderer = _renderer;//sets the renderer

	m_grid = _grid;//sets the grid
	m_breadthStateManager = _breadthStateManager;
	m_bestFirstManager = _bestFirstStateManager;
	m_aStarManager = _aStarStateManager;

	m_player = _player;
}

InGame::~InGame()
{

}

void InGame::Update()
{
	const Uint8* key = SDL_GetKeyboardState( NULL );//Get the KeyBoard State
	//update all Ai Managers
	m_breadthStateManager->Update();
	m_bestFirstManager->Update();
	m_aStarManager->Update();

	m_player->Update();//update Player
	if ( key[SDL_SCANCODE_BACKSPACE] )//if Backspace is pressed
	{
		m_stateManager->ChangeState( new SetUp( m_stateManager, m_breadthStateManager, m_bestFirstManager, m_aStarManager, m_renderer ) );//Change the State to a SetUpState
	}
}

void InGame::Draw()
{
	for ( size_t i = 0; i < m_grid.size(); i++ )//Draw all nodes in Grid
	{
		m_grid.at( i )->Draw();
	}
	//Draw all Ai Managers
	m_breadthStateManager->Draw();
	m_bestFirstManager->Draw();
	m_aStarManager->Draw();

	m_player->Draw();//Draw Player
}
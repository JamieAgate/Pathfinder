#include <SDL/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "StateManager.h"
#include "StateTemplate.h"
#include "Idle.h"
#include "AI.h"
#include "Search.h"
#include "Node.h"
#include "Cursor.h"
#include "SetUp.h"
#include "Player.h"

void MainLoop( SDL_Renderer* _renderer, SDL_Window* _window );

int main( int arc, char* args[] )
{
	const int SCREEN_WIDTH = 960;//sets screen width
	const int SCREEN_HEIGHT = 960;//sets screen height
	SDL_Window* window = NULL;//initializes the window
	SDL_Renderer* renderer = NULL;//initializes the renderer

	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )//initializes SDL
	{
		printf( "SDL could not Initialize. SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		if ( !IMG_Init( (IMG_INIT_PNG)& IMG_INIT_PNG ) )//initializes SDL_IMAGE
		{
			printf( "IMG could not be initialized. SDL_Error: %s\n", SDL_GetError() );
		}
		window = SDL_CreateWindow( "Pathfinder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );//creates the window
		if ( window == NULL )
		{
			printf( "Window couldn't be created. SDL_Error %s\n", SDL_GetError() );
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );//creates the renderer
			if ( renderer == NULL )//initialise renderer
			{
				printf( "Renderer could not be created! SDL_ERROR %s\n", SDL_GetError() );
			}
			else
			{
				MainLoop( renderer, window );//if everything is initializes correctly run the main loop
			}
		}
	}
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	IMG_Quit();
	system( "PAUSE" );
	return 0;
}

void MainLoop( SDL_Renderer* _renderer, SDL_Window* _window )
{

	bool quit = false;//looping variable
	SDL_Event e;//SDL_Event
	StateManager gameStateManager;//create Game State Manager
	StateManager aiStateManager;//create breadth first manager
	StateManager bestFirstStateManager;//create best first manager
	StateManager aStarStateManager;//create A* Manager

	gameStateManager.AddState( new SetUp( &gameStateManager, &aiStateManager, &bestFirstStateManager, &aStarStateManager, _renderer ) );//push the Setup state onto the vector
	while ( !quit )
	{
		while ( SDL_PollEvent( &e ) )//limit FPS
		{
			if ( e.type == SDL_QUIT )
				quit = true;
		}

		SDL_RenderClear( _renderer );//clear renderer

		gameStateManager.Update();//update top state
		gameStateManager.Draw();//draw top state

		SDL_RenderPresent( _renderer );//present renderer
	}
}
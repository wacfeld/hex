#include <stdio.h>

#include "drawer.h"
#include "hex.h"

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		exit(1);
	}

	//Load media
	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
		exit(1);
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

  // for(int x = 0; x < board_size; x++)
  // {
  //   drawHex(side, 100, 200, 
  // }

  // drawHex(side, 100, 200, SDL_Color{ 0, 255, 0, 255 });
  for(int r = 0; r < board_size; r++)
  {
    for(int c = 0; c < board_size; c++)
    {
      drawPiece(RED, r, c);
    }
  }
  update();

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		////Clear screen
		//SDL_SetRenderDrawColor( grend, 0xFF, 0xFF, 0xFF, 0xFF );
		//SDL_RenderClear( grend );

		////Render red filled quad
		//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		//SDL_SetRenderDrawColor( grend, 0xFF, 0x00, 0x00, 0xFF );		
		//SDL_RenderFillRect( grend, &fillRect );

		////Render green outlined quad
		//SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		//SDL_SetRenderDrawColor( grend, 0x00, 0xFF, 0x00, 0xFF );		
		//SDL_RenderDrawRect( grend, &outlineRect );

		////Draw blue horizontal line
		//SDL_SetRenderDrawColor( grend, 0x00, 0x00, 0xFF, 0xFF );		
		//SDL_RenderDrawLine( grend, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

		////Draw vertical line of yellow dots
		//SDL_SetRenderDrawColor( grend, 0xFF, 0xFF, 0x00, 0xFF );
		//for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
		//{
		//	SDL_RenderDrawPoint( grend, SCREEN_WIDTH / 2, i );
		//}

		////Update screen
		//SDL_RenderPresent( grend );
		//getchar();
	}

	//Free resources and close SDL
	close();

	return 0;
}

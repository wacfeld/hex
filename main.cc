#include <stdio.h>

#include "drawer.h"
#include "hex.h"
#include <SDL2/SDL_ttf.h>

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

  for(int r = 0; r < board_size; r++)
  {
    for(int c = 0; c < board_size; c++)
    {
      drawPiece(BLANK, r, c);
      set({r,c}, BLANK);
    }
  }

  // TTF_Font* font = TTF_OpenFont("Sans.ttf", 24);
  // SDL_Color White = {255, 255, 255};
  // for(int c = 0; c < board_size; c++)
  // {
  //   char str[2] = {'a' + c, '\0'};
  //   SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, str, White); 
  //   SDL_Texture* Message = SDL_CreateTextureFromSurface(grend, surfaceMessage);
  //   SDL_Rect Message_rect; //create a rect
  //   Message_rect.x = 50;  //controls the rect's x coordinate 
  //   Message_rect.y = 50; // controls the rect's y coordinte
  //   Message_rect.w = 100; // controls the width of the rect
  //   Message_rect.h = 100; // controls the height of the rect
  //   SDL_RenderCopy(grend, Message, NULL, &Message_rect);
  //   SDL_FreeSurface(surfaceMessage);
  //   SDL_DestroyTexture(Message);
  // }
  update();
  Piece cur = RED;
  
	SDL_Event e;
	while(true)
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				goto end;
			}

			else if(e.type == SDL_MOUSEBUTTONUP)
			{
			  Coord co = getCoord(e.button.x, e.button.y);
			  if(co.r != -1)
			  {
			    if(get(co) == BLANK)
			    {
			      set(co, cur);
			      drawPiece(cur, co.r, co.c);
			      update();

			      if(cur == pTB)
			      {
			        if(connected(top, bottom, matchTB))
			        {
			          printf("red wins!\n");
			          goto wait;
			        }
			      }

			      if(cur == pLR)
			      {
			        if(connected(left ,right, matchLR))
			        {
			          printf("green wins!\n");
			          goto wait;
			        }
			      }
			      
			      cur = opp(cur);
			    }
			  }
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
	
wait:
	while(true)
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				goto end;
			}
		}
	}
	
end:
	//Free resources and close SDL
	close();

	return 0;
}

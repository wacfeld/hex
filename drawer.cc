#include <vector>

#include "drawer.h"
#include "hex.h"

const float side_len = 30;

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

const float tlX = 100;
const float tlY = 100;

//The window we'll be rendering to
SDL_Window* gwin = NULL;

float side2height(int s)
{
  return s * 0.866025;
}

//The window renderer
SDL_Renderer* grend = NULL;

void getCenter(int r, int c, int &x, int &y)
{
  float height = side2height(side_len);
  x = tlX + r*2*height + c*height;
  y = tlY + c*1.5*side_len;
}

float deg2rad(float deg)
{
  const static float pi = 3.14159265358;
  return deg*pi/180;
}

void rotate(int &x, int &y, float deg)
{
  int th = deg2rad(deg);
  int nX = x*cos(th) - y*sin(th);
  int nY = x*sin(th) + y*cos(th);
  x = nX;
  y = nY;
}

bool inHex(int x, int y, int r, int c)
{
  int cX, cY;
  getCenter(r, c, cX, cY);

  int rX = x-cX;
  int rY = y-cY;

  float height = side2height(side_len);
  
  if((rX > height) || (rX < -height))
  {
    return false;
  }

  int nX=rX, nY=rY;
  rotate(nX, nY, 60);
  if((nX > height) || (nX < -height))
  {
    return false;
  }

  nX=rX, nY=rY;
  rotate(nX, nY, -60);
  if((nX > height) || (nX < -height))
  {
    return false;
  }

  return true;
}

Coord getCoord(int x, int y)
{
  for(int r = 0; r < board_size; r++)
  {
    for(int c = 0; c < board_size; c++)
    {
      if(inHex(x, y, r, c))
      {
        return Coord{r,c};
      }
    }
  }

  return Coord{-1,-1};
}

void drawPiece(Piece p, int r, int c)
{
  int x, y;
  getCenter(r, c, x, y);
  
  SDL_Color col;
  if(p == RED) {
    col = SDL_Color{ 255, 0, 0, 255 };
  } else if(p == GREEN) {
    col = SDL_Color{ 0, 255, 0, 255 };
  } else {
    col = SDL_Color{ 255, 255, 255, 255 };
  }

  drawHex(side_len*.99, x, y, col);
}

// https://stackoverflow.com/questions/69447778/fastest-way-to-draw-filled-quad-triangle-with-the-sdl2-renderer
void drawHex(float side, float x, float y, SDL_Color col)
{
  float height = side2height(side);
  
  SDL_Vertex verts[12] =
  {
    { SDL_FPoint{ x+height, y+side/2 },   col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x+height, y-side/2 },   col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x,        y-side },   col, SDL_FPoint{ 0 }, },
    
    { SDL_FPoint{ x-height, y-side/2 }, col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x-height, y+side/2 }, col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x,        y+side },   col, SDL_FPoint{ 0 }, },
    
    { SDL_FPoint{ x,        y-side },   col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x-height, y-side/2 }, col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x,        y+side },   col, SDL_FPoint{ 0 }, },
    
    { SDL_FPoint{ x,        y+side },   col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x+height, y+side/2 },   col, SDL_FPoint{ 0 }, },
    { SDL_FPoint{ x,        y-side },   col, SDL_FPoint{ 0 }, },
  };

  SDL_RenderGeometry( grend, nullptr, verts, 12, nullptr, 0 );
}

void update()
{
	SDL_RenderPresent( grend );
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gwin = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gwin == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			grend = SDL_CreateRenderer( gwin, -1, SDL_RENDERER_ACCELERATED );
			if( grend == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( grend, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( grend );
	SDL_DestroyWindow( gwin );
	gwin = NULL;
	grend = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( grend, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

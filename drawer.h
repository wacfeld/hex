#ifndef DRAWER_H
#define DRAWER_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

extern SDL_Window *gwin;
extern SDL_Renderer *grend;

void drawHex(float x, float y, SDL_Color col);

void update();

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

#endif

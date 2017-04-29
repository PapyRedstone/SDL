#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct{
	SDL_Rect *pos;
	SDL_Surface *flower;
}Flower;

SDL_Surface *SDLInitScreen();
void SDLInit();
SDL_Rect *SDLInitRect(int x, int y);
int collide(int mX, int mY, int fX, int fY, int fw, int fh);

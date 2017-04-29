#include "Function.h"

SDL_Surface *SDLInitScreen(){
	SDL_Surface *screen = SDL_SetVideoMode(909,613,32,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF);
	if(!screen){
		fprintf(stderr, "Erreur init screen : %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_FillRect(screen, NULL, 0xffffff);
	SDL_WM_SetCaption("Flower power", NULL);

	return screen;
}

void SDLInit(){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Erreur init SDL : %s\n", SDL_GetError());
		exit(-1);
	}
}

SDL_Rect *SDLInitRect(int x, int y){
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;

	return rect;
}

int collide(int mX, int mY, int fX, int fY, int fw, int fh){
	return (fX < mX && mX < fX+fw && fY < mY && mY < fY+fh)?1:0;
}

#include "Function.h"

int main()
{	
	//----------------------------------------------------------------------------
	//				Déclaration des variables
	//----------------------------------------------------------------------------
	int nextFrame = 1,i,drag;
	int mX,mY,fX,fY,fw,fh;
	char fileName[20];
	unsigned sizeFlowerArray = 0;

	SDL_Event event;
	event.type = SDL_NOEVENT;

	SDL_Surface *screen;

	SDL_Rect *pos = NULL;

	SDL_Surface *currentFlower= NULL;
	SDL_Surface **flowerText;
	SDL_Surface *background;

	Flower *dragFlower = NULL;
	Flower *flowerArray = NULL;

	printf("Fin Declaration\n");

	//-----------------------------------------------------------------------------
	//				Initialisation
	//----------------------------------------------------------------------------
	srand(time(NULL)); // Initialisation de la graine

	SDLInit();
	screen = SDLInitScreen();

	flowerText = malloc(sizeof(SDL_Surface*)*8);
	for(i=0; i<8; i++){
		sprintf(fileName, "fleur%da.bmp", i+1);
		flowerText[i] = SDL_LoadBMP(fileName);
		if(!flowerText[i]){
			fprintf(stderr, "Error loading flower : %s\n", SDL_GetError());
			return -1;
		}
		SDL_SetAlpha(flowerText[i], SDL_SRCALPHA, 0);
		flowerText[i]->format->Amask = 0xFF000000;
		flowerText[i]->format->Ashift = 24;
	}

	background = IMG_Load("background.jpg");
	if(!background){
		fprintf(stderr, "Error loading backgroundground : %s\n", SDL_GetError());
		return -1;
	}

	printf("Fin Initialisation\n");

	//----------------------------------------------------------------------------
	//				Boucle Principale
	//----------------------------------------------------------------------------
	printf("Debut de la boucle Principale\n");
	while(nextFrame){
		//Recuperation de l'evenent
		printf("test\n");
		fflush(stdout);
		SDL_PollEvent(&event);
		printf("test1\n");
		fflush(stdout);
		switch(event.type){

			//Cas ou on quitte l'application
			case SDL_QUIT:
				printf("test2\n");
				fflush(stdout);
				nextFrame = 0;
				break;

			//Cas d'un boutton de la souris enffonce
			case SDL_MOUSEBUTTONDOWN:
				printf("test3\n");
				fflush(stdout);
				switch(event.button.button){

					//Cas du boutton gauche
					case SDL_BUTTON_LEFT:
						//on ajoute une fleur
						currentFlower = flowerText[rand()%8];
						pos = malloc(sizeof(SDL_Rect));
						pos->x = event.button.x - currentFlower->w/2;
						pos->y = event.button.y - currentFlower->h + 10;
						sizeFlowerArray++;
						flowerArray = realloc(flowerArray, sizeof(Flower)*sizeFlowerArray);
						flowerArray[sizeFlowerArray-1].pos = pos;
						flowerArray[sizeFlowerArray-1].flower = currentFlower;
						break;

					//Cas du boutton droit
					case SDL_BUTTON_RIGHT:
						//on bouge une fleur
						mX = event.button.x;
						mY = event.button.y;
						for(i=0; i<sizeFlowerArray; i++){
							fw = flowerArray[i].flower->w;
							fh = flowerArray[i].flower->h;
							fX = flowerArray[i].pos->x;
							fY = flowerArray[i].pos->y;
							if(collide(mX,mY,fX,fY,fw,fh)){
								drag = 1;
								dragFlower = &flowerArray[i];
								dragFlower->pos->x = event.button.x - dragFlower->flower->w/2;
								dragFlower->pos->y = event.button.y - dragFlower->flower->h + 10;
								break;
							}
						}
						break;
				}
				break;

			//Cas de mouvement de la souris
			case SDL_MOUSEMOTION:
				printf("test4\n");
				fflush(stdout);
				//Si on est en train de bouger une fleur on la deplace sur la souris
				if(drag){
					dragFlower->pos->x = event.button.x - dragFlower->flower->w/2;
					dragFlower->pos->y = event.button.y - dragFlower->flower->h + 10;
				}
				break;

			//Cas d'un boutton de la souris relache
			case SDL_MOUSEBUTTONUP:
				printf("test5\n");
				fflush(stdout);
				switch(event.button.button){

					//Cas du boutton droit
					case SDL_BUTTON_RIGHT:
						//On deselectionne la fleur qui bouge
						drag = 0;
						dragFlower = NULL;
						break;
				}
				break;

			//Cas d'un bouton du clavier enfonce
			case SDL_KEYDOWN:
				printf("test6\n");
				fflush(stdout);
				switch(event.key.keysym.sym){

					//Cas pression sur q
					case 'q':
						//on quitte la boucle principale
						nextFrame = 0;
						break;

					//Cas pression sur c
					case 'c':
						//On supprime toutes les fleurs presentes			
						for(i=0; i<sizeFlowerArray; i++){
							free(flowerArray[i].pos);
						}
						sizeFlowerArray = 0;
						break;

					default:
						break;
				}

			default:
				break;
		}
		//Reinitialisation de l'evenement
		event.type = SDL_NOEVENT;
		printf("test6\n");
		fflush(stdout);
		//----------------------------------------------------------------------------
		//				Affichage
		//----------------------------------------------------------------------------
		SDL_BlitSurface(background,NULL,screen, NULL);
		for(i=0; i<sizeFlowerArray; i++){
			SDL_BlitSurface(flowerArray[i].flower,NULL,screen,flowerArray[i].pos);
		}
		SDL_Flip(screen);
	}
	printf("Fin Boucle Principale\n");
	//----------------------------------------------------------------------------
	//				Liberation de la memoire
	//----------------------------------------------------------------------------
	SDL_FreeSurface(background);
	for(i=0; i<8; i++){
		SDL_FreeSurface(flowerText[i]);
	}
	free(flowerText);
	for(i=0; i<sizeFlowerArray; i++){
		free(flowerArray[i].pos);
	}
	free(flowerArray);

	SDL_Quit();

	printf("Fin de la liberation de memoire\n");
	return 0;
}
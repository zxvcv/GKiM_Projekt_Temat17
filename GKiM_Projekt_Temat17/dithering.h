#ifndef DITHERING_H
#define DITHERING_H

#include <SDL.h>
#include "SDL_functions.h"


struct kolor {
	double r;
	double g;
	double b;
};


/*
funkcja wykonujaca operacj� ditheringu, zwracaj�ca wskaznik do tablicy dwuwymiarowej (o wymiarach wigth i height)
@param surface	wskaznik do obiektu w kt�rym otwarty jest obraz na kt�rym ma zostac wykonana operacja ditheringu
@param palette	paleta dla kt�rej ma zostac wykonana operacja ditheringu
@return			wskaznik na tablice pikseli podanego obrazu z wykonanym ditheringiem w oparciu o podan� palete
@EXCEPTIONS:	---
*/
Uint8 **dithering(SDL_Surface *surface, SDL_Color *palette);

#endif // !DITHERING_H
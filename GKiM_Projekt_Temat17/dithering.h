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
funkcja wykonujaca operacjê ditheringu, zwracaj¹ca wskaznik do tablicy dwuwymiarowej (o wymiarach wigth i height)
@param surface	wskaznik do obiektu w którym otwarty jest obraz na którym ma zostac wykonana operacja ditheringu
@param palette	paleta dla której ma zostac wykonana operacja ditheringu
@return			wskaznik na tablice pikseli podanego obrazu z wykonanym ditheringiem w oparciu o podan¹ palete
@EXCEPTIONS:	---
*/
Uint8 **dithering(SDL_Surface *surface, SDL_Color *palette);

#endif // !DITHERING_H
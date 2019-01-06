#ifndef DITHERING_H
#define DITHERING_H

#include <vector>
#include <SDL.h>
#include "SDL_functions.h"

using namespace std;

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
void dithering(SDL_Surface *surface, std::vector<SDL_Color> &palette, vector<Uint8> &output);

#endif // !DITHERING_H
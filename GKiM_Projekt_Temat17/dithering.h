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
funkcja wykonujaca operacj� ditheringu
@param surface	wskaznik do obiektu z ktorego beda ponierane piksele obrazu
@param palette	przekazana paleta dla kt�rej ma zostac wykonana operacja ditheringu
@param output	tablica do ktorej zostana wypisane dane wyjsciowe
@EXCEPTIONS:	---
*/
void dithering(SDL_Surface *surface, std::vector<SDL_Color> &palette, vector<Uint8> &output);

#endif // !DITHERING_H
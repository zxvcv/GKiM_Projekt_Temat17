#ifndef DATA_PREPARATION_H
#define DATA_PREPARATION_H

#include <vector>
#include <SDL.h>
#include "SDL_functions.h"

using namespace std;

extern SDL_Surface *input_file;

/*
funkcja znajduj¹ca najbli¿szego s¹siada dla kazdego piksela z palety kolorow
@param surface	definuje powierzchnie SDL z ktorej pobierane beda piksele
@param palette	tablica przedstawiajaca palete kolorow uzywan¹ przez funkjce
@param output	tabela daneych generowanych przez funkcjê
@EXCEPTIONS:	---
*/
void nearest_neighbor(SDL_Surface *surface, std::vector<SDL_Color> &palette, vector<Uint8> &output);

#endif // !DATA_PREPARATION_H


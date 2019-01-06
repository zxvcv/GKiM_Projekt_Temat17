#ifndef DATA_PREPARATION_H
#define DATA_PREPARATION_H

#include <vector>
#include <SDL.h>
#include "SDL_functions.h"

using namespace std;

extern SDL_Surface *input_file;

void nearest_neighbor(SDL_Surface *surface, std::vector<SDL_Color> &palette, vector<Uint8> &output);

#endif // !DATA_PREPARATION_H


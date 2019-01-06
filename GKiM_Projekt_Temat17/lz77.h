#ifndef LZ77_H
#define LZ77_H

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include "SDL_functions.h"
#include "palette.h"

//extern SDL_Surface *input_file;
extern SDL_Color ImposedPalette[];
extern SDL_Color ImposedPalette2[];

void lz77_conversion(SDL_Surface *surface, vector<Uint8> &data, vector<kod> &zakodowane);

#endif // !LZ77_H


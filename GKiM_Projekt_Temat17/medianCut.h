#ifndef MEDIAN_CUT_H
#define MEDIAN_CUT_H


#include "pch.h"
#include <algorithm>
#include <SDL.h>
#include <vector>
#include "SDL_functions.h"

using namespace std;

class subspace {
public:
	subspace(Uint8 Rmin, Uint8 Rmax, Uint8 Gmin, Uint8 Gmax, Uint8 Bmin, Uint8 Bmax, short level);
	void divide_to_64_subspaces(int*** colors);
	void create_palette(vector<SDL_Color> &palette, int*** colors);

private:
	SDL_Color botBorder;
	SDL_Color topBorder;
	short level;
	subspace* left;
	subspace* right;
};

void load_dedicated_palette(SDL_Surface * picture, int width, int height, vector<SDL_Color> &tmpPalette);


#endif // !MEDIAN_CUT_H